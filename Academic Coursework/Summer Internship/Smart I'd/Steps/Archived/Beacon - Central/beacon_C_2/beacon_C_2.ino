//Beacon 2

#include <WiFi.h>

const char* ssid = "Dark Matter";
const char* password = "omdinesh";
const char* centralSystemAddress = "192.168.137.200"; // Change to the IP address of the Central System
const uint16_t port = 80; // Port number to send data to

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
  if (client.connect(centralSystemAddress, port)) {
    // Construct the data to send including the beacon name
    String beaconName = "Beacon2"; // Change to the name of the beacon
    String data = beaconName + " here :)"; // Example data

    // Send the data to the central system
    client.println(data);
    Serial.println("Sent data: " + data);

    // Wait before sending the next data
    delay(5000); // Adjust delay as needed
  } else {
    Serial.println("Connection failed");
    delay(5000); // Wait before retrying
  }
}
