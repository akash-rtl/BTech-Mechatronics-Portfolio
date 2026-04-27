#include <WiFi.h>

const char* ssid = "Dark Matter";
const char* password = "omdinesh";
const uint16_t port = 80; // Port number to receive data on

// Define the static IP address, gateway, subnet mask, and DNS server
IPAddress staticIP(192, 168, 137, 200); // Change to your desired static IP address
IPAddress gateway(192, 168, 137, 1); // Change to your router's IP address
IPAddress subnet(255, 255, 255, 0); // Change to your subnet mask
IPAddress dns(8, 8, 8, 8); // Change to your DNS server's IP address

WiFiServer server(port);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Connecting to WiFi...");
  
  // Set the static IP address, gateway, subnet mask, and DNS server
  if(!WiFi.config(staticIP, gateway, subnet, dns)){
    Serial.print("FAILED DUDES!!!");
  }
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  client = server.available();

  if (client) {
    Serial.println("Client connected");

    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\n');
        Serial.println("Received data: " + data);
      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}
