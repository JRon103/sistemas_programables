#include <SoftwareSerial.h>
#include "DHT.h"

#define DHTPIN 53     // Pin donde está conectado el sensor

#define DHTTYPE DHT11   // Descomentar si se usa el DHT 11
DHT dht(DHTPIN, DHTTYPE);

byte rx=10;
byte tx=11;
SoftwareSerial bt(rx,tx);
float temperatura;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bt.begin(9600);
   dht.begin();
 
}

void loop() {
  // put your main code here, to run repeatedly:
  
  float t = dht.readTemperature(); //Leemos la temperatura en grados CelsiusSerial.print (" Temperatura:");
  
  if(bt.available()>0){
    //bt.println(bt.readString());
    char letra=bt.read();
    //Serial.println(letra);
    if(letra ==  97){
      Serial.print (" Temperatura:");
      Serial.println (t);
    } 
  }

      delay(1000);
  
}
