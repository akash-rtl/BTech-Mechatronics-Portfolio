#include <Servo.h>

Servo m1;
Servo m2;
int po = 0;
void setup() {
  // put your setup code here, to run once:
m1.attach(4);
m2.attach(6);     
Serial.begin(9600);
m1.write(0);
  m2.write(180);
}

void loop() {
    open();
    delay(2000);
    close();
    delay(2000);


/*
if (Serial.available()){  
  po = Serial.parseInt();
  if (po == 5){
    
    open();
    delay(1000);
    close();
    
    }



}
*/
}





/*
void open(){
  
  m1.write(90);
  m2.write(90);
  }


void close(){
  
  m1.write(180);
  m2.write(0);
  }

*/


void open(){
  
  m1.write(90);
  m2.write(90);
  }


void close(){
  
  m1.write(0);
  m2.write(180);
  }
