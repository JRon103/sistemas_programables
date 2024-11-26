#include <Ethernet.h>
#include <SPI.h>
#include <Wiegand.h>

// Configuración de Wiegand
WIEGAND wg;
#define WIEGAND_D0 2  // Pin D0 del lector
#define WIEGAND_D1 3  // Pin D1 del lector

// Configuración del relay
#define RELAY_PIN 8   // Pin del relay

EthernetClient client;

void setup() {
  Serial.begin(9600);

  // Inicializar Ethernet con DHCP
  if (Ethernet.begin() == 0) {
    Serial.println("Error obteniendo IP por DHCP");
    while (true); // Detener ejecución si falla DHCP
  }

  // Mostrar la IP asignada
  Serial.print("Dirección IP obtenida: ");
  Serial.println(Ethernet.localIP());

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
  if (client.connect("34.44.90.188", 80)) { // Usar el hostname o IP de la API
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
