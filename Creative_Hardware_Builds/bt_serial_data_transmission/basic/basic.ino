void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial.read()=='1'){


  
  Serial.println("LED ON");
  digitalWrite(7,HIGH);
  }
else if (Serial.read() == '0'){

  Serial.println("LED OFF");
  digitalWrite(7,LOW);

}

  


}
