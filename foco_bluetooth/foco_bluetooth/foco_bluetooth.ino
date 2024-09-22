#include <SoftwareSerial.h> // Incluimos la librería  SoftwareSerial
SoftwareSerial BT(10, 11);  // Definimos los pines RX y TX del Arduino conectados al Bluetooth

// Adicion codigo de foco
int pin = 34;
int incomingByte = 0;
char letra;

void setup()
{
    BT.begin(9600);     // Inicializamos el puerto serie BT (Para Modo AT 2)
    Serial.begin(9600); // Inicializamos  el puerto serie

    // banderas de encendido y pines del foco
    // bool band = false;
    pinMode(pin, OUTPUT);
}

void loop()
{
    if (BT.available() > 0) // Si llega un dato por el puerto BT se envía al monitor serial
    {
        //Serial.write(BT.read());
        letra = BT.read();
        Serial.write(letra);
        
         if (letra== 'a' || letra == 'A')
        {
          //Serial.write("encender");
            digitalWrite(pin, LOW);
        }
        else if (letra== 'e' || letra == 'E')
        {
          
          //  Serial.write("apagado");
            digitalWrite(pin, HIGH);
        }

    }

    if (Serial.available() > 0) // Si llega un dato por el monitor serial se envía al puerto BT
    {
        BT.write(Serial.read());
    }
}
