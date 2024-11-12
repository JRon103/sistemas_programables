#include <Wire.h>
int pinSalida=13;
void setup() {
  // put your setup code here, to run once:
  Wire.begin(1);
  pinMode(pinSalida,OUTPUT);
  Wire.onReceive(recieveEvent);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    delay(300);
}

void recieveEvent(int esclavo){

  int estado = 0;

  if(Wire.available()==1){
    estado = Wire.read();
    Serial.println(estado);
  }

  digitalWrite(pinSalida,estado);
}
