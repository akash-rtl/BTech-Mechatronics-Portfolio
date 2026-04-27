String Room_num = "R1";

#include <esp_now.h>
#include <WiFi.h>
#include <map>
#include <vector>

// Coordinates of the three beacons
float x1 = 3.6;
float y_1 = 2.45; //y1 is a header file/funtion in math.h 

float x2 = 3.3;
float y2 = 0.3;

float x3 = 1.05;
float y3 = 3.15;

uint8_t broadcastAddress[] = {0xB8, 0xD6, 0x1A, 0x6B, 0x2B, 0x5C};


// Structure example to receive data
// Must match the sender structure
typedef struct {
  char msg[50];  // Adjust the size based on the maximum message length
} struct_message;

// Create a struct_message called myData
struct_message myData;
struct_message outgoing; //To hold outgoing data

// Map to store RSSI values for each address
//std::map<String, std::vector<int>> addressRSSIMap;
std::map<String, std::vector<int>> rssiMap;




// Track the count of received batches
int batchCount = 0;

// Function to process received data
void processData() {

  // Print RSSI values for each address
  Serial.println("RSSI for each address:");
  for (auto& entry : rssiMap) {
    Serial.print("Address: ");
    Serial.print(entry.first);
    Serial.print(", RSSI values: ");
    const std::vector<int>& rssiValues = entry.second;
    for (int i = 0; i < rssiValues.size(); ++i) {
      Serial.print(rssiValues[i]);
      Serial.print(" ");
    }

    // Calculate and print the 4th, 5th, and 6th values based on the formula
    float r1 = calculateRSSIValue(rssiValues[0]);
    float r2 = calculateRSSIValue(rssiValues[1]);
    float r3 = calculateRSSIValue(rssiValues[2]);

    Serial.print(", Distance values: ");
    Serial.print(r1);
    Serial.print(" ");
    Serial.print(r2);
    Serial.print(" ");
    Serial.print(r3);


    float x_coord = x_calc(r1,r2,r3);
    float y_coord = y_calc(r1,r2,r3);

    Serial.print(", Coordinates: (");
    Serial.print(x_coord);
    Serial.print(", ");
    Serial.print(y_coord);
    Serial.print(")");

    

    //Outgoing message:

    String data_send ="(" + Room_num + ", " + String(x_coord) + ", " + String(y_coord) + ") : " + entry.first;

    strcpy(outgoing.msg, data_send.c_str());

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &outgoing, sizeof(outgoing));
   
      if (result == ESP_OK) {
        Serial.println("Sent with success");
      }
      else {
        Serial.println("Error sending the data");
      }


    Serial.println();
    
  }
  Serial.println("--------------------3-data received-----------------");
  Serial.println();

  String data_send ="---";
  strcpy(outgoing.msg, data_send.c_str());
  esp_now_send(broadcastAddress, (uint8_t *) &outgoing, sizeof(outgoing));

  // Clear the map for the next iteration
  rssiMap.clear();
  batchCount = 0;  // Reset the count for the next iteration
}

float calculateRSSIValue(int input) {
  if (input == 0){
    return 0;
  }
  return pow(10, (-64 - input) / 40.0);
}


float x_calc(float r1, float r2, float r3){

    if(r1 == 0 || r1 == 0 || r3 == 0 ){
      return 0;
    }

    float x_cal = (2*(r1*r1 - r2*r2 - x1*x1 + x2*x2 -y_1*y_1 +y2*y2)*(y3-y2) - 2*(r2*r2 - r3*r3 - x2*x2 +x3*x3 - y2*y2 + y3*y3)*(y2-y_1))/(4*(y3-y2)*(x2-x1)-4*(y2-y_1)*(x3-x2));
    return x_cal;
}

float y_calc(float r1, float r2, float r3){

  if(r1 == 0 || r1 == 0 || r3 == 0 ){
      return 0;
    }

    float y_cal = (2*(r1*r1 - r2*r2 - x1*x1 + x2*x2 -y_1*y_1 +y2*y2)*(x3-x2) - 2*(r2*r2 - r3*r3 - x2*x2 +x3*x3 - y2*y2 + y3*y3)*(x2-x1))/(4*(y2-y_1)*(x3-x2) - 4*(y3-y2)*(x2-x1));
    return y_cal;
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







esp_now_peer_info_t peerInfo;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
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



  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Add your code here if needed
  delay(1000);  // Delay to prevent the loop from executing too frequently
}
