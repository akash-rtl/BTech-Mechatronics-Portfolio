#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  
  // Initialize Wi-Fi
  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin();
/*  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
*/  
  // Print MAC address
  Serial.println();
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  // Empty loop
}
