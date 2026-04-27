#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "MAX30105.h"

// ---------------- WiFi ----------------
const char* ssid = "The Broken Empire";
const char* password = "Thorns-1";

// Endpoint
String serverName = "https://safesense.requestcatcher.com/test";

// ---------------- Temperature (DS18B20) ----------------
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// ---------------- Gas Sensor (MQ135) ----------------
#define MQ135_PIN 34

// ---------------- Heart Sensor (MAX30102) ----------------
MAX30105 particleSensor;

// ---------------- Setup ----------------
void setup() {
  Serial.begin(115200);

  // WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  // Temp
  sensors.begin();

  // MAX30102 (IR only, simple stable config)
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("MAX30102 not found. Check wiring!");
    while (1);
  }

  // Minimal, robust IR configuration
  byte ledBrightness = 0x24;  // ~12.6 mA; adjust 0x18–0x3F as needed
  byte sampleAverage = 4;     // averaging for noise reduction
  byte ledMode = 2;           // Red + IR (we’ll read IR only)
  int sampleRate = 100;       // 100 Hz
  int pulseWidth = 411;       // 16-bit resolution
  int adcRange = 4096;        // range

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
  particleSensor.setPulseAmplitudeIR(ledBrightness);
  particleSensor.setPulseAmplitudeRed(ledBrightness);
  particleSensor.setPulseAmplitudeGreen(0); // off
}

// ---------------- Main Loop ----------------
void loop() {
  // Read temperature
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  // Read gas sensor
  int gasValue = analogRead(MQ135_PIN);

  // Read IR from MAX30102
  long irValue = particleSensor.getIR();

  // Local print
  Serial.print("Temp: ");
  Serial.print(tempC, 2);
  Serial.print(" °C | Gas: ");
  Serial.print(gasValue);
  Serial.print(" | IR: ");
  Serial.println(irValue);

  // Send to cloud
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String httpRequestData = "{\"temperature\":" + String(tempC, 2) +
                             ",\"gas\":" + String(gasValue) +
                             ",\"ir\":" + String(irValue) +
                             "}";

    int httpResponseCode = http.POST(httpRequestData);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  // Loop rate: 10 Hz (adjust as needed)
  delay(100);
}
