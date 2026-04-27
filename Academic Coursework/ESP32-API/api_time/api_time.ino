//Time API - URL: https://www.timeapi.io/api/Time/current/zone?timeZone=Asia/Kolkata
//{"year":2024,"month":7,"day":6,"hour":14,"minute":35,"seconds":29,"milliSeconds":746,"dateTime":"2024-07-06T14:35:29.7461841","date":"07/06/2024","time":"14:35","timeZone":"Asia/Kolkata","dayOfWeek":"Saturday","dstActive":false}




#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define ssid "Dark Matter"
#define password "omdinesh"

String URL = "https://www.timeapi.io/api/Time/current/zone?timeZone=Asia/Kolkata";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  Serial.print("Connecting to WiFi");

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected to WIFI");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());


}

void loop() {
  // put your main code here, to run repeatedly:

if(WiFi.status() == WL_CONNECTED){

  HTTPClient client;

  client.begin(URL);

  int httpcode = client.GET();

  if(httpcode > 0){
    Serial.println("\nStatus: "+String(httpcode));
    
    String Jsondata = client.getString();

    // Serial.println(Jsondata);

    StaticJsonDocument<2048> doc;
    DeserializationError error = deserializeJson(doc, Jsondata);

    if(!error){
      const char* date = doc["date"];
      const char* time = doc["time"];
      const char* day = doc["dayOfWeek"];

      Serial.println(time);
      Serial.println(date);
      Serial.println(day);

    }
    else{
      Serial.println("Error parsing Json: " + String(error.c_str()));
    }





  }

  else{
    Serial.println("Error!");
  }



  client.end();
}


delay(10000);



}
