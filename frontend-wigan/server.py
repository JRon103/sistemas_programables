from http.server import BaseHTTPRequestHandler, HTTPServer
import json
import mysql.connector

# Configuración de la base de datos
DB_CONFIG = {
    'host': 'localhost',
    'user': 'root',
    'password': 'password',
    'database': 'bd_wigan'
}

class SimpleServer(BaseHTTPRequestHandler):

    def do_GET(self):
        if self.path == "/usuarios":
            self.get_usuarios()
        else:
            self.not_found()

    def do_POST(self):
        if self.path == "/usuarios":
            self.create_usuario()
        else:
            self.not_found()

    def do_PUT(self):
        if self.path.startswith("/usuarios/"):
            self.update_usuario()
        else:
            self.not_found()

    def do_DELETE(self):
        if self.path.startswith("/usuarios/"):
            self.delete_usuario()
        else:
            self.not_found()

    def get_usuarios(self):
        conn = mysql.connector.connect(**DB_CONFIG)
        cursor = conn.cursor(dictionary=True)
        cursor.execute("SELECT * FROM usuarios")
        usuarios = cursor.fetchall()
        conn.close()

        print(usuarios)

        self.respond(200, usuarios)

    def create_usuario(self):
        content_length = int(self.headers['Content-Length'])
        post_data = json.loads(self.rfile.read(content_length))
        hexa = post_data.get("hexa")

        conn = mysql.connector.connect(**DB_CONFIG)
        cursor = conn.cursor()
        cursor.execute("INSERT INTO usuarios (hexa) VALUES (%s)", (hexa,))
        conn.commit()
        conn.close()

        self.respond(201, {"message": "Usuario creado"})

    def update_usuario(self):
        id_usuario = self.path.split("/")[-1]
        content_length = int(self.headers['Content-Length'])
        put_data = json.loads(self.rfile.read(content_length))
        hexa = put_data.get("hexa")

        conn = mysql.connector.connect(**DB_CONFIG)
        cursor = conn.cursor()
        cursor.execute("UPDATE usuarios SET hexa = %s WHERE id = %s", (hexa, id_usuario))
        conn.commit()
        conn.close()

        self.respond(200, {"message": "Usuario actualizado"})

    def delete_usuario(self):
        id_usuario = self.path.split("/")[-1]

        conn = mysql.connector.connect(**DB_CONFIG)
        cursor = conn.cursor()
        cursor.execute("DELETE FROM usuarios WHERE id = %s", (id_usuario,))
        conn.commit()
        conn.close()

        self.respond(200, {"message": "Usuario eliminado"})

    def not_found(self):
        self.respond(404, {"error": "Not Found"})
        
    def respond(self, status, data):
        self.send_response(status)
        self.send_header("Content-type", "application/json")
        self.send_header("Access-Control-Allow-Origin", "*")  # Permite cualquier origen
        self.send_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS")  # Métodos permitidos
        self.send_header("Access-Control-Allow-Headers", "Content-Type")  # Cabeceras permitidas
        self.end_headers()
        self.wfile.write(json.dumps(data).encode())

    def do_OPTIONS(self):
        self.send_response(200)
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        self.end_headers()

    # def respond(self, status, data):
    #     self.send_response(status)
    #     self.send_header("Content-type", "application/json")
    #     self.end_headers()
    #     self.wfile.write(json.dumps(data).encode())

if __name__ == "__main__":
    server = HTTPServer(('localhost', 8080), SimpleServer)
    print("Servidor corriendo en http://localhost:8080")
    server.serve_forever()
