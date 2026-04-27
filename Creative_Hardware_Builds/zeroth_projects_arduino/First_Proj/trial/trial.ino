void setup() {
  // put your setup code here, to run once:

 pinMode(7,OUTPUT);
 pinMode(2,INPUT); 

 digitalWrite(7,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:


  
  

  if (digitalRead(2) == HIGH){
    
    digitalWrite(7, HIGH);
    delay(500);
    
    }

   if (digitalRead(2) == HIGH && digitalRead(7) == HIGH){
    
    digitalWrite(7, LOW);
    delay(500);
    }
  
}
