#include <ESP8266WiFi.h> // The library for internet processes.

#define led D4 //connect led to Digital pin 4

/* Server - Client Theroy:
Client is a device which can always just put request (for data), to its higher authority i.e
the Server.
While Server is the main control unit which stores the date and can answer the request for data.

In our case, out mobile/pc is the Client which sends request in form of string, while server is NodeMCU
*/

WiFiClient client; //Just giving the wifi-client a name (or variable...)
WiFiServer server(80); // 80 is the port number, reads data, further check on google.


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
  

  client  = server.available(); //Gets the data whether is client is connected or not.
  String request;

  if (client == 1){
    
    request = client.readStringUntil('\n'); //It will read the string/data from the client untill the end of the sentence.
    //NOTE: hamesha upar wale bracket me single quotes ka hi use karna.
    request.trim(); // this trims the garbage valu
    Serial.println(request);
     
    
  }

  if (request == "GET /on HTTP/1.1"){
    digitalWrite(led, HIGH);
    } 
  if (request == "GET /off HTTP/1.1"){
    digitalWrite(led, LOW);
    }

    
  

}
