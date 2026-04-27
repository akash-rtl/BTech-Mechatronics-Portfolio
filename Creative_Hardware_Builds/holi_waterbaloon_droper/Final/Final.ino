#include <Servo.h>
Servo m1;
Servo m2;
int po = 0;


const int echopin= 7;
const int trigpin= 8 ;
long duration;
int distance;





void setup() {
  // put your setup code here, to run once:
pinMode(trigpin,OUTPUT);
pinMode(echopin,INPUT);

Serial.begin(9600);





m1.attach(4);
m2.attach(6);     
Serial.begin(9600);
m1.write(0);
m2.write(180);

pinMode(13,OUTPUT);
digitalWrite(13,HIGH);
}

void loop() {

digitalWrite(13,HIGH);
  
// ##########################################
digitalWrite(trigpin,HIGH);

delayMicroseconds(10);

digitalWrite(trigpin,LOW);

duration=pulseIn(echopin,HIGH);

distance = duration*0.034/2;

Serial.println(distance);

if ((distance < 80 && distance > 15) || (distance > 2000)){
  open();
  delay(500);
  close();
  delay(1000);
  
  }

delay(100);

//###########################################









//##########################################
}



void open(){
  
  m1.write(90);
  m2.write(90);
  }


void close(){
  
  m1.write(0);
  m2.write(180);
  }
