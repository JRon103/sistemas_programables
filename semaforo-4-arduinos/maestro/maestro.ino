#include <Wire.h>

// Definir direcciones de cada esclavo
const int SLAVE_1 = 8;
const int SLAVE_2 = 9;
const int SLAVE_3 = 10;

void setup() {
  Wire.begin(); // Inicia I2C como maestro
  delay(1000);  // Espera un segundo para inicialización
 // Serial.begin(9600);
}

void loop() {
  // Encender LED en todos los esclavos
  /*sendCommand(SLAVE_1, 1); // Enciende LED en esclavo 1
  sendCommand(SLAVE_2, 1); // Enciende LED en esclavo 2
  sendCommand(SLAVE_3, 1); // Enciende LED en esclavo 3
  //Serial.println("encender");
  delay(1000); // LED encendido durante 5 segundos

  // Apagar LED en todos los esclavos
  //Serial.println("apagar");
  sendCommand(SLAVE_1, 0); // Apaga LED en esclavo 1
  sendCommand(SLAVE_2, 0); // Apaga LED en esclavo 2
  sendCommand(SLAVE_3, 0); // Apaga LED en esclavo 3
  delay(1000); // LED apagado durante 5 segundos
  */
  int c=8;
  for(int i =0; i<3;i++){
    sendCommand(c+i, 1);
  }
  delay(1000);
  c=8;
  for(int i =0; i<3;i++){
    sendCommand(c+i, 0);
  }
  delay(1000);
}

// Función para enviar comandos a un esclavo específico
void sendCommand(int slaveAddress, int command) {
  Wire.beginTransmission(slaveAddress);
  Wire.write(command);
  Wire.endTransmission();
}
