// C++ code
//
int LedR = 2;
float temperatura;
void setup()
{
  pinMode(LedR, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int valorArduino = analogRead(A0);
  float voltaje = (valorArduino/1024.0)*5.0;
  temperatura = (voltaje - 0.5)*100;
  Serial.print (" ValorArduino:");
  Serial.print(valorArduino);
  Serial.print(" Voltaje:");
  Serial.print (voltaje);
  Serial.print (" Temperatura:");
  Serial.println (temperatura);
  delay(2000);
}
