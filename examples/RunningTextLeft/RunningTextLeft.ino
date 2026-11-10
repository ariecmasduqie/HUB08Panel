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

String pesan = "Selamat Datang di Panel P4.75 HUB08 - Mode Running Text Horizontal";
int textX = PANEL_WIDTH;
uint32_t lastScroll = 0;

void setup() {
  display.begin();
  display.setBrightness(80);
}

void loop() {
  // Scan display terus menerus
  display.scan();

  // Geser posisi teks X setiap 40 milidetik
  if (millis() - lastScroll > 40) {
    lastScroll = millis();
    textX--;

    // Jika teks sudah lewat penuh dari layar kiri, reset ke layar kanan
    if (textX < -((int)pesan.length() * 6)) {
      textX = PANEL_WIDTH;
    }

    // Render ulang buffer
    display.clearBuffer();
    display.setTextColor(1);
    
    // Teks judul di atas
    display.printCentered("INFO RUNNING", 2);

    // Running text di baris bawah
    display.setCursor(textX, 20);
    display.print(pesan);
  }
}