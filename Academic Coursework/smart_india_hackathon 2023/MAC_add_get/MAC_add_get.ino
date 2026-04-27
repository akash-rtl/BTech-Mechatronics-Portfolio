#include <ESP8266WiFi.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500); //This is mandatory
  
  Serial.print(" Following is the MAC_Address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  // put your main code here, to run repeatedly:

}
