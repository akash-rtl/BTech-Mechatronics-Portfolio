#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// #define ssid "Dark Matter"
// #define password "omdinesh"





void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  WiFi.begin("Dark Matter", "omdinesh");
  Serial.print("Connecting to wifi");

  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:
if(WiFi.status() == WL_CONNECTED){
    HTTPClient client;

    int a = random(1,10);

    client.begin("https://jsonplaceholder.typicode.com/comments?id="+String(a));
    int httpCode = client.GET();

    if(httpCode > 0){
      String payload = client.getString();
      Serial.println("\nStatuscode: "+ String(httpCode));
      Serial.println(payload);

    }
    else{
      Serial.println("Error on HTTP request...");

    }
}

else{
  Serial.println("Error connecting to the internet...");
}


delay(20000);

}
