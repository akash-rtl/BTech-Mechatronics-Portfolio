//For arduino ----


#define trigpin 9
#define echopin 10



long duration;
int distance;

void setup(){

pinMode(trigpin,OUTPUT);
pinMode(echopin,INPUT);

Serial.begin(9600);


}

void loop(){



digitalWrite(trigpin,HIGH);

delayMicroseconds(10);

digitalWrite(trigpin,LOW);

duration=pulseIn(echopin,HIGH);

distance = duration*0.034/2;

Serial.print(distance);
Serial.println(" cm");
delay(200);

}
