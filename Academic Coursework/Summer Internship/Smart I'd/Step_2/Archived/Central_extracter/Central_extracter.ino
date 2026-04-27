#include <esp_now.h>
#include <WiFi.h>
#include <map>
#include <vector>

// Structure example to receive data
// Must match the sender structure
typedef struct {
  char msg[50];  // Adjust the size based on the maximum message length
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Map to store RSSI values for each address
//std::map<String, std::vector<int>> addressRSSIMap;
std::map<String, std::vector<int>> rssiMap;




// Track the count of received batches
int batchCount = 0;

// Function to process received data
void processData() {
  Serial.println("--------------------3-data received-----------------");



  // Print RSSI values for each address----------------------
  /*
  for (const auto& entry : addressRSSIMap) {
    Serial.print(entry.first);
    Serial.print(" : ");
    const std::vector<int>& rssiValues = entry.second;
    for (int i = 0; i < rssiValues.size(); ++i) {
      Serial.print(rssiValues[i]);
      if (i < rssiValues.size() - 1) {
        Serial.print(" ");
      }
    }
    Serial.println();
  }
  */

  Serial.println("RSSI for each address:");
  for (auto& entry : rssiMap) {
    Serial.print("Address: ");
    Serial.print(entry.first);
    Serial.print(", RSSI values: ");
    for (int rssi : entry.second) {
      Serial.print(rssi);
      Serial.print(" ");
    }
    Serial.println();
  }






//----------------------------------------

  Serial.println();
  // Clear the map for the next iteration
  //addressRSSIMap.clear();
  rssiMap.clear();
  batchCount = 0;  // Reset the count for the next iteration
}

// Callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));

  // Print the received data
  Serial.println(myData.msg);

  //-----------------------------------------------------

  // Parse received data
  String dataString = String(myData.msg);

  /*
  int pos1 = dataString.indexOf(", ");
  int pos2 = dataString.indexOf(", ", pos1 + 1);
  int pos3 = dataString.indexOf(", ", pos2 + 1);
  String address = dataString.substring(pos1 + 2, pos2);
  int rssi1 = dataString.substring(pos3 + 2).toInt(); // Parse the RSSI value

  // Update addressRSSIMap
  addressRSSIMap[address].push_back(rssi1);
  */



  int startPos = 0;
    int endPos = 0;  // In the line below, I'm replacing ';' with ')', cause single line data is only there, if multiple data are there in a single line then replace it back.
    while ((endPos = dataString.indexOf(')', startPos)) != -1) {
      String record = dataString.substring(startPos, endPos);
      if (record.length() > 0) {
        int beaconNum = record.charAt(2) - '0'; // Extract beacon number
        int firstCommaPos = record.indexOf(',');
        String address = record.substring(firstCommaPos + 2, firstCommaPos + 14);
        int rssi = record.substring(record.lastIndexOf(',') + 2).toInt();
        if (rssiMap.find(address) == rssiMap.end()) {
          // Address not found in the map, initialize with zeros
          rssiMap[address] = std::vector<int>(3, 0);
        }
        rssiMap[address][beaconNum - 1] = rssi; // Store RSSI value for the address and beacon
      }
      startPos = endPos + 2;
    }


  //------------------------------------------------------------

  // Check if the received data is the delimiter
  if (strcmp(myData.msg, "---") == 0) {
    batchCount++;  // Increment the count of received batches
    if (batchCount == 3) {
      processData();  // Call the function to process received data
      //rssiMap.clear();
    }
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
  delay(1000);  // Delay to prevent the loop from executing too frequently
}
