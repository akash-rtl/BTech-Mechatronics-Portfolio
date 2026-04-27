void setup() {
  // put your setup code here, to run once:
pinMode(5,INPUT);
Serial.begin(9600);
}

void loop() {
if (digitalRead(5) == HIGH){
  Serial.print(1);
  delay(5000);
}
}
