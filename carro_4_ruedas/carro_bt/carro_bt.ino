#include <AFMotor.h>
#include <SoftwareSerial.h>

// Crear objetos para controlar los 4 motores
AF_DCMotor motor1(1); // Trasero izquierdo
AF_DCMotor motor2(2); // Trasero derecho
AF_DCMotor motor3(3); // Frontal derecho
AF_DCMotor motor4(4); // Frontal izquierdo

// Configuración de pines para el módulo Bluetooth
SoftwareSerial BT(50, 52); // RX, TX

// Pines del sensor ultrasónico
const int trigPin = 46 ; //cable amarillo
const int echoPin = 48; //cable verde

const int buzzerPin =22; // Pin donde está conectado el buzzer


// Variables para definir si un motor está invertido
bool invertidoMotor1 = false;
bool invertidoMotor2 = false;
bool invertidoMotor3 = true;
bool invertidoMotor4 = true;

// Buffer para almacenar el comando recibido
String comando = "";

unsigned long tiempoUltimoComando = 0;
const unsigned long tiempoLimite = 2000; 

void setup() {
  // Inicializar los pines del sensor ultrasónico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT); // Configurar el pin del buzzer como salida

  Serial.begin(9600);
  delay(500);
  BT.begin(9600);
  //delay(500);
  // Detener todos los motores al inicio
  stopMotors();
  Serial.println("Inicia");
}

//funciones de utilidad
void limpiarBuffer() {
  while (BT.available()) {
    BT.read(); // Leer y descartar el contenido del buffer
  }
}

long medirDistancia() {
  // Enviar pulso de trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Leer la duración del pulso de echo
  long duracion = pulseIn(echoPin, HIGH);
  
  // Calcular la distancia en cm (velocidad del sonido: 343 m/s o 29.1 microsegundos por cm)
  long distancia = duracion * 0.0343 / 2; 
  
  return distancia;
}

void playTone(int frequency, int duration) {
    tone(buzzerPin, frequency, duration); // Emitir tono
    delay(duration); // Esperar el tiempo del tono
    noTone(buzzerPin); // Detener el tono
}

void loop() {
   // Imprimir la distancia medida por el sensor ultrasónico
  long distancia = 0; 
  // Verificar si hay datos disponibles desde Bluetooth
  while (BT.available()) {//porque son 7 caracteres en nuestra transmision c-1.00#
    char c = BT.read(); 
    delay(10);
    if (c == '#') { // El carácter '#' indica el final de un comando
      //Serial.print("Comando recibido: ");
      Serial.println(comando); 
      comando+="#";
      //voy a separar el comando del valor, deberia de venir algo asi: w-0.5
      // Separar el comando usando el carácter '-'
      int separador = comando.indexOf('-');
      int fin = comando.indexOf('#');
      int valorEntero=0;
      if (separador != -1 && fin != -1) {
          String direccion = comando.substring(0, separador);
          String valorStr = comando.substring(separador + 1, fin);
          
          float valorDecimal = valorStr.toFloat(); // Convierte a decimal
          int valorEntero = round(valorDecimal * 255); // Convierte a 0-255
          
          // checando que el valor este en el rango permitido
          if (valorEntero < 0) valorEntero = 0;
          if (valorEntero > 255) valorEntero = 255;
         
          // Ejecutar la acción correspondiente al comando recibido
          //cambiar por wasd por simpleza de caracter
          //centro es c
          distancia = medirDistancia();
          Serial.print("Distancia: ");
          Serial.print(distancia);
          Serial.println(" cm");
            
          if(distancia>10 || distancia <=2){
            if (distancia< 18){
              valorEntero=round(valorEntero*.50);
            }
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
            }else{//llego un comando incompleto o roto, lo ignoramos y limpiamos
             limpiarBuffer(); 
            }
          }else{
            //stopMotors();
            playTone(523, 100); // Nota C (Do) - Octava alta
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
  if (millis() - tiempoUltimoComando > tiempoLimite) {
   // Serial.println("Conexión Bluetooth perdida. Deteniendo motores.");
    stopMotors(); // Detener los motores si no se recibe comando
  }
  delay(100);
  }

// Función para controlar la dirección de los motores por si estan invertidos
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

void moveBackward(int valorEntero) {
  //Serial.println("Atrás");
  
  motor1.setSpeed(valorEntero);
  motor2.setSpeed(valorEntero);
  motor3.setSpeed(valorEntero);
  motor4.setSpeed(valorEntero);

  controlarMotor(motor1, invertidoMotor1, BACKWARD);
  controlarMotor(motor2, invertidoMotor2, BACKWARD);
  controlarMotor(motor3, invertidoMotor3, BACKWARD);
  controlarMotor(motor4, invertidoMotor4, BACKWARD);
}

void turnLeft(int valorEntero) {
  //Serial.println("Izquierda");
  
  motor1.setSpeed(valorEntero);
  motor2.setSpeed(valorEntero);
  motor3.setSpeed(valorEntero);
  motor4.setSpeed(valorEntero);

  controlarMotor(motor1, invertidoMotor1, BACKWARD);
  controlarMotor(motor2, invertidoMotor2, FORWARD);
  controlarMotor(motor3, invertidoMotor3, FORWARD);
  controlarMotor(motor4, invertidoMotor4, BACKWARD);
}

void turnRight(int valorEntero) {
  //Serial.println("Derecha");
  
  motor1.setSpeed(valorEntero);
  motor2.setSpeed(valorEntero);
  motor3.setSpeed(valorEntero);
  motor4.setSpeed(valorEntero);

  controlarMotor(motor1, invertidoMotor1, FORWARD);
  controlarMotor(motor2, invertidoMotor2, BACKWARD);
  controlarMotor(motor3, invertidoMotor3, BACKWARD);
  controlarMotor(motor4, invertidoMotor4, FORWARD);
}

void stopMotors() {
  //Serial.println("Detener motores");

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
