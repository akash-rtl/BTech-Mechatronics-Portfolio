#include <Servo.h>

Servo m1;

void setup() {
  // put your setup code here, to run once:
    
  Serial.begin(9600);
  m1.attach(5);
  
  m1.write(0);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    if (Serial.readString() == "1"){
      open();
    }
  }
  
  
}


void open(){



}