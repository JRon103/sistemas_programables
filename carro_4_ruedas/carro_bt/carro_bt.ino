#include <AFMotor.h>
#include <SoftwareSerial.h>

// Crear objetos para controlar los 4 motores
AF_DCMotor motor1(1); // Trasero izquierdo
AF_DCMotor motor2(2); // Trasero derecho
AF_DCMotor motor3(3); // Frontal derecho
AF_DCMotor motor4(4); // Frontal izquierdo

// Configuración de pines para el módulo Bluetooth
SoftwareSerial BT(50, 52); // RX, TX

// Variables para definir si un motor está invertido
bool invertidoMotor1 = false;  // Motor trasero izquierdo
bool invertidoMotor2 = false;  // Motor trasero derecho
bool invertidoMotor3 = true; // Motor frontal derecho
bool invertidoMotor4 = true; // Motor frontal izquierdo

// Buffer para almacenar el comando recibido
String comando = "";
unsigned long tiempoUltimoComando = 0; // Tiempo del último comando recibido
const unsigned long tiempoLimite = 2000; // Tiempo límite en milisegundos

void setup() {
  // Iniciar comunicación serial
  Serial.begin(9600);
  delay(500);
  BT.begin(9600);
delay(500);
  // Detener todos los motores al inicio
  stopMotors();
  Serial.println("Iniciando");
}
void limpiarBuffer() {
  while (BT.available()) {
    BT.read(); // Leer y descartar el contenido del buffer
  }
}


void loop() {
  // Verificar si hay datos disponibles desde Bluetooth
  while (BT.available()>7) {//porque son 7 caracteres en nuestra transmision c-1.00#
    char c = BT.read(); // Leer un byte del Bluetooth
    delay(10);
    if (c == '#') { // El carácter '#' indica el final de un comando
      Serial.print("Comando recibido: ");
      Serial.println(comando); // Mostrar el comando completo recibido
      comando+="#";
      //voy a separar el comando del valor, deberia de venir algo asi: arriba-0.5
      // Separar el comando usando el carácter '-'
      int separador = comando.indexOf('-');
      int fin = comando.indexOf('#');
      int valorEntero=0;
      if (separador != -1 && fin != -1) {
          String direccion = comando.substring(0, separador);
          String valorStr = comando.substring(separador + 1, fin);
          
          float valorDecimal = valorStr.toFloat(); // Convierte a decimal
          int valorEntero = round(valorDecimal * 255); // Convierte a 0-255
          
          // Asegúrate de que el valor esté en el rango permitido
          if (valorEntero < 0) valorEntero = 0;
          if (valorEntero > 255) valorEntero = 255;
         
          // Ejecutar la acción correspondiente al comando recibido
          //cambiar por wasd por simpleza de caracter
          //centro es c
          if (direccion == "w") {
            moveForward(valorEntero);
          } else if (direccion == "s") {
            moveBackward(valorEntero);
          } else if (direccion == "a") {
            turnLeft(valorEntero);
          } else if (direccion == "d") {
            turnRight(valorEntero);
          } else if (direccion == "c") {
            stopMotors();
          }else{
           limpiarBuffer(); 
            }
          
          // Actualizar el tiempo del último comando recibido
         tiempoUltimoComando = millis();
          
          // Limpiar el buffer de comando para recibir el siguiente
          direccion = "";
          comando="";

          
      }
      
    } else {
      comando += c; // Agregar el carácter al comando actual
    }
    //delay(100);
  }

  // Verificar si ha pasado el tiempo límite desde el último comando
  /*if (millis() - tiempoUltimoComando > tiempoLimite) {
    Serial.println("Conexión Bluetooth perdida. Deteniendo motores.");
    stopMotors(); // Detener los motores si no se recibe comando
  }*/
}

// Función para controlar la dirección de los motores considerando si están invertidos
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

// Función para mover hacia adelante
void moveForward(int valorEntero) {
  Serial.println("Adelante");
  
  motor1.setSpeed(valorEntero);
  motor2.setSpeed(valorEntero);
  motor3.setSpeed(valorEntero);
  motor4.setSpeed(valorEntero);

  controlarMotor(motor1, invertidoMotor1, FORWARD);
  controlarMotor(motor2, invertidoMotor2, FORWARD);
  controlarMotor(motor3, invertidoMotor3, FORWARD);
  controlarMotor(motor4, invertidoMotor4, FORWARD);
}

// Función para mover hacia atrás
void moveBackward(int valorEntero) {
  Serial.println("Atrás");
  
  motor1.setSpeed(valorEntero);
  motor2.setSpeed(valorEntero);
  motor3.setSpeed(valorEntero);
  motor4.setSpeed(valorEntero);

  controlarMotor(motor1, invertidoMotor1, BACKWARD);
  controlarMotor(motor2, invertidoMotor2, BACKWARD);
  controlarMotor(motor3, invertidoMotor3, BACKWARD);
  controlarMotor(motor4, invertidoMotor4, BACKWARD);
}

// Función para girar a la izquierda
void turnLeft(int valorEntero) {
  Serial.println("Izquierda");
  
  motor1.setSpeed(valorEntero);
  motor2.setSpeed(valorEntero);
  motor3.setSpeed(valorEntero);
  motor4.setSpeed(valorEntero);

  controlarMotor(motor1, invertidoMotor1, BACKWARD);
  controlarMotor(motor2, invertidoMotor2, FORWARD);
  controlarMotor(motor3, invertidoMotor3, FORWARD);
  controlarMotor(motor4, invertidoMotor4, BACKWARD);
}

// Función para girar a la derecha
void turnRight(int valorEntero) {
  Serial.println("Derecha");
  
  motor1.setSpeed(valorEntero);
  motor2.setSpeed(valorEntero);
  motor3.setSpeed(valorEntero);
  motor4.setSpeed(valorEntero);

  controlarMotor(motor1, invertidoMotor1, FORWARD);
  controlarMotor(motor2, invertidoMotor2, BACKWARD);
  controlarMotor(motor3, invertidoMotor3, BACKWARD);
  controlarMotor(motor4, invertidoMotor4, FORWARD);
}

// Función para detener los motores
void stopMotors() {
  Serial.println("Detener motores");

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
