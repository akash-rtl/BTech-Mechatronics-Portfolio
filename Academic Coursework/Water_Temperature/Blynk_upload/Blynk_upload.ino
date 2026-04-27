#define BLYNK_AUTH_TOKEN "XXeiIaS5ypzOLpM_UHz7n90_WSJVE3wC"
#define BLYNK_TEMPLATE_ID "TMPL3mB4JiBDq";
#define BLYNK_TEMPLATE_NAME "Water Temperature Measurement";


#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Replace with your network credentials
char ssid[] = "Dark Matter";
char pass[] = "omdinesh";

// Replace with your Blynk Auth Token
char auth[] = "XXeiIaS5ypzOLpM_UHz7n90_WSJVE3wC";

// Data wire is connected to GPIO4 on the ESP32
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature
DallasTemperature sensors(&oneWire);

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);

  // Initialize the Blynk connection
  Blynk.begin(auth, ssid, pass);

  // Start up the temperature sensor library
  sensors.begin();
}

void loop() {
  // Run Blynk
  Blynk.run();

  // Request temperature readings
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);

  // Print temperature to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  // Send temperature to Blynk (Virtual Pin V0)
  Blynk.virtualWrite(V0, temperatureC);

  // Delay before the next reading
  delay(1000);
}
