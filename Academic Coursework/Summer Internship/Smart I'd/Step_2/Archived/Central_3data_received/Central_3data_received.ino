#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  char msg[50]; // Adjust the size based on the maximum message length
} struct_message;

// Create a struct_message called myData
struct_message myData;

bool beaconReceived[3] = {false}; // Track whether data has been received from each beacon

// Callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println(myData.msg);
  
  // Extract the beacon number from the message
  int beaconNumber = myData.msg[2] - '0'; // Assumes the beacon number is in the third character of the message
  
  // Mark the corresponding beacon as received
  beaconReceived[beaconNumber - 1] = true;
  
  // Check if data has been received from all beacons
  bool allBeaconsReceived = true;
  for (int i = 0; i < 3; i++) {
    if (!beaconReceived[i]) {
      allBeaconsReceived = false;
      break;
    }
  }
  
  // If data has been received from all beacons, print the message
  if (allBeaconsReceived) {
    Serial.println("3 data received");
    
    // Reset the beaconReceived array for the next iteration
    memset(beaconReceived, false, sizeof(beaconReceived));
  }
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packet info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  // Add your code here if needed
  delay(10000);
}
