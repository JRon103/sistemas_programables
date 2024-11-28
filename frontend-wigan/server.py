from http.server import BaseHTTPRequestHandler, HTTPServer
import json
import mysql.connector
import time

# Configuración de la base de datos
DB_CONFIG = {
    'host': '34.41.255.104',
    'user': 'root',
    'password': 'carrito',
    'database': 'bd_wigan'
}

# Cola de eventos para mensajes en tiempo real
event_queue = []

class SimpleServer(BaseHTTPRequestHandler):

    def do_GET(self):
        if self.path.startswith("/usuarios/check?hexa="):
            self.check_usuario()
        elif self.path == "/usuarios":
            self.get_usuarios()
        elif self.path == "/usuarios/events":
            self.handle_events()
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

    def check_usuario(self):
        # Extraer el valor de 'hexa' del query string
        import urllib.parse
        query = urllib.parse.urlparse(self.path).query
        params = urllib.parse.parse_qs(query)
        hexa = params.get("hexa", [None])[0]

        if hexa:
            try:
                conn = mysql.connector.connect(**DB_CONFIG)
                cursor = conn.cursor(dictionary=True)
                cursor.execute("SELECT * FROM usuarios WHERE hexa = %s", (hexa,))
                usuario = cursor.fetchone()
                conn.close()

                if usuario:
                    message = f"success"
                else:
                    message = f"Usuario {hexa} no registrado"

                # Agregar el mensaje a la cola de eventos
                event_queue.append(message)

                # Responder al cliente actual
                self.respond(200, {"message": message})
            except Exception as e:
                self.respond(500, {"error": str(e)})
        else:
            self.respond(400, {"error": "Falta el parámetro 'hexa'"})

    def handle_events(self):
        # Configuración para Server-Sent Events
        self.send_response(200)
        self.send_header("Content-Type", "text/event-stream")
        self.send_header("Cache-Control", "no-cache")
        self.send_header("Access-Control-Allow-Origin", "*")
        self.end_headers()

        # Mantener la conexión abierta para enviar eventos en tiempo real
        try:
            while True:
                if event_queue:
                    message = event_queue.pop(0)  # Sacar el primer mensaje de la cola
                    self.wfile.write(f"data: {message}\n\n".encode())
                    self.wfile.flush()
                time.sleep(1)  # Intervalo entre mensajes
        except:
            pass  # Manejo de desconexiones del cliente

    def respond(self, status, data):
        self.send_response(status)
        self.send_header("Content-type", "application/json")
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        self.end_headers()
        self.wfile.write(json.dumps(data).encode())

    def do_OPTIONS(self):
        self.send_response(200)
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        self.end_headers()

    def not_found(self):
        self.respond(404, {"error": "Not Found"})


if __name__ == "__main__":
    #server = HTTPServer(('localhost', 3002), SimpleServer)
    server = HTTPServer(('0.0.0.0', 8080), SimpleServer)

    print("Servidor corriendo en http://localhost:8080")
    server.serve_forever()
