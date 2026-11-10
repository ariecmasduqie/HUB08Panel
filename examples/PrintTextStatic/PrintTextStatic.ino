#include <Arduino.h>
#include <HUB08Panel.h>

// Definisi Pin HUB08 (Mapping ESP8266 / NodeMCU)
#define PIN_A   12  // D6
#define PIN_B   16  // D0
#define PIN_C   2   // D4
#define PIN_D   3   // RX
#define PIN_LAT 0   // D3
#define PIN_OE  15  // D8
#define PIN_CLK 14  // D5
#define PIN_R1  13  // D7
#define PIN_R2  5   // D1

HUB08Panel display(PIN_A, PIN_B, PIN_C, PIN_D, PIN_LAT, PIN_OE, PIN_CLK, PIN_R1, PIN_R2);

void setup() {
  display.begin();
  display.setBrightness(80); // Set kecerahan LED

  // Tulis teks ke buffer (cukup sekali jika statis)
  display.clearBuffer();
  display.setTextColor(1);
  display.printCentered("HUB08 PANEL", 4);    // Baris atas (y = 4)
  display.printCentered("TEXT STATIS", 18);   // Baris bawah (y = 18)
}

void loop() {
  // PANGGILAN WAJIB: scan() terus-menerus di loop untuk refresh LED
  display.scan();
}