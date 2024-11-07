#include <Servo.h>
Servo servo1;
int valor = 0;

void setup() {
  servo1.attach(31, 500, 2500);
  Serial.begin(9600); // Asegúrate de que el baud rate coincida con tu monitor serial
}

void loop() {
  if (Serial.available() > 0) {
    String Svalor = Serial.readString();
    valor = Svalor.toInt();
    valor = constrain(valor, 0, 180); // Limita el valor al rango permitido
    Serial.println(valor);
    servo1.write(valor);
  }
  delay(10); // Opcional para dar tiempo al procesamiento
}
