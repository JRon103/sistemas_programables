#include <Wire.h>
byte estado1 = 0;

void setup() {
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(1);
  if(estado1==0){
    estado1=1;
  }else{
    estado1=0;
  }
  Wire.write(estado1);
  Wire.endTransmission();
  delay(1000);
  Wire.beginTransmission(2);
 
  if(estado1)
    Wire.write(0);
  else 
    Wire.write(1);
  
  Wire.endTransmission();
  delay(1000);
  
}
