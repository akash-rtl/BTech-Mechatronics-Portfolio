#define MQ135_PIN 34  // Use an ADC pin

void setup() {
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(MQ135_PIN);  
  float voltage = sensorValue * (3.3 / 4095.0); // Convert to voltage (ESP32 ADC = 12-bit)
  
  Serial.print("MQ135 Raw: ");
  Serial.print(sensorValue);
  Serial.print(" | Voltage: ");
  Serial.println(voltage);

  delay(1000);
}
