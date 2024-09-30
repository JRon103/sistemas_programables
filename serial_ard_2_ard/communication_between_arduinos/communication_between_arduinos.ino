// C++ code
//

#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);
bool abajo = true;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop()
{
  
  if(Serial.available()>0)
  {
  
    String dato = Serial.readString();
    Serial.println(dato);
    
    if(abajo == false)
    {
      lcd.setCursor(0,1);
      lcd.println(dato);
      abajo = true;
    }
    else 
    {
      lcd.setCursor(0,0);
        lcd.print(dato);
        abajo = false;
    
    }
  }
}
