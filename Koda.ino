#include <LiquidCrystal.h>

// LCD pini
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int sensorPin = A0;
const int sampleWindow = 50;

unsigned int sample;

// Kalibracija: dB = k * peakToPeak + n
const float k = 1.156;
const float n = 2.22;

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.print("Merilnik hrupa");
  delay(2000);
  lcd.clear();
}

void loop() {

  unsigned long startMillis = millis();

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // Vzorčenje signala
  while (millis() - startMillis < sampleWindow) {

    sample = analogRead(sensorPin);

    if (sample < 1024) {

      if (sample > signalMax) {
        signalMax = sample;
      }

      if (sample < signalMin) {
        signalMin = sample;
      }
    }
  }

  // Peak-to-peak vrednost
  unsigned int peakToPeak = signalMax - signalMin;

  // Linearna kalibracija
  double dB = k * peakToPeak + n;

  // Omejitve
  if (dB < 8) {
    dB = 8;
  }

   if (dB > 120) {
    dB = 180;
  }

  // Serial Monitor
  Serial.print("PeakToPeak: ");
  Serial.print(peakToPeak);
  Serial.print(" | Hrup: ");
  Serial.print(dB, 1);
  Serial.println(" dB");

  // LCD - prva vrstica
  lcd.setCursor(0, 0);
  lcd.print("Hrup:");
  lcd.setCursor(6, 0);
  lcd.print(dB, 1);
  lcd.print(" dB   ");

  delay(250);
}
