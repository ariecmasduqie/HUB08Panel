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

String pesan = " >>> Running Text Bergerak ke Kanan >>> ";
int textWidth = 0;
int textX = 0;
uint32_t lastScroll = 0;

void setup() {
  display.begin();
  display.setBrightness(80); // Atur tingkat kecerahan LED

  // Hitung total lebar teks dalam piksel (1 karakter = 6 piksel termasuk spasi)
  textWidth = pesan.length() * 6;
  
  // Posisi awal dimulai dari luar sebelah kiri layar
  textX = -textWidth;
}

void loop() {
  // PANGGILAN WAJIB: Scan multiplexing LED terus menerus
  display.scan();

  // Geser posisi teks ke kanan setiap 40 milidetik
  if (millis() - lastScroll > 40) {
    lastScroll = millis();
    textX++; // Nilai bertambah (increment) agar teks bergeser ke kanan

    // Jika ujung teks sudah melewati batas kanan panel, reset kembali ke kiri luar layar
    if (textX > PANEL_WIDTH) {
      textX = -textWidth;
    }

    // Render ulang buffer display
    display.clearBuffer();
    display.setTextColor(1);
    
    // Teks statis di baris atas
    display.printCentered("MODE", 2);

    // Running text berjalan ke kanan di baris bawah (y = 20)
    display.setCursor(textX, 20);
    display.print(pesan);
  }
}