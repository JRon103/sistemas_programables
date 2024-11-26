#include <SPI.h>
#include <Ethernet.h>

// Configuración Ethernet
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Dirección MAC
IPAddress server(34, 41, 255, 104); // Dirección IP del servidor
EthernetClient cliente;

void setup() {
  Serial.begin(9600);

  // Configurar Ethernet
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Error al obtener una IP mediante DHCP.");
    while (true); // Detener si falla DHCP
  }

  Serial.println("Conexión Ethernet exitosa.");
  Serial.print("Dirección IP local: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  if (Serial.available() > 0) {
    String hexValue = Serial.readStringUntil('\n'); // Leer el valor hexadecimal desde la consola
    hexValue.trim(); // Eliminar espacios en blanco

    if (hexValue.length() > 0) {
      Serial.print("Valor recibido: ");
      Serial.println(hexValue);

      // Construir la petición POST
      if (cliente.connect(server, 80)) {
        Serial.println("Conectado al servidor.");

        // Crear el cuerpo de la petición POST
        String postData = "valor_hex=" + hexValue;

        // Enviar cabeceras y cuerpo de la petición
        cliente.println("POST /api/tarjeta HTTP/1.1");
        cliente.println("Host: 34.41.255.104");
        cliente.println("Content-Type: application/x-www-form-urlencoded");
        cliente.print("Content-Length: ");
        cliente.println(postData.length());
        cliente.println(); // Línea vacía para indicar fin de cabeceras
        cliente.println(postData);

        Serial.println("Petición enviada.");
      } else {
        Serial.println("Error al conectar al servidor.");
      }

      // Leer y mostrar la respuesta del servidor
      while (cliente.connected()) {
        if (cliente.available()) {
          char c = cliente.read();
          Serial.print(c);
        }
      }

      // Finalizar la conexión
      cliente.stop();
      Serial.println("\nConexión cerrada.");
    } else {
      Serial.println("Valor vacío. Intenta nuevamente.");
    }
  }
}
