#include <Servo.h>


Servo g,b;



void setup() {
  // put your setup code here, to run once:
  g.attach(5);
  b.attach(6);

  g.write(0);
  b.write(0);




}

void loop() {
  // put your main code here, to run repeatedly:

/*
for (int i = 0; i > 91; i++ ){

  b.write(i);
  delay(200);

}
*/

}
