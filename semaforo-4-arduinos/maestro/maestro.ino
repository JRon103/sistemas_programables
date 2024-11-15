#include <Wire.h>

const int SEMAFORO_JUAREZ_DERECHA = 10; // ID: 1
const int SEMAFORO_JUAREZ_IZQUIERDA = 11; // ID: 2
const int SEMAFORO_XOCHI_ARRIBA = 8; // ID: 3
const int SEMAFORO_XOCHI_ABAJO = 9; // ID: 4

void setup() {
  Wire.begin(); // Inicia I2C como maestro
  delay(1000);  // Espera un segundo para inicialización
  Serial.begin(9600);
  Serial.println("empezamos");
}

void loop() {
  // Apaga todos los LEDs antes de cada rutina
  apagarTodos();

  // Rutina: Izquierdas de Juárez (encienden rojo en ID 1 y 2)
  sendCommand(SEMAFORO_JUAREZ_DERECHA, 3); // Enciende LED rojo
  sendCommand(SEMAFORO_JUAREZ_IZQUIERDA, 3); // Enciende LED rojo
  delay(2000); // Mantiene encendido durante 5 segundos

  // Apaga todos los LEDs antes de la siguiente rutina
  apagarTodos();

  // Rutina: Recto de Juárez (encienden verde en ID 1 y 2)
  sendCommand(SEMAFORO_JUAREZ_DERECHA, 2); // Enciende LED verde
  sendCommand(SEMAFORO_JUAREZ_IZQUIERDA, 2); // Enciende LED verde
  delay(2000); // Mantiene encendido durante 5 segundos

  // Apaga todos los LEDs antes de la siguiente rutina
  apagarTodos();

  // Rutina: Recto de Xochi (encienden rojo en ID 3 y 4)
  sendCommand(SEMAFORO_XOCHI_ARRIBA, 2); // Enciende LED rojo
  sendCommand(SEMAFORO_XOCHI_ABAJO, 2); // Enciende LED rojo
  delay(2000); // Mantiene encendido durante 5 segundos
}

// Función para apagar todos los LEDs en los esclavos
void apagarTodos() {
  sendCommand(SEMAFORO_JUAREZ_DERECHA, 0);
  sendCommand(SEMAFORO_JUAREZ_IZQUIERDA, 0);
  sendCommand(SEMAFORO_XOCHI_ARRIBA, 0);
  sendCommand(SEMAFORO_XOCHI_ABAJO, 0);
}

// Función para enviar comandos a un semáforo específico
void sendCommand(int slaveAddress, int command) {
 
   Serial.print ("Comando: ");
  Serial.println(command);
   Serial.print("Arduin: ");
   Serial.println(slaveAddress);
  
  Wire.beginTransmission(slaveAddress);
  Wire.write(command);
  Wire.endTransmission();
}
