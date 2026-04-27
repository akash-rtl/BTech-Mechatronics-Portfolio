/*
pin diagram  [ GND ] [ VCC ] [ DQ ]  


*/

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4  // ESP32 "D4" = GPIO4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin();
  sensors.setResolution(12);      // 9..12 (12 = ~750ms conversion)
  sensors.setWaitForConversion(true);

  Serial.print("Devices found: ");
  Serial.println(sensors.getDeviceCount());

}

void loop() {
  sensors.requestTemperatures();
  float t = sensors.getTempCByIndex(0);
  Serial.println(t);              // prints °C
  delay(1000);
}
