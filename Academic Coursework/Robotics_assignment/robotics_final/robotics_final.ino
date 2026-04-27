#include <Servo.h>
#include <PS2X_lib.h>

PS2X ps2x;
Servo servo1, servo2, servo3;

int error = 0; 
byte vibrate = 0;
int angle1 = 90;
int angle2 = 90;
int angle3 = 90;

void setup() {
  Serial.begin(9600);
  
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);

  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);

  error = ps2x.config_gamepad(10,12,11,13, false, false);
  
  if(error == 0) Serial.println("Controller Connected");
  else Serial.println("Controller Error");
}

void loop() {
  ps2x.read_gamepad(false, vibrate);

  // Servo1 control with UP and DOWN
  if(ps2x.Button(PSB_PAD_RIGHT)) {
    angle1 = constrain(angle1 + 1, 0, 180);
    servo1.write(angle1);
    Serial.print("Servo1 Angle: ");
    Serial.println(angle1);
  }
  if(ps2x.Button(PSB_PAD_LEFT)) {
    angle1 = constrain(angle1 - 1, 0, 180);
    servo1.write(angle1);
    Serial.print("Servo1 Angle: ");
    Serial.println(angle1);
  }

  // Servo2 control with R1 and R2 (SWAPPED)
  if(ps2x.Button(PSB_R2)) {
    angle2 = constrain(angle2 + 1, 0, 180);
    servo2.write(angle2);
    Serial.print("Servo2 Angle: ");
    Serial.println(angle2);
  }
  if(ps2x.Button(PSB_R1)) {
    angle2 = constrain(angle2 - 1, 0, 180);
    servo2.write(angle2);
    Serial.print("Servo2 Angle: ");
    Serial.println(angle2);
  }

  // Servo3 control with L1 and L2
  if(ps2x.Button(PSB_L1)) {
    angle3 = constrain(angle3 + 1, 0, 180);
    servo3.write(angle3);
    Serial.print("Servo3 Angle: ");
    Serial.println(angle3);
  }
  if(ps2x.Button(PSB_L2)) {
    angle3 = constrain(angle3 - 1, 0, 180);
    servo3.write(angle3);
    Serial.print("Servo3 Angle: ");
    Serial.println(angle3);
  }

  // Reset all servos to 90 degrees when Triangle is pressed
  if(ps2x.ButtonPressed(PSB_GREEN)) {
    angle1 = angle2 = angle3 = 90;
    servo1.write(angle1);
    servo2.write(angle2);
    servo3.write(angle3);
    Serial.println("All Servos reset to 90 degrees");
  }

  delay(20); // smoother movement while holding
}
