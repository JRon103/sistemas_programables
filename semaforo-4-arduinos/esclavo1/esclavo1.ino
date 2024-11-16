#include <Wire.h>

// Pines del LED RGB principal
#define RED_PIN 3
#define GREEN_PIN 4
#define BLUE_PIN 5

// Pines del LED RGB para vueltas izquierdas
#define LEFT_RED_PIN 10
#define LEFT_GREEN_PIN 11
#define LEFT_BLUE_PIN 12

/*
Esclavo:
ID: 10
17=10
18=11
20=9
*/

void setup() {
  Wire.begin(10); // Cambia para cada esclavo (8, 9, 10, 11)
  Wire.onReceive(receiveEvent); 
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(LEFT_RED_PIN, OUTPUT);
  pinMode(LEFT_GREEN_PIN, OUTPUT);
  pinMode(LEFT_BLUE_PIN, OUTPUT);

  mantenerEnRojo(); // Inicializa en rojo
  Serial.begin(9600);
}

void loop() {
  // El loop queda vacío
}

// Mantiene todos los LEDs en rojo
void mantenerEnRojo() {
  encenderColor(HIGH, LOW, LOW);      // LEDs principales
  encenderColorLeft(HIGH, LOW, LOW); // LEDs de vueltas
}

// Apaga todos los LEDs
void mantenerApagado() {
  encenderColor(LOW, LOW, LOW);      // LEDs principales
}
void mantenerApagadoLeft() {
encenderColorLeft(LOW, LOW, LOW); // LEDs de vueltas
}

// Enciende el color deseado en los pines principales
void encenderColor(int red, int green, int blue) {
  digitalWrite(RED_PIN, red);
  digitalWrite(GREEN_PIN, green);
  digitalWrite(BLUE_PIN, blue);
}

// Enciende el color deseado en los pines de vueltas izquierdas
void encenderColorLeft(int red, int green, int blue) {
  digitalWrite(LEFT_RED_PIN, red);
  digitalWrite(LEFT_GREEN_PIN, green);
  digitalWrite(LEFT_BLUE_PIN, blue);
}

// Maneja los comandos recibidos
void receiveEvent(int bytes) {
  int command = Wire.read(); // Lee el comando
  Serial.print("Comando recibido: ");
  Serial.println(command);

  // Comportamiento basado en el comando
  switch (command) {
    case 0:  // Rojo principal
      mantenerEnRojo();
      break;
    case 2:  // Verde principal
      encenderColor(LOW, HIGH, LOW);
      break;
    case 3:  // Rojo principal
      encenderColor(HIGH, LOW, LOW);
      break;
    case 4:  // Amarillo principal
      encenderColor(HIGH, HIGH, LOW);
      break;
    case 5:  // Verde vueltas
      encenderColorLeft(LOW, HIGH, LOW);
      break;
    case 6:  // Rojo vueltas
      encenderColorLeft(HIGH, LOW, LOW);
      encenderColor(HIGH, LOW, LOW);
      break;
    case 7:  // Amarillo vueltas
      encenderColorLeft(HIGH, HIGH, LOW);
      break;
    case 10: // Apagar todos
      mantenerApagado();
      break;
    case 11: // Apagar todos
      mantenerApagadoLeft();
      break;
    default: // Apagar todos
      mantenerEnRojo();
      break;
  }
}
