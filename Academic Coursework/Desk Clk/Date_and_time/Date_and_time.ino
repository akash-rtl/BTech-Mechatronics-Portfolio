#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char *ssid = "Dark Matter";
const char *password = "omdinesh";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800); // 19800 seconds is 5.5 hours (IST)

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  display.display();
  delay(2000);

  display.clearDisplay();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  //configTime(19800, 0, "pool.ntp.org");
  configTime(0, 0, "pool.ntp.org");  // Manually set the time zone offset
  // Use "in.pool.ntp.org" for Indian NTP server

  timeClient.begin();
}

void loop() {
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *p_tm = localtime((const time_t *)&epochTime);

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 0);
  //display.print("Time: ");
  display.print(p_tm->tm_hour);
  display.print(":");
  if (p_tm->tm_min < 10)
    display.print("0");
  display.print(p_tm->tm_min);
  display.print(":");
  
  if (p_tm->tm_sec < 10)
    display.print("0");
  display.println(p_tm->tm_sec);
  
  display.setTextSize(1);
  display.setCursor(35, 22);
  //display.print("Date: ");
  display.print(p_tm->tm_mday);
  display.print("/");
  display.print(p_tm->tm_mon + 1);
  display.print("/");
  display.println(p_tm->tm_year + 1900);

  display.display();
  delay(1000);
}
