#include <Ethernet.h>
#include <SPI.h>
#include <Wiegand.h>

// Configuración de Ethernet
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Dirección MAC
IPAddress ip(192, 168, 1, 177);                      // IP del Arduino
IPAddress server(34, 44, 90, 188);                   // IP de la API

EthernetClient client;

// Configuración de Wiegand
WIEGAND wg;
#define WIEGAND_D0 2  // Pin D0 del lector
#define WIEGAND_D1 3  // Pin D1 del lector

// Configuración del relay
#define RELAY_PIN 8   // Pin del relay

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);

  // Configurar pines
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Apagar relay al inicio

  // Iniciar Wiegand
  wg.begin(WIEGAND_D0, WIEGAND_D1);
  Serial.println("Sistema iniciado y esperando tarjetas...");
}

void loop() {
  // Verificar lectura de la tarjeta
  if (wg.available()) {
    uint32_t cardData = wg.getCode();
    Serial.print("Tarjeta leída: ");
    Serial.println(cardData, HEX); // Mostrar en formato hexadecimal
    
    // Enviar datos a la API
    if (enviarDatosAPI(String(cardData, HEX))) {
      Serial.println("Acceso permitido, activando relay...");
      activarRelay();
    } else {
      Serial.println("Acceso denegado.");
    }
  }
}

// Función para enviar los datos a la API
bool enviarDatosAPI(String tarjetaHex) {
  if (client.connect(server, 80)) {
    Serial.println("Conectado al servidor");
    
    // Crear la solicitud POST
    String postData = "{\"card\":\"" + tarjetaHex + "\"}"; // JSON con datos de la tarjeta
    client.println("POST /endpoint HTTP/1.1"); // Cambiar "/endpoint" al nombre correcto
    client.println("Host: 34.44.90.188");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();
    client.println(postData);

    // Leer la respuesta
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println("Respuesta: " + line);

        // Buscar palabra "success" en la respuesta
        if (line.indexOf("success") != -1) {
          client.stop();
          return true; // Acceso permitido
        }
      }
    }
    client.stop();
  } else {
    Serial.println("Error conectando al servidor");
  }
  return false; // Acceso denegado
}

// Función para activar el relay
void activarRelay() {
  digitalWrite(RELAY_PIN, HIGH); // Activar relay
  delay(5000);                   // Mantener relay activado por 5 segundos
  digitalWrite(RELAY_PIN, LOW);  // Apagar relay
}
