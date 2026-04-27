#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>


const char* ssid = "OMAKASH";
const char* password = "omdinesh";

const char* server = "api.thingspeak.com";
const char* apiKey = "WRCMVF6I3UC2LVTW";
const int fieldId = 1; // Replace this with your specific field ID

WiFiClient client;
String Monkey = "0"; // Global variable to store the retrieved value

void alert(){

  sendMessage("Alert! Monkey is spotted......<further detail>");
}

String phoneNumber = "+919580217175"; // satya -7893228182
String apiKey2 = "6468170";


void sendMessage(String message){

  // Data to send with HTTP POST
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey2 + "&text=" + urlEncode(message);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}








//---------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    client.print(String("GET /channels/2324787/fields/") + fieldId + "/last.txt?api_key=" + apiKey);
    client.println(" HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println();
    delay(1000); // Delay for stability
  } else {
    Serial.println("Connection to server failed");
  }

  while (client.available() == 0) {
    // Wait for data
  }

  String line;
  while (client.available()) {
    line = client.readStringUntil('\n');
  }
  Monkey = line; // Store the value in the global variable
  Serial.println(line);

  Serial.println("Closing connection");
  client.stop();

  
  if(Monkey == "1"){
    alert();
    delay(30000);
  }



  delay(500); // Delay for 1 minute before reading again
}