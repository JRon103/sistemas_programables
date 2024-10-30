#include <SPI.h> //Importamos librería comunicación SPI
#include <SD.h>
File archivo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.print("Inicializando Sd..");
  if(!SD.begin()){
    Serial.println("Error inicialización!");
    return;
  }
  archivo = SD.open("prueba.txt");
 
  if(archivo){
    Serial.println("prueba.txt");
    while(archivo.available()){
      Serial.write(archivo.read());
    }
    archivo.close();
  }else {
    Serial.println("Error");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
