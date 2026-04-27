#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "OMAKASH";
const char* password = "omdinesh";

const char* server = "api.thingspeak.com";
const char* apiKey = "WRCMVF6I3UC2LVTW";
const int fieldId = 1; // Replace this with your specific field ID

WiFiClient client;
String fieldValue; // Global variable to store the retrieved value

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
  fieldValue = line; // Store the value in the global variable
  Serial.println("Retrieved value: " + fieldValue);

  Serial.println("Closing connection");
  client.stop();

  delay(60000); // Delay for 1 minute before reading again
}