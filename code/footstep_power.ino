#include <LiquidCrystal.h>

/* LCD pin configuration
   RS, EN, D4, D5, D6, D7 */
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pin definitions
const int piezoPin = A0;     // Piezo sensor output
const int ledPin   = 8;      // LED indicator

// Variables
int stepCount = 0;
int sensorValue = 0;
float voltage = 0.0;

// Threshold to detect a footstep
const int stepThreshold = 60;  

void setup() {
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Footstep Power");
  lcd.setCursor(0, 1);
  lcd.print("Generation");
  delay(2000);
  lcd.clear();
}

void loop() {
  sensorValue = analogRead(piezoPin);

  // Convert analog value to voltage
  voltage = sensorValue * (5.0 / 1023.0);

  // Detect footstep
  if (sensorValue > stepThreshold) {
    stepCount++;
    digitalWrite(ledPin, HIGH);
    delay(200);              // Debounce delay
  } else {
    digitalWrite(ledPin, LOW);
  }

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("STEP COUNT: ");
  lcd.print(stepCount);

  lcd.setCursor(0, 1);
  lcd.print("VOLTAGE: ");
  lcd.print(voltage, 2);
  lcd.print(" V ");

  delay(300);
}

