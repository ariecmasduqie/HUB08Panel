# HUB08Panel Library

Library custom untuk panel LED Matrix P4.75 / P10 HUB08 single color (64x32) berbasis ESP8266/ESP32, diekstrak dari project standalone.

## Cara Instalasi
1. Ekstrak folder `HUB08Panel` ke dalam direktori `Arduino/libraries/` di komputer Anda, atau masukkan folder `src` langsung ke project PlatformIO / Arduino IDE Anda.
2. Pastikan library `Adafruit_GFX` sudah terinstall.

## Penggunaan Singkat
```cpp
#include <HUB08Panel.h>

HUB08Panel display(12, 16, 2, 3, 0, 15, 14, 13, 5); // PIN_A, B, C, D, LAT, OE, CLK, R1, R2

void setup() {
  display.begin();
}

void loop() {
  display.scan(); // Harus dipanggil terus menerus di loop
}
```
