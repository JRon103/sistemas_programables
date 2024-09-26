#include <EEPROM.h>
int estado;
String letra;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  Serial.begin(9600);
  estado = EEPROM.read(0);
  //estado=1;
  if(estado==1)
    digitalWrite(2,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    letra = Serial.readString();
   // Serial.print(letra);
    letra.trim();
    Serial.print(letra);
      if(letra=="S" || letra=="s"){
        digitalWrite(2,HIGH);
        Serial.println("Encendido");
        EEPROM.write(0,1);
      }
      if(letra=="N" || letra=="n"){
        digitalWrite(2,LOW);
        Serial.println("Apagado");
        EEPROM.write(0,0);
      } q
    }
}
