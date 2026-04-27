#define trigpin1 D2
#define echopin1 D1

#define trigpin2 D6
#define echopin2 D5

long duration1;
int distance1;

long duration2;
int distance2;


void setup(){

pinMode(trigpin1,OUTPUT);
pinMode(echopin1,INPUT);

pinMode(trigpin2,OUTPUT);
pinMode(echopin2,INPUT);

Serial.begin(9600);


pinMode(D3,OUTPUT);
pinMode(D4,OUTPUT);
pinMode(D7,OUTPUT);

digitalWrite(D7, HIGH);
digitalWrite(D3, HIGH);
digitalWrite(D4, HIGH);

}

void loop(){



digitalWrite(trigpin1,HIGH);
delayMicroseconds(10);
digitalWrite(trigpin1,LOW);
duration1=pulseIn(echopin1,HIGH);
distance1 = duration1*0.034/2;
Serial.print("First: ");
Serial.println(distance1);
delay(200);

digitalWrite(trigpin2,HIGH);
delayMicroseconds(10);
digitalWrite(trigpin2,LOW);
duration2=pulseIn(echopin2,HIGH);
distance2 = duration2*0.034/2;
delay(200);
Serial.print("Second: ");
Serial.println(distance2);
delay(200);

}