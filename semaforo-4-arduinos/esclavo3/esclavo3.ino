#include <Wire.h>
#define LED_PIN 2 // Pin 2 del Arduino

void setup() {
  // Cambia el número entre paréntesis para cada esclavo (8, 9 o 10)
  Wire.begin(10); // Dirección del esclavo (ajustar según esclavo)
  Wire.onReceive(receiveEvent); // Registra el evento de recepción
  pinMode(LED_PIN, OUTPUT); // Configura el pin 2 como salida
}

void loop() {
  // El loop queda vacío ya que solo reacciona a los comandos del maestro
}

void receiveEvent(int bytes) {
  int command = Wire.read(); // Lee el comando enviado por el maestro
  if (command == 1) {
    digitalWrite(LED_PIN, HIGH); // Enciende el LED en el pin 2
  } else if (command == 0) {
    digitalWrite(LED_PIN, LOW); // Apaga el LED en el pin 2
  }
}
