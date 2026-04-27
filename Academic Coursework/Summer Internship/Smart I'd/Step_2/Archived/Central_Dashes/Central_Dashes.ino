#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct {
  char msg[50];  // Adjust the size based on the maximum message length
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Track the count of received batches
int batchCount = 0;

// Function to process received data
void processData() {
  Serial.println("--------------------3-data received-----------------");
  batchCount = 0;  // Reset the count for the next iteration
}

// Callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));

  // Print the received data
  Serial.println(myData.msg);

  // Check if the received data is the delimiter
  if (strcmp(myData.msg, "---") == 0) {
    batchCount++;  // Increment the count of received batches
    if (batchCount == 3) {
      processData();  // Call the function to process received data
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
