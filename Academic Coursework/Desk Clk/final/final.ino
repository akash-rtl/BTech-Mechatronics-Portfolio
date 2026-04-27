#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ctime>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char *ssid = "Dark Matter";
const char *password = "omdinesh";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800); // 19800 seconds is 5.5 hours (IST)

enum DisplayState {
  SHOWING_JAI_SHREE_RAM,
  SHOWING_TIME_AND_DATE
};

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

void displayJaiShreeRam() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE); // Set to white
  
  display.setCursor(10, 0);
  display.print("Jai Shree");
  display.setCursor(45, 16);
  display.println("Ram");
  display.display();
}

void loop() {
  static DisplayState currentState = SHOWING_JAI_SHREE_RAM;
  static unsigned long lastTransitionMillis = 0;

  unsigned long currentMillis = millis();

  if (currentState == SHOWING_JAI_SHREE_RAM) {
    displayJaiShreeRam();
    if (currentMillis - lastTransitionMillis >= 2000) {
      currentState = SHOWING_TIME_AND_DATE;
      lastTransitionMillis = currentMillis;
    }
  }
else if (currentState == SHOWING_TIME_AND_DATE) {
    timeClient.update();
    time_t epochTime = timeClient.getEpochTime();  // Store the epoch time in a variable
    struct tm *p_tm = localtime(&epochTime);  // Use the variable with localtime
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(15, 0);
    display.print(timeClient.getFormattedTime());

    display.setTextSize(1);
    display.setCursor(35, 22);
    display.print(p_tm->tm_mday);
    display.print("/");
    display.print(p_tm->tm_mon + 1);
    display.print("/");
    display.println(p_tm->tm_year + 1900);
    
    if (currentMillis - lastTransitionMillis >= 5000) {
      currentState = SHOWING_JAI_SHREE_RAM;
      lastTransitionMillis = currentMillis;
    }
}

  display.display();
  delay(1000); // Adjust the delay to control the update rate
}
