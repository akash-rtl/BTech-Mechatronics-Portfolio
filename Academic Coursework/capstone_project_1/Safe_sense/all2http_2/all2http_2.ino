#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "MAX30105.h"
#include "heartRate.h"

// ---------------- WiFi ----------------
const char* ssid = "The Broken Empire";
const char* password = "Thorns-1";

// Endpoint (get your own from https://webhook.site)

String serverName = "https://safesense.requestcatcher.com/test";

// String serverName = "https://safesense.free.beeceptor.com";

// String serverName = "https://webhook.site/802f9cc6-66c4-48f8-8c47-606c899c64bd"; // Replace with your cloud endpoint

// ---------------- Temperature (DS18B20) ----------------
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// ---------------- Gas Sensor (MQ135) ----------------
#define MQ135_PIN 34

// ---------------- Heart Rate (MAX30102) ----------------
MAX30105 particleSensor;
long irValue;
byte rates[4];        // rolling average array
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;

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

  // Heart Rate
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("MAX30102 not found. Check wiring!");
    while (1);
  }
  particleSensor.setup();  
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);
}

// ---------------- Main Loop ----------------
void loop() {
  // Temperature
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  // Gas
  int gasValue = analogRead(MQ135_PIN);

  // Heart Rate
  irValue = particleSensor.getIR();
  if (checkForBeat(irValue)) {
    long delta = millis() - lastBeat;
    lastBeat = millis();
    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20) {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= 4;

      beatAvg = 0;
      for (byte x = 0; x < 4; x++) beatAvg += rates[x];
      beatAvg /= 4;
    }
  }

  // Print locally
  Serial.print("Temp: ");
  Serial.print(tempC);
  Serial.print(" °C | Gas: ");
  Serial.print(gasValue);
  Serial.print(" | IR: ");
  Serial.print(irValue);
  Serial.print(" | BPM: ");
  Serial.print(beatsPerMinute);
  Serial.print(" | Avg BPM: ");
  Serial.println(beatAvg);

  // Send to cloud
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String httpRequestData = "{\"temperature\":" + String(tempC) +
                             ",\"gas\":" + String(gasValue) +
                             ",\"ir\":" + String(irValue) +
                             ",\"bpm\":" + String(beatsPerMinute) +
                             ",\"avg_bpm\":" + String(beatAvg) + "}";

    int httpResponseCode = http.POST(httpRequestData);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(100); // practical delay for stability
}
