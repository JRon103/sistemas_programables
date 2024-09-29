#include <SoftwareSerial.h>
#include "DHT.h"

#define DHTPIN 53     // Pin donde está conectado el sensor
DHT dht(DHTPIN, DHTTYPE);

byte rx=10;
byte tx=11;
SoftwareSerial bt(rx,tx);
float temperatura;

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
   dht.begin();
 
}

void loop() {
  float t = dht.readTemperature();
  
  if(bt.available()>0){
    char letra=bt.read();
    if(letra ==  97){ // inserte letra a para enviar la temperatura
      Serial.print (" Temperatura:");
      Serial.println (t);
    } 
  }

      delay(1000);
  
}
