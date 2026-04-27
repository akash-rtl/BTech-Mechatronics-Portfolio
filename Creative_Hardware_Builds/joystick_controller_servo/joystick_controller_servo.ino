const int SW_pin = 11; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output


#include <Servo.h>

Servo m1;
Servo m2;

int p1 = 0;
int p2 = 0;


void setup() {
  // put your setup code here, to run once:

  
pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);

m1.attach(9);
m1.attach(11);

  
}

void loop() {
  // put your main code here, to run repeatedly:


Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print(" | ");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print(" | ");
  Serial.print("Y-axis: ");
  Serial.print(analogRead(Y_pin));
  Serial.println(" | ");
  delay(200);


if(analogRead(X_pin) < 150){
  
  p1 = 0;
  //motor.write(0);
  }
else if( 150 < analogRead(X_pin) < 800 ){
  
  p1 = 180;
  //motor.write(90);
  
  }

else if(analogRead(X_pin) > 800 ){
  
  p1 = 90;
  //motor.write(180);
  
  }

m1.write(p1);

if(analogRead(Y_pin) < 150){
  
  p2 = 0;
  //motor.write(0);
  }
else if( 150 < analogRead(Y_pin) < 800 ){
  
  p2 = 180;
  //motor.write(90);
  
  }

else if(analogRead(Y_pin) > 800 ){
  
  p2 = 90;
  //motor.write(180);
  
  }

 m2.write(p2);





}
