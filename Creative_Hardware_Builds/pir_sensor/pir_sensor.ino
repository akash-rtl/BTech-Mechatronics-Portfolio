#define sense D2

void setup() {

Serial.begin(115200);

pinMode(sense,INPUT);

}

void loop() {

if (digitalRead(sense)){
  
  Serial.println("Hila Mat !!!");
  delay(500);
  
}

}
