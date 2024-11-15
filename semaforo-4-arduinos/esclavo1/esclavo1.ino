#include <Wire.h>
#define GREEN_PIN 51  // LED verde
#define RED_PIN 3    // LED rojo

void setup() {
  Wire.begin(8); // Cambiar para cada esclavo (8, 9, 10, 11)
  Wire.onReceive(receiveEvent); 
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  Serial.begin(9600);
  //digitalWrite(GREEN_PIN, HIGH);
  
}

void loop() {

  // El loop queda vacío
}

void receiveEvent(int bytes) {
  int command = Wire.read(); // Lee el comando
  Serial.println("comando: ");
  Serial.println(command);
  // Apaga ambos LEDs antes de encender el correspondiente
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(RED_PIN, LOW);

  // Controla los LEDs en función del comando recibido
  if (command == 2) {
    digitalWrite(GREEN_PIN, HIGH);  // Enciende LED verde
    Serial.println("verde prendido");
  } else if (command == 3) {
    digitalWrite(RED_PIN, HIGH);    // Enciende LED rojo
  }
}
