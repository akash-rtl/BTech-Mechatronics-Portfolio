#include <LiquidCrystal.h>
#include <PulseSensorPlayground.h>

const int PulseWire = A0;
const int LED = 13;
int Threshold = 550;

PulseSensorPlayground pulseSensor;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);  // set up the LCD's number of columns and rows

  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED);
  pulseSensor.setThreshold(Threshold);

  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");
  }
}

void loop() {
  if (pulseSensor.sawStartOfBeat()) {
    int myBPM = pulseSensor.getBeatsPerMinute();
    lcd.clear();  // clear the LCD screen
    lcd.setCursor(0, 0);  // set the cursor to column 0, row 0
    lcd.print("Heartbeat!");  // Print a message to the LCD
    lcd.setCursor(0, 1);  // set the cursor to column 0, row 1
    lcd.print("BPM: ");
    lcd.print(myBPM);  // Print the BPM value to the LCD

    Serial.println("♥  A HeartBeat Happened ! ");
    Serial.print("BPM: ");
    Serial.println(myBPM);
  }

  delay(20);
}