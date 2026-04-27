#include <ESP8266WiFi.h>

#define led D4

WiFiClient client;
WiFiServer server(80);

void setup() {

Serial.begin(9600);
pinMode(led, OUTPUT);

WiFi.begin("OMAKASH", "omdinesh");
Serial.println();

while(WiFi.status() != WL_CONNECTED){
  Serial.print("...");
  delay(500);
}
Serial.println("\nConnected Bhidu \n");
Serial.println(WiFi.localIP());


server.begin(); // by this we begin the NodeMCU as the server.



}

void loop() {
  

  client  = server.available();
   String request;

  if (client == 1){
    
    request = client.readStringUntil('\n'); 
    request.trim(); 
    Serial.println(request);
   }

  if (request == "GET /on HTTP/1.1"){
    digitalWrite(led, HIGH);
  } 
  if (request == "GET /off HTTP/1.1"){
    digitalWrite(led, LOW); 
  }




//Whenever you wanna create a webpage to just type the following 3 lines.

client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("");



//Then whatever your HTML code is, just write it line by line, in the following way:

client.println("<!DOCTYPE html>");
client.println("<html>");
client.println("<head> <title>Welcome Page</title> </head>");
client.println("<body>");
client.println("    <h1>Welcome to the webpage</h1>");
client.println("    <p>Click on one of the buttons below to go to a different webpage:</p>");
    
client.println("    <!-- Button 1 --> <a href=\"/on\"> <button>ON</button> </a>");

client.println("    <!-- Button 2 --> <a href=\"/off\"> <button>OFF</button> </a>");

client.println("</body> </html>");



}