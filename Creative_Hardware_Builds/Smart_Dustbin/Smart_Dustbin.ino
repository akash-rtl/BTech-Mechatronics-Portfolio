#include <Servo.h>
Servo m1;

void setup() {
  
  m1.attach(4);
  m1.write(0);
}

void loop() {

if (digitalRead(2) == false){
  
  m1.write(120);
  delay(2000);

}else if(digitalRead(2) == true){
  m1.write(0);
  delay(500);
}




}
