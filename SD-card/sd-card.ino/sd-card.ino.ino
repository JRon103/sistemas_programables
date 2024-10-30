#include <SPI.h> //Importamos librería comunicación SPI
#include <SD.h>
File archivo;
String estado="OFF";  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){;}
  Serial.print("Inicializando Sd..");
  if(!SD.begin()){
    Serial.println("Error inicialización!");
    return;
  }
  Serial.println("Inicializando");
  archivo = SD.open("prueba.txt",FILE_WRITE);
  if(archivo){
    Serial.print("Probando");

    //-------------------------------------------
        archivo.println("HTTP/1.1 200 OK");
        archivo.println("Content-Type: text/html");
        archivo.println();
        //Página web en formato HTML
        archivo.println("<html>");
        archivo.println("<head>");
        archivo.println("</head>");
        archivo.println("<body>");
        archivo.println("<h1 align='center'>JLMOTA.MX</h1><h3 align='center'>LED controlado por Servidor Web con Arduino</h3>");
        //Creamos los botones. Para enviar parametres a través de HTML se utiliza el metodo URL encode. Los parámetros se envian a través del símbolo '?'
        archivo.println("<div style='text-align:center;'>");
        archivo.println("<button onClick=location.href='./?LED=ON\'style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>");
        archivo.println("ON");
        archivo.println("</button>");
        archivo.println("<button onClick=location.href='./?LED=OFF\'style='margin:auto;background-color: #84B1FF;color: snow;padding:10px;border: 1px solid #3F7CFF;width:65px;'>");
        archivo.println("OFF");
        archivo.println("</button>");
        archivo.println("<br /><br />");
        archivo.println("<b>LED = ");
        archivo.print(estado);
        archivo.println("</b><br />");
        archivo.println("</b></body>");
        archivo.println("</html>");
    //-------------------------------------------
    
    archivo.close();
    Serial.println("Guardado");
  }else {
    Serial.println("Error");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
