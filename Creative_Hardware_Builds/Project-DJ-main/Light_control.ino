char data = 'z';
String pat;









void Light_off(){
  digitalWrite(5,LOW);
}

void Light_on(){
  digitalWrite(5,HIGH);
}





void Disco_superfast(){
  
  while(true){
  digitalWrite(5,HIGH);
  delay(100);
  digitalWrite(5,LOW);
  delay(100);

  if (Serial.available()){

    if(Serial.read() == 'z' || Serial.read() == 'y'){
      
      data = 'z';
      break;
      }
    }

  }
}

void Disco_fast(){
  
  while(true){
  digitalWrite(5,HIGH);
  delay(200);
  digitalWrite(5,LOW);
  delay(200);

  if (Serial.available()){

    if(Serial.read() == 'z' || Serial.read() == 'y'){
      
      data = 'z';
      break;
      }
    }
  
  }
}



void Disco_medium(){
  
  while(true){
  digitalWrite(5,HIGH);
  delay(400);
  digitalWrite(5,LOW);
  delay(400);
  
  if (Serial.available()){

    if(Serial.read() == 'z' || Serial.read() == 'y'){
      
      data = 'z';
      break;
      }
    }
  
  }
}

void Disco_slower(){
  
  while(true){
  digitalWrite(5,HIGH);
  delay(500);
  digitalWrite(5,LOW);
  delay(500);
  
  if (Serial.available()){

    if(Serial.read() == 'z' || Serial.read() == 'y'){
      
      data = 'z';
      break;
      }
    }
  }
}

void Disco_moreslower(){
  
  while(true){
  digitalWrite(5,HIGH);
  delay(700);
  digitalWrite(5,LOW);
  delay(700);
  
  if (Serial.available()){

    if(Serial.read() == 'z' || Serial.read() == 'y'){
      
      data = 'z';
      break;
      }
    }
  }
}

void Disco_slowest(){
  
  while(true){
  digitalWrite(5,HIGH);
  delay(1000);
  digitalWrite(5,LOW);
  delay(1000);
  
  if (Serial.available()){

    if(Serial.read() == 'z' || Serial.read() == 'y'){
      
      data = 'z';
      break;
      }
    }
  }
}


























void setup() {
  // put your setup code here, to run once:

  

  Serial.begin(9600);

  pinMode(5,OUTPUT);

  
}

void loop() {
  
  

  if (Serial.available()){

    data = Serial.read();
    Serial.println(data);
    //if(pat == "" || pat == " "){}
    //else{data = pat;}    
  }
  
  

  

  //if (data == 'a'){
    //Serial.println("Detected: ");
  //}


  if (data == 'y'){
    Light_off();
  }
  else if(data == 'z'){
    Light_on();
  }
  
  
  
  else if(data == 'a'){
    
    Disco_superfast();
    data = 'z';
  }
  
  else if(data == 'b'){
    
    Disco_fast();
  }

  else if(data == 'c'){
    
    Disco_medium();
  }
  
  else if(data == 'd'){
    
    Disco_slower();
  }

  else if(data == 'e'){
    
    Disco_moreslower();
  }

  else if(data == 'f'){
    Disco_slowest();
  }

}


//---------------------------------------------------------------



