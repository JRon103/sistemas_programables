#include <AFMotor.h>
#include <SoftwareSerial.h>

// Crear objetos para controlar los 4 motores
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
/*
 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
*/
// Configuración de pines para el módulo Bluetooth (RX en pin 19, TX en pin 18)
//verde 10, primero tx
//morado 11 segundo rx
SoftwareSerial BT(51, 53);

void setup() {
  // Iniciar comunicación serial
  Serial.begin(9600);
  BT.begin(9600);

  // Detener todos los motores al inicio
  stopMotors();
 Serial.print("iniciando");
  
}

void loop() {
  // Verificar si hay datos disponibles desde Bluetooth
  if (BT.available()) {
    String direccion = BT.readStringUntil('\n'); // Leer la dirección hasta un salto de línea
    
    Serial.print("Comando recibido: ");
    Serial.println(direccion); // Mostrar la dirección recibida en el monitor serie
    
    // Ejecutar la acción correspondiente a la dirección
    if (direccion == "arriba") {
      moveForward();
    } else if (direccion == "abajo") {
      moveBackward();
    } else if (direccion == "izquierda") {
      turnLeft();
    } else if (direccion == "derecha") {
      turnRight();
    } else if (direccion == "centro") {
      stopMotors();
    } else {
      stopMotors(); // Detener motores si el comando no es reconocido
    }
  }
}

// Función para mover hacia adelante
void moveForward() {
  Serial.println("Adelante");
  motor1.setSpeed(255); // Velocidad máxima
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

// Función para mover hacia atrás
void moveBackward() {
  Serial.println("Atras");
  motor1.setSpeed(255); // Velocidad máxima
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

// Función para girar a la izquierda
void turnLeft() {
  Serial.println("Izquierda");
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

// Función para girar a la derecha
void turnRight() {
  Serial.println("Derecha");
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

// Función para detener los motores
void stopMotors() {
  Serial.println("Detener motores");
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}