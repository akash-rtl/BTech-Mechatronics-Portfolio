#include <Servo.h>

Servo m1,m2;

void setup() {
  // put your setup code here, to run once:
  

    Serial.begin(9600);
  m1.attach(5);
  m2.attach(6);

  // 5 - Bare hand; 6 - Flag hand

  m1.write(0);
  m2.write(60);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    if (Serial.readString() == "1"){
      flag();
    }
  }
  
  
}


void flag(){

  // Flag hand upper limit - 110; lower limit - 60
int l = 60;
int u = 110;


for (int i = 0; i < 5; i++){





for (int i  = 45; i <= 80; i++){
  m1.write(i);
  delay(10);
}
for (int i  = l; i <= u; i++){
  m2.write(i);
  delay(10);
}
for (int i  = 80; i >= 45; i--){
  m1.write(i);
  delay(10);
}
for (int i  = u; i >= l; i--){
  m2.write(i);
  delay(25);
}






}
 

}