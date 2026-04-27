#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

// Create an ADXL345 sensor object
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);

  // Check if the accelerometer is detected
  if (!accel.begin()) {
    Serial.println("Could not find ADXL345 sensor, check wiring!");
    while (1);
  }

  Serial.println("ADXL345 Accelerometer Found!");
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);

  // Print accelerometer data
  Serial.print("X: ");
  Serial.print(event.acceleration.x);
  Serial.print(" m/s^2, Y: ");
  Serial.print(event.acceleration.y);
  Serial.print(" m/s^2, Z: ");
  Serial.print(event.acceleration.z);
  Serial.println(" m/s^2");

  delay(500); // Delay for readability
}