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

String line1 = "PANEL HUB08";
String line2 = "P4.75 SINGLE";

// --- PILIH DIREKSI ANIMASI ---
// 1 = Scroll ke Bawah (Top-to-Bottom)
// 2 = Scroll ke Atas (Bottom-to-Top)
int directionMode = 1; 

int scrollY = (directionMode == 1) ? -20 : PANEL_HEIGHT;
uint32_t lastScroll = 0;

void setup() {
  display.begin();
  display.setBrightness(80);
}

void loop() {
  display.scan();

  if (millis() - lastScroll > 45) {
    lastScroll = millis();

    if (directionMode == 1) { 
      // SCROLL KE BAWAH
      scrollY++;
      if (scrollY > PANEL_HEIGHT) scrollY = -20;
    } else { 
      // SCROLL KE ATAS
      scrollY--;
      if (scrollY < -20) scrollY = PANEL_HEIGHT;
    }

    display.clearBuffer();
    display.setTextColor(1);
    display.printCentered(line1, scrollY);
    display.printCentered(line2, scrollY + 10);
  }
}