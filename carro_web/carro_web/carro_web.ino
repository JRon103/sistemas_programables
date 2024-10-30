#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

bool bandera = false;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server(34, 41, 255, 104);  // Dirección IP del servidor MySQL en la nube

char usuario[] = "root";
char pass[] = "carrito";
char db_name[] = "bd_carrito";  // Reemplaza con el nombre de tu base de datos

char INSERT_SQL[] = "INSERT INTO temperaturas(temperatura, lugar) VALUES(43.1, '19M')";

EthernetClient cliente;
MySQL_Connection conn((Client *)&cliente);

void setup() {
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Fallo al obtener una IP mediante DHCP");
    while (true);  // Detiene el programa si no obtiene una IP
  }
  
  Serial.println("Conectando...");
  if (conn.connect(server, 3306, usuario, pass)) {
    delay(1000);
    Serial.println("Conexión exitosa.");

    // Selecciona la base de datos
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    char use_db[50];
    sprintf(use_db, "USE %s", db_name);
    cur_mem->execute(use_db);
    delete cur_mem;
  } else {
    Serial.println("Connection failed.");
  }
}

void loop() {
  if (bandera == false) {
    delay(2000);

    if (!conn.connected()) {  // Verifica si la conexión está activa
      Serial.println("Reconectando...");
      if (conn.connect(server, 3306, usuario, pass)) {
        Serial.println("Reconectado exitosamente.");

        // Selecciona la base de datos tras la reconexión
        MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
        char use_db[50];
        sprintf(use_db, "USE %s", db_name);
        cur_mem->execute(use_db);
        delete cur_mem;
      } else {
        Serial.println("Error al reconectar.");
        return;  // Sale de loop si la reconexión falla
      }
    }

    Serial.println("Insertando Datos");

    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    cur_mem->execute(INSERT_SQL);  // Inserta los datos
    delete cur_mem;

    bandera = true;
  }
}
