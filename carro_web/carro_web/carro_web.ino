#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include "DHT.h"

#define DHTPIN 26     // Pin donde está conectado el sensor

#define DHTTYPE DHT11   // Descomentar si se usa el DHT 11
DHT dht(DHTPIN, DHTTYPE);
// Configuración de Ethernet

bool bandera = false;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(34, 41, 255, 104); // Dirección IP del servidor MySQL en la nube
EthernetServer webServer(80);

char usuario[] = "root";
char pass[] = "carrito";
char db_name[] = "bd_carrito";
//char temperatura [] ="43.1";
char lugar [] = "19M";


//char INSERT_SQL[] = "INSERT INTO temperaturas(temperatura, lugar) VALUES(43.1, '19M')";
char INSERT_SQL[100];
unsigned long lastInsertTime = 0; // Para medir el tiempo desde la última inserción
const unsigned long interval = 10000; // Intervalo de 2 minutos en milisegundos


EthernetClient cliente;
MySQL_Connection conn((Client *)&cliente);

// Configuración de los motores
AF_DCMotor motor1(1); // Trasero izquierdo
AF_DCMotor motor2(2); // Trasero derecho
AF_DCMotor motor3(3); // Frontal derecho
AF_DCMotor motor4(4); // Frontal izquierdo

bool invertidoMotor1 = true;
bool invertidoMotor2 = false;
bool invertidoMotor3 = true;//moridos
bool invertidoMotor4 = true;//moridos


void setup() {
  Serial.begin(9600);
  dht.begin();
  // Inicializar Ethernet
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Fallo al obtener una IP mediante DHCP");
    while (true);
  }
  webServer.begin();
  Serial.print("Servidor web en: ");
  Serial.println(Ethernet.localIP());
  
  // Conexión a la base de datos
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
  
  // Detener todos los motores al inicio
  stopMotors();
}

void loop() {
  EthernetClient cliente = webServer.available();
  float t = dht.readTemperature();
  String displayTemp = isnan(t) ? getLastTemperature() : String(t, 2);
  
  if (cliente) {
    Serial.println("Nuevo Cliente");
    boolean espacioenblanco = true;
    String cadena = "";
    
    while (cliente.connected()) {
      if (cliente.available()) { 
        char c = cliente.read();
        Serial.write(c);
        cadena.concat(c);
        
        int posicion = cadena.indexOf("accion=");
        if (posicion != -1) {
          String comando = cadena.substring(posicion + 7);
          //Serial.println(comando);
          // Control de motores basado en comando
          if (comando.startsWith("FORWARD")) {
            moveForward(255);
          } else if (comando.startsWith("BACKWARD")) {
            moveBackward(255);
          } else if (comando.startsWith("LEFT")) {
            turnLeft(255);
          } else if (comando.startsWith("RIGHT")) {
            turnRight(255);
          } else if (comando.startsWith("STOP")) {
            stopMotors();
          }
        }
        
        if (c == '\n' && espacioenblanco) {
          cliente.println("HTTP/1.1 200 OK");
          cliente.println("Content-Type: text/html");
          cliente.println();
          cliente.println("<html>");
          cliente.println("<head>");
          cliente.println("</head>");
          cliente.println("<body>");
          cliente.println("<h1 align = 'center'>EQUIPO TeamSP</h1> <h3 align = 'center'>Control de vehiculo por Servidor Web con Arduino</h3>");
             // Temperature Display
          cliente.println("<div class='temp'>Temperatura Actual: " + displayTemp + " °C</div>");
          
          cliente.println("<div style='text-align:center;'>");
          cliente.println("<button onClick=location.href='./?accion=FORWARD' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>Arriba</button>");
          cliente.println("</div>");
          cliente.println("<span> <br> </span>");
          cliente.println("<div style='text-align:center;'>");
          cliente.println("<button onClick=location.href='./?accion=LEFT' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:70px;'>Izquierda</button>");
          cliente.println("<button onClick=location.href='./?accion=STOP' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:70px;'>Detener</button>");
          cliente.println("<button onClick=location.href='./?accion=RIGHT' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:70px;'>Derecha</button>");
          cliente.println(" </div>");
          cliente.println("<span> <br> </span>");
          cliente.println("<div style='text-align:center;'>");
          cliente.println("<button onClick=location.href='./?accion=BACKWARD' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>Abajo</button>");
          cliente.println("</div>");
          cliente.println("</body>");
          cliente.println("</html>");
          break;
        }
        
        if (c == '\n') {
          espacioenblanco = true;
        } else if (c != '\r') {
          espacioenblanco = false;
        }
      }
    }
    
    delay(1);
    cliente.stop();
  }

  // Insertar en la base de datos cada 2 minutos
  unsigned long currentMillis = millis();
  if (currentMillis - lastInsertTime >= interval) {
      Serial.println("Intervalo alcanzado. Intentando insertar datos.");
      lastInsertTime = currentMillis;
      
      // Verificar si la conexión está activa
      if (!conn.connected()) {  
          Serial.println("Reconectando...");
          if (conn.connect(server, 3306, usuario, pass)) {
              Serial.println("Reconectado exitosamente.");
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
  
      // Verificar si la lectura de temperatura es válida
      float t = dht.readTemperature();
      if (isnan(t)) {
          Serial.println("Error al leer la temperatura! No se insertarán datos.");
          return; // Salir si hay un error en la lectura
      }
  
      // Convertir el valor de temperatura a una cadena
      char tempStr[10]; // Suficientemente grande para el valor formateado
      dtostrf(t, 4, 2, tempStr); // Convierte el float t a string con 2 decimales
  
      // Construcción de la consulta SQL
      Serial.println("Insertando Datos");
      sprintf(INSERT_SQL, "INSERT INTO temperaturas(temperatura, lugar) VALUES(%s, '%s')", tempStr, lugar);
      Serial.print("Consulta SQL: ");
      Serial.println(INSERT_SQL); // Imprimir consulta para verificar formato
      MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
      cur_mem->execute(INSERT_SQL);  // Inserta los datos
      delete cur_mem;
  }


}

String getLastTemperature() {
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  char query[100];
  sprintf(query, "SELECT temperatura FROM temperaturas WHERE lugar='%s' ORDER BY id DESC LIMIT 1", lugar);
  
  // Execute query
  cur_mem->execute(query);
  
  // Fetch result
  column_names *cols = cur_mem->get_columns();
  row_values *row = cur_mem->get_next_row();
  
  String lastTemp = "N/A";
  if (row) {
    lastTemp = row->values[0];
  }
  
  delete cur_mem;
  return lastTemp;
}
// Funciones para controlar motores
void controlarMotor(AF_DCMotor &motor, bool invertido, int accion) {
  if (invertido) {
    if (accion == FORWARD) {
      motor.run(BACKWARD);
    } else if (accion == BACKWARD) {
      motor.run(FORWARD);
    } else {
      motor.run(RELEASE);
    }
  } else {
    motor.run(accion);
  }
}

void moveForward(int velocidad) {
  Serial.println("adelante");
  motor1.setSpeed(velocidad);
  motor2.setSpeed(velocidad);
  motor3.setSpeed(velocidad);
  motor4.setSpeed(velocidad);
  controlarMotor(motor1, invertidoMotor1, FORWARD);
  controlarMotor(motor2, invertidoMotor2, FORWARD);
  controlarMotor(motor3, invertidoMotor3, FORWARD);
  controlarMotor(motor4, invertidoMotor4, FORWARD);
}

void moveBackward(int velocidad) {
  Serial.println("atras");
  motor1.setSpeed(velocidad);
  motor2.setSpeed(velocidad);
  motor3.setSpeed(velocidad);
  motor4.setSpeed(velocidad);
  controlarMotor(motor1, invertidoMotor1, BACKWARD);
  controlarMotor(motor2, invertidoMotor2, BACKWARD);
  controlarMotor(motor3, invertidoMotor3, BACKWARD);
  controlarMotor(motor4, invertidoMotor4, BACKWARD);
}

void turnLeft(int velocidad) {
  Serial.println("izquierda");
  
  motor1.setSpeed(velocidad);
  motor2.setSpeed(velocidad);
  motor3.setSpeed(velocidad);
  motor4.setSpeed(velocidad);
  controlarMotor(motor1, invertidoMotor1, BACKWARD);
  controlarMotor(motor2, invertidoMotor2, FORWARD);
  controlarMotor(motor3, invertidoMotor3, FORWARD);
  controlarMotor(motor4, invertidoMotor4, BACKWARD);
}

void turnRight(int velocidad) {
  Serial.println("derecha");
  motor1.setSpeed(velocidad);
  motor2.setSpeed(velocidad);
  motor3.setSpeed(velocidad);
  motor4.setSpeed(velocidad);
  controlarMotor(motor1, invertidoMotor1, FORWARD);
  controlarMotor(motor2, invertidoMotor2, BACKWARD);
  controlarMotor(motor3, invertidoMotor3, BACKWARD);
  controlarMotor(motor4, invertidoMotor4, FORWARD);
}

void stopMotors() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
