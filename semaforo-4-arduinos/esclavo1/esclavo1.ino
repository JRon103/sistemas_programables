#include <Wire.h>

// Pines del LED RGB
#define RED_PIN 3
#define GREEN_PIN 4
#define BLUE_PIN 5

void setup() {
  Wire.begin(8); // Cambia para cada esclavo (8, 9, 10, 11)
  Wire.onReceive(receiveEvent); 
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  apagarRGB(); // Apaga el LED RGB al inicio
  Serial.begin(9600);
}

void loop() {
  // El loop queda vacío
}

// Función para apagar el LED RGB
void apagarRGB() {
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}

// Rutina para encender el color deseado
void encenderColor(int red, int green, int blue) {
  digitalWrite(RED_PIN, red);
  digitalWrite(GREEN_PIN, green);
  digitalWrite(BLUE_PIN, blue);
}

void receiveEvent(int bytes) {
  int command = Wire.read(); // Lee el comando
  Serial.print("Comando recibido: ");
  Serial.println(command);

  // Rutinas para los comandos
  if (command == 2) { // Procedimiento para verde
    encenderColor(LOW, HIGH, LOW); // Verde sólido
    delay(2000);

    for (int i = 0; i < 4; i++) { // Verde parpadeando
      encenderColor(LOW, HIGH, LOW);
      delay(250);
      apagarRGB();
      delay(250);
    }

    encenderColor(HIGH, HIGH, LOW); // Amarillo
    delay(2000);

    encenderColor(HIGH, LOW, LOW); // Rojo
  } else if (command == 3) { // Procedimiento para vuelta
    encenderColor(LOW, HIGH, LOW); // Verde sólido
    delay(2000);

    for (int i = 0; i < 4; i++) { // Verde parpadeando
      encenderColor(LOW, HIGH, LOW);
      delay(250);
      apagarRGB();
      delay(250);
    }

    encenderColor(HIGH, HIGH, LOW); // Amarillo
    delay(2000);

    encenderColor(HIGH, LOW, LOW); // Rojo
  } else {
    apagarRGB();
  }
}
