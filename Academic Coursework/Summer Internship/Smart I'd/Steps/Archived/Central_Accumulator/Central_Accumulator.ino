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

String accumulatedData = ""; // Variable to accumulate data from all beacons
int beaconCounter = 0; // Counter to track the number of received data from all beacons

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Connecting to WiFi...");
  
  // Set the static IP address, gateway, subnet mask, and DNS server
  if (!WiFi.config(staticIP, gateway, subnet, dns)){
    Serial.println("FAILED to configure static IP!");
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
    String receivedData = ""; // Initialize variable to accumulate received data

    unsigned long startTime = millis(); // Get the start time

    // Wait for 5 seconds or until the client is disconnected
    while (client.connected() && (millis() - startTime < 5000)) {
      if (client.available()) {
        String data = client.readStringUntil('\n');
        receivedData += data + "; "; // Accumulate the received data
      }
    }

    // Print the received data
    Serial.println("Received data: [" + receivedData.substring(0, receivedData.length() - 2) + "]");

    // Accumulate received data from all beacons
    accumulatedData += receivedData;

    // Increment beacon counter
    beaconCounter++;

    // Check if data has been received from all three beacons
    if (beaconCounter >= 3) {
      // Print accumulated data
      Serial.println("Accumulated data: " + accumulatedData);

      // Clear accumulated data and reset beacon counter
      accumulatedData = "";
      beaconCounter = 0;
    }

    client.stop();
  }
}
