uint8_t buf[8] = { 0 };   //Keyboard report buffer

const int trigpin= 6 ;
const int echopin= 7;

long duration;
int distance;


void setup() {

Serial.begin(9600); // Setup Serial communication

pinMode(trigpin,OUTPUT);
pinMode(echopin,INPUT);

}

void loop() {
//When button representing W is pressed  


digitalWrite(trigpin,HIGH);

delayMicroseconds(10);

digitalWrite(trigpin,LOW);

duration=pulseIn(echopin,HIGH);

distance = duration*0.034/2;
 
  if (distance < 70){
    
    change();
    delay(300);
    }
}




void change(){
   
    
    
    buf[2] = 40;   // W keycode
    Serial.write(buf, 8); // Send keypress
    
   // Serial.println("W");
    releaseKey();
  
}


void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Send Release key  
}
