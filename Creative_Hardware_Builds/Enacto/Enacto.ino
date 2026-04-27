#include <Servo.h>

Servo m1,m2;

void setup() {
  // put your setup code here, to run once:
  

  pinMode(3, OUTPUT);
  digitalWrite(3,HIGH);

  
  Serial.begin(9600);
  m1.attach(5);
  m2.attach(6);

  m1.write(0);
  m2.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    if (Serial.readString() == "1"){
      welcome();
    }
  }
  
  
}


void welcome(){

  

  delay(2500);

  m2.write(90);
  m1.write(90);

  delay(5000);

  m1.write(0);
  m2.write(0);


}