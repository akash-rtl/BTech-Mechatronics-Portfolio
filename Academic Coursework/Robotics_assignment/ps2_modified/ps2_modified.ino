#include "PS2X_lib.h"  //for v1.6

PS2X ps2x; // create PS2 Controller Class

int error = 0; 
byte type = 0;
byte vibrate = 0;

void setup(){
  Serial.begin(115200);
  
  error = ps2x.config_gamepad(10,12,11,13, false, false);   // setup pins: clock, command, attention, data
  
  if(error == 0){
    Serial.println("Found Controller, configured successfully");
  }
  else if(error == 1)
    Serial.println("No controller found, check wiring");
  else if(error == 2)
    Serial.println("Controller found but not accepting commands");
  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode");
   
  type = ps2x.readType(); 
  switch(type) {
    case 0: Serial.println("Unknown Controller type"); break;
    case 1: Serial.println("DualShock Controller Found"); break;
    case 2: Serial.println("GuitarHero Controller Found"); break;
  }
}

void loop(){
    ps2x.read_gamepad(false, vibrate); // read controller input
    
    if(ps2x.Button(PSB_START)) 
      Serial.println("Start is being held");
      
    if(ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");
      
    if(ps2x.Button(PSB_PAD_UP)) 
      Serial.println("UP is being held");
      
    if(ps2x.Button(PSB_PAD_RIGHT))
      Serial.println("Right is being held");
      
    if(ps2x.Button(PSB_PAD_LEFT))
      Serial.println("LEFT is being held");
      
    if(ps2x.Button(PSB_PAD_DOWN))
      Serial.println("DOWN is being held");
      
    if(ps2x.NewButtonState()) {
        if(ps2x.Button(PSB_L3))
          Serial.println("L3 pressed");
        if(ps2x.Button(PSB_R3))
          Serial.println("R3 pressed");
        if(ps2x.Button(PSB_L2))
          Serial.println("L2 pressed");
        if(ps2x.Button(PSB_R2))
          Serial.println("R2 pressed");
    }

    if(ps2x.ButtonPressed(PSB_RED))
          Serial.println("Circle just pressed");
    if(ps2x.ButtonReleased(PSB_RED))
          Serial.println("Circle just released");

    if(ps2x.ButtonPressed(PSB_PINK))
          Serial.println("Square just pressed");
    if(ps2x.ButtonReleased(PSB_PINK))
          Serial.println("Square just released");

    if(ps2x.ButtonPressed(PSB_GREEN))
          Serial.println("Triangle just pressed");
    if(ps2x.ButtonReleased(PSB_GREEN))
          Serial.println("Triangle just released");

    if(ps2x.ButtonPressed(PSB_BLUE))
          Serial.println("X just pressed");
    if(ps2x.ButtonReleased(PSB_BLUE))
         Serial.println("X just released");

    if(ps2x.Button(PSB_L1)) 
        Serial.println("L1 is being held");

    if(ps2x.Button(PSB_R1)) 
        Serial.println("R1 is being held");

    delay(50);
}
