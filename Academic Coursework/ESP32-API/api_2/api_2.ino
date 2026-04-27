#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  WiFi.begin("Dark Matter", "omdinesh");
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient client;
    client.begin("https://v2.jokeapi.dev/joke/Any?type=single");
    int httpCode = client.GET();

    if (httpCode > 0) {
      String payload = client.getString();
      Serial.println("\nStatus code: " + String(httpCode));

      // Parse the JSON response
      StaticJsonDocument<2048> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        const char* joke = doc["joke"]; // Extract the joke
        Serial.println("Joke: " + String(joke));
      } else {
        Serial.println("Error parsing JSON: " + String(error.c_str()));
      }
    } else {
      Serial.println("Error on HTTP request...");
    }

    client.end();
  }

  delay(20000);
}
