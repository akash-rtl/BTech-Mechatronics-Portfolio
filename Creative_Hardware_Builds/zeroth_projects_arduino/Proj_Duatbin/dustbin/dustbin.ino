/*
  Sensor t = 6, e = 3

  Motor 1 : 7, 12

  motor 2 : 8, 11



*/




const int trigpin= 6 ;
const int echopin= 3;

const int La = 7;
const int Lb = 12;


const int Ra = 8;
const int Rb = 11;


long duration;
int distance;

int sense = 0;

void setup(){

pinMode(La,OUTPUT);
pinMode(Lb,OUTPUT);



pinMode(Ra,OUTPUT);
pinMode(Rb,OUTPUT);



pinMode(trigpin,OUTPUT);
pinMode(echopin,INPUT);

Serial.begin(9600);


}

void loop(){

  sense = 0;

digitalWrite(trigpin,HIGH);

delayMicroseconds(10);

digitalWrite(trigpin,LOW);

duration=pulseIn(echopin,HIGH);

distance = duration*0.034/2;

delay(1000);

 
if(distance < 15 ){
          sense = 1;
}
else{
          sense = 0;
}


if (sense == 1){
  digitalWrite(La,HIGH);
  digitalWrite(Ra,HIGH);

  digitalWrite(Lb,LOW);
  digitalWrite(Rb,LOW);


  delay(1000);

  digitalWrite(La,LOW);
  digitalWrite(Rb,LOW);

  delay (1000);

  sense = 0;
}

else{}



Serial.println(distance);

//delay(100);

}







