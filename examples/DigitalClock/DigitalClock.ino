#include <Arduino.h>
#include <HUB08Panel.h>

#define PIN_A   12
#define PIN_B   16
#define PIN_C   2
#define PIN_D   3
#define PIN_LAT 0
#define PIN_OE  15
#define PIN_CLK 14
#define PIN_R1  13
#define PIN_R2  5

HUB08Panel display(PIN_A, PIN_B, PIN_C, PIN_D, PIN_LAT, PIN_OE, PIN_CLK, PIN_R1, PIN_R2);

// Variabel Waktu Simulasi (Bisa diganti dengan data RTC/DS1307/NTP)
int hour = 07;
int minute = 30;
int second = 0;

uint32_t lastSecond = 0;
bool showColon = true;

void setup() {
  display.begin();
  display.setBrightness(80);
}

void loop() {
  // Panggilan wajib untuk multiplexing LED
  display.scan();

  // Hitung detik & toggle kedip titik dua setiap 1000 ms
  if (millis() - lastSecond >= 1000) {
    lastSecond = millis();
    showColon = !showColon;

    second++;
    if (second >= 60) {
      second = 0;
      minute++;
      if (minute >= 60) {
        minute = 0;
        hour = (hour + 1) % 24;
      }
    }

    // Render ulang tampilan jam
    display.clearBuffer();
    display.setTextColor(1);
    display.printCentered("JAM DIGITAL", 2);

    char timeBuffer[10];
    if (showColon) {
      snprintf(timeBuffer, sizeof(timeBuffer), "%02d:%02d:%02d", hour, minute, second);
    } else {
      snprintf(timeBuffer, sizeof(timeBuffer), "%02d %02d %02d", hour, minute, second);
    }

    display.printCentered(String(timeBuffer), 18);
  }
}