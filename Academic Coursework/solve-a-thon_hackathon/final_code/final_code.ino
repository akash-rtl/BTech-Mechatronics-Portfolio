const unsigned long Interval = 1500;
unsigned long startT = 0;

#include <Servo.h>

Servo g,b;


int ir = 7;


void blue(){
  b.write(110);
  delay(3000);
  b.write(0);
}

void green(){
  g.write(110);
  delay(3000);
  g.write(0);
}





void setup() {
  // put your setup code here, to run once:
 
 Serial.begin(9600);
 
  pinMode(A0, INPUT);
  pinMode(ir, INPUT);
  

  g.attach(5);
  b.attach(6);

  g.write(0);
  b.write(0);
}


void loop() {
  // put your main code here, to run repeatedly:

int k = 0;

unsigned long currentT;


while(digitalRead(ir) == LOW){

  if(k == 0){
  startT = millis();  
  currentT = millis();
  k = 1;
  }
  if(k == 1){
    currentT = millis();
  }

  int a = map(analogRead(A0), 0, 1023, 1000, 0);
  Serial.println(a);

  if((currentT - startT) < Interval){
    //Serial.println(currentT - startT);
    continue;
  }

  if(((currentT - startT) > Interval) && (a < 20)){
    Serial.println("....Blue....");
    blue();
    break;
  }

  if(((currentT - startT) > Interval) && (a > 900)){
    Serial.println("....Metal....");
    blue();
    break;
  }

  if(((currentT - startT) > Interval) && (a > 20)){
    Serial.println("....Green....");
    green();
    break;
  }



}













//int a = analogRead(A0);
//Serial.println(a);


}
