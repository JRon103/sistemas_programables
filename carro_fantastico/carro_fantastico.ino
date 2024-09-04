int leds[10] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4};
int i = 0;
bool flag = true;
void setup()
{
  for (int i = 0; i < 10; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop()
{
  if(flag){
    digitalWrite(leds[i++], HIGH);
    delay(200);
    digitalWrite(leds[i-1], LOW);
    if(i==9) flag = false;
  }else{
    digitalWrite(leds[i--], HIGH);
    delay(200);
    digitalWrite(leds[i+1], LOW);
    if(i==0) flag = true;

      
  }
}
