#include <BLEDevice.h>
#include <BLEScan.h>

#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH THE RECEIVER'S MAC Address
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
    char message[50]; // message to send
    //String message;
    
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Create peer interface
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 


String removeColons(String address) {
  address.replace(":", "");
  return address;
}


void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

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

String data = "";
 
void loop() {

// Scanning for BLE --------------------------------------------------------
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

  data = "---";  
  
  strcpy(myData.message, data.c_str());
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));


  // delay(2000);

   int count = scanResults.getCount();
   
    for (int i = 0; i < count; i++) {
      BLEAdvertisedDevice device = scanResults.getDevice(i);
      if (device.haveName() && device.getName() == "BT05") {
        String address = removeColons(device.getAddress().toString().c_str());
        int rssi = device.getRSSI();
        data = "( 2, " + address + ", " + String(rssi) + " )";
        //client.println(data);


        //sending data ------
        
        strcpy(myData.message, data.c_str());
        esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
        // yaha se esp_err_t hata sakte hai I guess

        //Serial.println("Sent data to central system: " + data);
      }
    }
  
  data = "";

  delay(1000);

  




// Set message to send ---------------------------------------------------
/*
  Serial.println("Sent data to central system: " + data);

  strcpy(myData.message, data.c_str());
  /*
  char char_data[data.length() + 1];
  data.toCharArray(char_data, data.length() + 1);

  //myData.message = char_data;
  strcpy(myData.message, char_data);
  * /
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(1000);
*/




}
