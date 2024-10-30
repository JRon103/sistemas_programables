#include <SPI.h> //Importamos librería comunicación SPI
#include <Ethernet.h> //Importamos librería Ethernet

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };//Ponemos la dirección MAC de la Ethernet Shield que está con una etiqueta debajo la placa
IPAddress ip(192,168,1,100); //Asingamos la IP al Arduino
EthernetServer server(80); //Creamos un servidor Web con el puerto 80 que es el puerto HTTP por defecto
int led=4;
String estado="OFF"; //Estado del Led inicialmente "OFF"
char caracter;

void setup(){
  Serial.begin(9600);
  // Inicializamos la comunicación Ethernet y el servidor
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Servidor en: ");
  Serial.println(Ethernet.localIP());
  pinMode(led,OUTPUT);
}


void loop(){
  EthernetClient cliente = server.available(); //Creamos un clientee Web
  //Cuando detecte un clientee a través de una petición HTTP
  if (cliente) {
    
    Serial.println("Nuevo Cliente");
    boolean espacioenblanco = true; //Una petición HTTP acaba con una lí..nea en blanco
    String cadena=""; //Creamos una cadena de caracteres vacía
    
    while (cliente.connected()) {
      if (cliente.available()) {
        
        char c = cliente.read();//Leemos la petición HTTP carácter porcarácter
        Serial.write(c);//Visualizamos la petición HTTP por el Monitor Serial
        cadena.concat(c);//Unimos el String 'cadena' con la petición HTTP (c). De esta manera convertimos la petición HTTP a un String
        //Ya que hemos convertido la petición HTTP a una cadena de caracteres, ahora podremos buscar partes del texto.        
        int posicion=cadena.indexOf("LED="); //Guardamos la posición de la instancia "LED=" a la variable 'posicion'
        
        if(cadena.substring(posicion)=="LED=ON")//Si a la posición'posicion' hay "LED=ON"
        {
          digitalWrite(led,HIGH);
          estado="ON";
        }
        if(cadena.substring(posicion)=="LED=OFF")//Si a la posición'posicion' hay "LED=OFF"
        {
          digitalWrite(led,LOW);
          estado="OFF";
        }
        //Cuando reciba una línea en blanco, quiere decir que la petición HTTP ha acabado y el servidor Web está listo para enviar una respuesta
        if (c == '\n' && espacioenblanco) {
          // Enviamos al clientee una respuesta HTTP
          cliente.println("HTTP/1.1 200 OK");
          cliente.println("Content-Type: text/html");
          cliente.println();
          //Página web en formato HTML
          cliente.println("<html>");
          cliente.println("<head>");
          cliente.println("</head>");
          cliente.println("<body>");
          cliente.println("<h1 align='center'>JLMOTA.MX</h1><h3 align='center'>LED controlado por Servidor Web con Arduino</h3>");
          //Creamos los botones. Para enviar parametres a través de HTML se utiliza el metodo URL encode. Los parámetros se envian a través del símbolo '?'
          cliente.println("<div style='text-align:center;'>");
          cliente.println("<button onClick=location.href='./?LED=ON\'style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>");
          cliente.println("ON");
          cliente.println("</button>");
          cliente.println("<button onClick=location.href='./?LED=OFF\'style='margin:auto;background-color: #84B1FF;color: snow;padding:10px;border: 1px solid #3F7CFF;width:65px;'>");
          cliente.println("OFF");
          cliente.println("</button>");
          cliente.println("<br /><br />");
          cliente.println("<b>LED = ");
          cliente.print(estado);
          cliente.println("</b><br />");
          cliente.println("</b></body>");
          cliente.println("</html>");
          break;
        }
        
        if (c == '\n') {
          espacioenblanco = true;
        }else if (c != '\r') {
          espacioenblanco = false;
        }
        
      }
    }
    //Dar tiempo al navegador para recibir los datos
    delay(1);
    cliente.stop();// Cierra la conexión
  }
}
