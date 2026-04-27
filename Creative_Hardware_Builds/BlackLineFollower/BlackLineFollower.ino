  int m1a = 5 ;//LEFT
  int m1b = 6 ;
  int m2a = 9;
  int m2b = 8; 

  int sL = 12;
  int sR = 13;



void setup() {
  // put your setup code here, to run once:

 

  pinMode(m1a, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m2b, OUTPUT);

  //pinMode(7, OUTPUT);
  //pinMode(6, OUTPUT);

  pinMode(sL, INPUT);
  pinMode(sR, INPUT);

}

void loop() {


/*  digitalWrite(m2a, HIGH);
  digitalWrite(m2b , LOW);
  delay (1000);
*/

/* if (sL == 0 && sR == 0){

    digitalWrite(m1a, HIGH);
    digitalWrite(m2a, HIGH);
    digitalWrite(m1a, LOW);
    digitalWrite(m1a, LOW);
    
    }
 */

 // val = digitalRead(11);


if((digitalRead(sR) == HIGH) && (digitalRead(sL) == HIGH) ){

  digitalWrite(m1a, HIGH);
  digitalWrite(m2a, HIGH);
  delay (100);
  }

else if((digitalRead(sR) == LOW) && (digitalRead(sL) == HIGH)) {
  
  digitalWrite(m1a, HIGH);
  digitalWrite(m2a, LOW);
  delay (100);
  }

else if((digitalRead(sR) == HIGH) && (digitalRead(sL) == LOW)) {
  
  digitalWrite(m1a, LOW);
  digitalWrite(m2a, HIGH);
  delay (100);
  }

else{
  }
   
  // put your main code here, to run repeatedly:
 
}
