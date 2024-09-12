
int pin=30;
void setup() {
  // put your setup code here, to run once:
  bool band=false;
  pinMode(pin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
   digitalWrite(pin,HIGH);
   delay (5000);  
  
    digitalWrite(pin,LOW);
  delay (5000); 
  
}
