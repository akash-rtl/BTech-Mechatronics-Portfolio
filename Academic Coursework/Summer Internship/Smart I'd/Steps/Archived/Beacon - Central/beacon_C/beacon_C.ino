#include <WiFi.h>

const char* ssid = "Dark Matter";
const char* password = "omdinesh";
const char* receiverIP = "192.168.137.200"; // IP address of the receiver ESP32
const uint16_t receiverPort = 80; // Port number to send data to

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (client.connect(receiverIP, receiverPort)) {
    Serial.println("Sending data to receiver...");
    client.println("Hello from the Beacon!");
    client.stop();
    delay(5000); // Adjust delay as needed
  } else {
    Serial.println("Connection failed");
    delay(5000); // Retry after 5 seconds
  }
}
