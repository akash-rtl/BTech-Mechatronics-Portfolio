#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "MAX30105.h"  
#include "heartRate.h"

// WiFi credentials
const char* ssid = "The Broken Empire";
const char* password = "Thorns-1";

// Endpoint (get your own from https://webhook.site)
String serverName = "https://webhook.site/802f9cc6-66c4-48f8-8c47-606c899c64bd";

// ---- Temperature (DS18B20) ----
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// ---- Heart Rate (MAX30102) ----
MAX30105 particleSensor;

// ---- Gas Sensor (MQ e.g. MQ135) ----
#define MQ_PIN 34

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  sensors.begin();

  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("MAX30102 not found. Check wiring/power.");
    while (1);
  }
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);
}

void loop() {
  // --- Temp ---
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);

  // --- Heart rate (simple IR) ---
  long irValue = particleSensor.getIR();
  int bpm = 0;
  if (checkForBeat(irValue)) {
    bpm = random(70, 90); // placeholder logic (replace with real avg if needed)
  }

  // --- Gas ---
  int gasValue = analogRead(MQ_PIN);

  // --- JSON ---
  StaticJsonDocument<200> doc;
  doc["temperature"] = temperatureC;
  doc["heartrate"] = bpm;
  doc["gas"] = gasValue;

  String requestBody;
  serializeJson(doc, requestBody);

  // --- Send POST ---
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(requestBody);

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.println("Sent JSON: " + requestBody);

    http.end();
  }

  delay(5000); // practical delay (5s between posts)
}
