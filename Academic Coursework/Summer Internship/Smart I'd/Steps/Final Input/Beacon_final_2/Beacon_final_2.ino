// Beacon 2

#include <BLEDevice.h>
#include <BLEScan.h>
#include <WiFi.h>

const char* ssid = "Dark Matter";
const char* password = "omdinesh";
const char* centralSystemAddress = "192.168.137.200"; // Change to the IP address of the Central System
const uint16_t port = 80; // Port number to send data to

WiFiClient client;

String removeColons(String address) {
  address.replace(":", "");
  return address;
}

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
  BLEScan* pBLEScan;
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);

  Serial.println();
  Serial.println("Scanning for BLE devices...");

  pBLEScan->start(3, false);

  delay(3000);

  pBLEScan->stop();

  BLEScanResults scanResults = BLEDevice::getScan()->getResults(); // Store the scan results

  BLEDevice::deinit();

  delay(2000); // Delay before sending data to the central system

  if (client.connect(centralSystemAddress, port)) {
    Serial.println("Connected to central system");

    // Process the scan results
    int count = scanResults.getCount();
    for (int i = 0; i < count; i++) {
      BLEAdvertisedDevice device = scanResults.getDevice(i);
      if (device.haveName() && device.getName() == "BT05") {
        String address = removeColons(device.getAddress().toString().c_str());
        int rssi = device.getRSSI();
        String data = "( 2, " + address + ", " + String(rssi) + " )";
        client.println(data);
        Serial.println("Sent data to central system: " + data);
      }
    }
  } else {
    Serial.println("Connection to central system failed");
  }

  delay(1000); // Adjust delay as needed before next scan and sending data
}
