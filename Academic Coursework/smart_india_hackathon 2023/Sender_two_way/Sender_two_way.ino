/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/
#define trigpin1 D2
#define echopin1 D1

#define trigpin2 D6
#define echopin2 D5

long duration1;
int distance1;

long duration2;
int distance2;




#include <ESP8266WiFi.h>
#include <espnow.h>

// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x84, 0xCC, 0xA8, 0xA9, 0xB8, 0xC6};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  String d;
  bool e;
} struct_message;

// Create a struct_message called myData
struct_message myData; // for sending data


unsigned long lastTime = 0;  
unsigned long timerDelay = 100;  // send readings timer

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  //Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    //Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}








void setup() {
  // Init Serial Monitor
  pinMode(trigpin1,OUTPUT);
  pinMode(echopin1,INPUT);

  pinMode(trigpin2,OUTPUT);
  pinMode(echopin2,INPUT);

  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);
  
  Serial.begin(9600);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);


  analogWrite(D4,10);
  analogWrite(D7,10);
  analogWrite(D8,10);

    
}

void loop() {
//Serial.println(myData1.b);

//digital write -> 0 to 255
// D3, D4, D7, D8




digitalWrite(trigpin1,HIGH);
delayMicroseconds(10);
digitalWrite(trigpin1,LOW);
duration1=pulseIn(echopin1,HIGH);
distance1 = duration1*0.034/2;
//Serial.println(distance1);
delay(50);

digitalWrite(trigpin2,HIGH);
delayMicroseconds(10);
digitalWrite(trigpin2,LOW);
duration2=pulseIn(echopin2,HIGH);
distance2 = duration2*0.034/2;
//Serial.println(distance2);
delay(50);


if(distance1 < 30){

  analogWrite(D4,250);
  analogWrite(D7,250);
  analogWrite(D8,250);
}


if(distance2 < 30){

  

  
  
  analogWrite(D4,10);
  analogWrite(D7,10);
  analogWrite(D8,10);


    if ((millis() - lastTime) > timerDelay) {
    // Set values to send
    
    /*
    strcpy(myData.a, "THIS IS A CHAR");
    myData.b = random(1,20);
    myData.c = 1.2;
    myData.d = "Hello";
    myData.e = false;
    */
    
    myData.d = "h";
  
    
  
    //myData.b = distance2;
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    lastTime = millis();
  
  }

  }
  
  if ((millis() - lastTime) > timerDelay) {
    // Set values to send
    
    /*
    strcpy(myData.a, "THIS IS A CHAR");
    myData.b = random(1,20);
    myData.c = 1.2;
    myData.d = "Hello";
    myData.e = false;
    */
    myData.d = "a";
    
  
    //myData.b = distance2;
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    lastTime = millis();
  
  }
  
  
  
}