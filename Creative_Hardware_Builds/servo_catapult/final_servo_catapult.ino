const int SW_pin = 8; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output


#include <Servo.h>

Servo m1;
Servo m2;

int pos;

void setup() {
  // put your setup code here, to run once:

  
pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);

m1.attach(8);
m2.attach(12);

m1.write(20);  
}

void loop() {
  // put your main code here, to run repeatedly:

/*
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
*/





float x = analogRead(X_pin);

Serial.print("X: axis:");
Serial.print(x);
Serial.print("| Angle: ");
Serial.print((x*180/1023));
Serial.print("| \n");

pos = ((x*180/1023));
m2.write(pos);
delay(200);

if (Serial.available() > 0){
  
  if (Serial.parseInt() == 1){
    
    m1.write(100);
    
    delay(1000);

    m1.write(20);
    
    }
  
  }


}
