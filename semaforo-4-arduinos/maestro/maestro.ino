#include <Wire.h>

const int SEMAFORO_JUAREZ_DERECHA = 9; // ID: 1
const int SEMAFORO_JUAREZ_IZQUIERDA = 11; // ID: 2
const int SEMAFORO_XOCHI_ARRIBA = 8; // ID: 3
const int SEMAFORO_XOCHI_ABAJO = 10; // ID: 4

void setup() {
  Wire.begin(); 
  Serial.begin(9600);
  Serial.println("Inicio del control de semáforos");
}
void loop() {
  // Rutina: Izquierdas de Juárez (vueltas)
  manejarSemaforoVuelta(SEMAFORO_JUAREZ_DERECHA, SEMAFORO_JUAREZ_IZQUIERDA);

  // Asegurarse de que vuelvan a rojo
  establecerEnRojo(SEMAFORO_JUAREZ_DERECHA, SEMAFORO_JUAREZ_IZQUIERDA);

  // Rutina: Recto de Juárez
  manejarSemaforo(SEMAFORO_JUAREZ_DERECHA, SEMAFORO_JUAREZ_IZQUIERDA);

  // Asegurarse de que vuelvan a rojo
  establecerEnRojo(SEMAFORO_JUAREZ_DERECHA, SEMAFORO_JUAREZ_IZQUIERDA);

  // Rutina: Recto de Xochi
  manejarSemaforo(SEMAFORO_XOCHI_ARRIBA, SEMAFORO_XOCHI_ABAJO);

  // Asegurarse de que vuelvan a rojo
  establecerEnRojo(SEMAFORO_XOCHI_ARRIBA, SEMAFORO_XOCHI_ABAJO);
}

// Establece los semáforos en rojo
void establecerEnRojo(int semaforo1, int semaforo2) {
  enviarComando(semaforo1, 3); // Rojo
  enviarComando(semaforo2, 3); // Rojo
  delay(500); // Pequeña pausa para asegurar la transición
}
9
void manejarSemaforoVuelta(int semaforo1, int semaforo2) {
  // Verde sólido para vueltas
  enviarComando(semaforo1, 5); // Verde vuelta
  enviarComando(semaforo2, 5); // Verde vuelta
  delay(2000);

  // Verde parpadeando para vueltas
  for (int i = 0; i < 4; i++) {
    enviarComando(semaforo1, 5); // Verde vuelta
    enviarComando(semaforo2, 5); // Verde vuelta
    delay(250);
    enviarComando(semaforo1, 11); // Apagar
    enviarComando(semaforo2, 11); // Apagar
    delay(250);
  }

  // Amarillo para vueltas
  enviarComando(semaforo1, 7); // Amarillo vuelta
  enviarComando(semaforo2, 7); // Amarillo vuelta
  delay(2000);

  // Rojo para vueltas
  enviarComando(semaforo1, 6); // Rojo vuelta
  enviarComando(semaforo2, 6); // Rojo vuelta
}

void manejarSemaforo(int semaforo1, int semaforo2) {
  // Verde sólido
  enviarComando(semaforo1, 2); // Verde
  enviarComando(semaforo2, 2); // Verde
  delay(2000);

  // Verde parpadeando
  for (int i = 0; i < 4; i++) {
    enviarComando(semaforo1, 2); // Verde
    enviarComando(semaforo2, 2); // Verde
    delay(250);
    enviarComando(semaforo1, 10); // Apagar
    enviarComando(semaforo2, 10); // Apagar
    delay(250);
  }

  // Amarillo
  enviarComando(semaforo1, 4); // Amarillo
  enviarComando(semaforo2, 4); // Amarillo
  delay(2000);

  // Rojo
  enviarComando(semaforo1, 3); // Rojo
  enviarComando(semaforo2, 3); // Rojo
}

void enviarComando(int slaveAddress, int command) {
  Wire.beginTransmission(slaveAddress);
  Wire.write(command);
  Wire.endTransmission();
  Serial.print("Enviado comando ");
  Serial.print(command);
  Serial.print(" a semáforo ");
  Serial.println(slaveAddress);
}
