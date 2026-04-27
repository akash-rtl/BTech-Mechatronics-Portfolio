#include <Servo.h>

Servo m1;
int val;


void setup() {
  m1.attach(7);
   m1.write(180);   
  Serial.begin(9600);
  }

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(A0);
  Serial.println(val);
  if (val < 45){
    delay(300);
    space();
    delay(100);
  }

  
}

void space(){
  
  m1.write(168);
  delay(300);
  m1.write(180);

}
