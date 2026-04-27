#include <Servo.h> // Include the Servo library

Servo myServo1;
Servo myServo2;
Servo myServo3; // Create a servo object to control the servo motor

void setup() {
  myServo1.attach(3);
  myServo2.attach(5);
  myServo3.attach(6);
     // Attach the servo to pin 9
  myServo1.write(90);
  myServo2.write(90);
  myServo3.write(90);
  
   // Start at the neutral position (90 degrees)
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  Serial.println("Enter a number between 0 and 180:");
}

void loop() {
  if (Serial.available() > 0) {
    String rawInput = Serial.readStringUntil('\n'); // Read until a newline character
    Serial.print("Raw Input: \"");
    Serial.print(rawInput);
    Serial.println("\"");

    int angle = rawInput.toInt(); // Try converting the whole string to an integer

    if (angle >= 0 && angle <= 180) {
      myServo1.write(angle);
      myServo2.write(angle);
      myServo3.write(angle);
       // Move the servo to the specified angle
      Serial.print("Servo moved to: ");
      Serial.println(angle);
    } else {
      Serial.println("Invalid input. Enter a number between 0 and 180.");
    }
    delay(50); // Small delay after reading to avoid rapid re-reads
  }
}