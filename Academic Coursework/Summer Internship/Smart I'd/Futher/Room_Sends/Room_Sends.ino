String room = "R1";
String data = " ";

#include <BLEDevice.h>
#include <BLEScan.h>

#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0xB8, 0xD6, 0x1A, 0x6B, 0x2B, 0x5C};

// Boss MACaddress: {0xB8, 0xD6, 0x1A, 0x6B, 0x2B, 0x5C}

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
  // put your setup code here, to run once:
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

void loop() {
  // put your main code here, to run repeatedly:

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

  delay(1500);

  pBLEScan->stop();

  BLEScanResults scanResults = BLEDevice::getScan()->getResults(); // Store the scan results

  BLEDevice::deinit();

// Sending the data ----------------------------------------------------------

  int count = scanResults.getCount();
   
  for (int i = 0; i < count; i++) {

    BLEAdvertisedDevice device = scanResults.getDevice(i);

    if (device.haveName() && device.getName() == "BT05") {
        String address = removeColons(device.getAddress().toString().c_str());
        //int rssi = device.getRSSI();
        data = "( " + room + ", " + address + ")";
        //client.println(data);


        //sending data ------
        
        strcpy(myData.message, data.c_str());
        esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
        // yaha se esp_err_t hata sakte hai I guess

        //Serial.println("Sent data to central system: " + data);
    }
      /*
        if (i == (count - 1)){
          data = "---";

          strcpy(myData.message, data.c_str());
        esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
        }
      */

  }


// Finalizing ---------------------------------------------------------------------
  data = "";




}
