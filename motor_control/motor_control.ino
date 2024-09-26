int motorAPin1 = 5; // Pin 5 de L293 
int motorBPin2 = 6;// Pin 6 de L293

void setup() {
  pinMode (motorAPin1, OUTPUT);
  pinMode (motorBPin2, OUTPUT);
}
void loop() {
  
  
  
  digitalWrite (motorAPin1, HIGH); // Al activar gira el motor A en sentido de las agujas del digitalWrite(motorBPin2, HIGH); // Al activar gira el motor B en sentido de las agujas del
  digitalWrite (motorBPin2, HIGH);
  while(1){} // Esta parte del codigo inicia un bucle inifinito.
} 
