#include <EEPROM.h>
#include <SoftwareSerial.h>

int estado;
//Bluetooth
byte rx=10;
byte tx=11;
SoftwareSerial bt(rx,tx);

//password
bool set_password=false;
unsigned int length_password;
//String password="";
String incoming_password;

int pin_led=2;
void setup() {


  //reset all memory from the EEPROM
  /*pinMode(13, OUTPUT);

   for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }

  // turn the LED on when we're done
  digitalWrite(13, HIGH);
  Serial.println("termino");
  */
  EEPROM.write(0,0);
  
  pinMode(pin_led,OUTPUT);  //led
  Serial.begin(9600);
  bt.begin(9600);

  length_password = EEPROM.read(0);
  if(length_password==0){
    set_password=true;
    Serial.println("configurando contraseña");
  }
   else
  {
    Serial.println("introduce la contraseña");
   
  }
}

void loop() {
  
  if(set_password){
    //setting the password
    if(Serial.available()){
     incoming_password = Serial.readString();
     incoming_password.trim();
     Serial.println("tu contraseña es: " + incoming_password);
     
     EEPROM.write(0, incoming_password.length());
      for (int i = 0; i < incoming_password.length(); i++) {
        EEPROM.write(i + 1, incoming_password[i]);
      }
      
      Serial.println("largo de la contraseña actual: " + String(incoming_password.length()));
      
      set_password=false;
      Serial.println("contraseña configurada correctamente");
      length_password=incoming_password.length();
    }
   
  }
  else
    {
       
      //trying to enter to the system, if succesfull enable a led in "pin_led"
      if(Serial.available()){
        
        delay(50); // for stability purposes
        incoming_password = Serial.readString();
        
        incoming_password.trim();
        Serial.println("contraseña que viene: " + incoming_password);

           //contraseña esperada
        char password[length_password+1];
        for (int i = 0; i < length_password; i++) {
        password[i] = EEPROM.read(i + 1);
        }
        password[length_password] = '\0';
        Serial.print("contraseña esperada: ");
        Serial.println(password);
        if (incoming_password.equals(password)) {
          Serial.println("contraseña correcta :D");
          digitalWrite(pin_led, HIGH);
        } else{
          
          Serial.println("contraseña incorrecta >:(");
        }
      }
   
    }
}
