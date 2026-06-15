# Merilnik-zvoka
**Kratek opis**

Za nalogo sva izdelala merilnik zvoka z uporabo zvočnega senzorja KY-038, ki vsebuje kondenzatorski mikrofon za zaznavanje zvočnih valovov. Uporabila sva tudi mikrokrmilnik Arduino NANO.
Merilnik deluje na principu znočnega senzorka KY-038, ki preko mikrofona zaznava zvočne valove, na to oddaja analogni signal, katerega ojačevalnik procesira in dobimo digita output.

**Komponente in kosovnica**

KY-038 Merilnik zvoka (1x), Arduino NANO (1x), LCD zaslon (1x), Potenciometer (1x), Upor 22kE (1x), Ploščica za povezovanje (1x), Stikalo (1x), 9V baterija (1x) in priključek (1x).



![kosovnica](Kosovnica.png)



**Slika vezja v programu Easy EDA**


![Vezava](Vezava.png)



**Arduino koda**



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




**Slika ohišja v programu Onshape**


<img width="810" height="525" alt="image" src="https://github.com/user-attachments/assets/7f71c189-be7f-4e89-9af2-52752e3ed8f6" />





**Slika pokrova za ohišje v programu Onshape**


<img width="810" height="525" alt="image" src="https://github.com/user-attachments/assets/9e2a6ada-86de-4e1e-b16c-73979a433824" />






**Video delovanja**


**Končne slike delovanja**


**Komentar na delovanje**


**Prednosti**


**Omejitve**


**Ocena natančnosti delovanja**


**Primerjava**


**Zaključek**


