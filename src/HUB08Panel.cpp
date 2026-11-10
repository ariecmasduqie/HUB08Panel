#include "HUB08Panel.h"

HUB08Panel::HUB08Panel(uint8_t pinA, uint8_t pinB, uint8_t pinC, uint8_t pinD,
                       uint8_t pinLat, uint8_t pinOe, uint8_t pinClk,
                       uint8_t pinR1, uint8_t pinR2)
  : Adafruit_GFX(PANEL_WIDTH, PANEL_HEIGHT),
    _pinA(pinA), _pinB(pinB), _pinC(pinC), _pinD(pinD),
    _pinLat(pinLat), _pinOe(pinOe), _pinClk(pinClk),
    _pinR1(pinR1), _pinR2(pinR2),
    brightnessLevel(100) {
  memset(displayBuffer, 0, sizeof(displayBuffer));
}

void HUB08Panel::begin() {
  pinMode(_pinA, OUTPUT);
  pinMode(_pinB, OUTPUT);
  pinMode(_pinC, OUTPUT);
  pinMode(_pinD, OUTPUT);
  pinMode(_pinLat, OUTPUT);
  pinMode(_pinOe, OUTPUT);
  pinMode(_pinClk, OUTPUT);
  pinMode(_pinR1, OUTPUT);
  pinMode(_pinR2, OUTPUT);

  digitalWrite(_pinOe, HIGH);

  setTextWrap(false);
  setTextSize(1);
  setFont(NULL);
}

void HUB08Panel::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if (x < 0 || x >= PANEL_WIDTH || y < 0 || y >= PANEL_HEIGHT) return;
  int index = (y * PANEL_WIDTH + x) / 8;
  uint8_t bit = 1 << (7 - (x % 8));
  if (color) {
    displayBuffer[index] |= bit;
  } else {
    displayBuffer[index] &= ~bit;
  }
}

void HUB08Panel::clearBuffer() {
  memset(displayBuffer, 0, sizeof(displayBuffer));
}

void HUB08Panel::setBrightness(uint8_t brightness) {
  brightnessLevel = brightness;
}

void HUB08Panel::printCentered(String text, int y) {
  setFont(NULL);
  setTextSize(1);
  int textWidth = text.length() * 6;
  int posX = (PANEL_WIDTH - textWidth) / 2;
  setCursor(posX, y);
  print(text);
}

void HUB08Panel::scan() {
  for (uint8_t line = 0; line < 16; line++) {
    digitalWrite(_pinOe, HIGH);
    delayMicroseconds(2);

    for (int8_t col = 0; col < PANEL_WIDTH; col++) {
      digitalWrite(_pinClk, LOW);

      int idxR1 = (line * PANEL_WIDTH + col) / 8;
      int idxR2 = ((line + 16) * PANEL_WIDTH + col) / 8;
      uint8_t bitMask = 1 << (7 - (col % 8));

      bool valR1 = (displayBuffer[idxR1] & bitMask);
      bool valR2 = (displayBuffer[idxR2] & bitMask);

      digitalWrite(_pinR1, valR1 ? HIGH : LOW);
      digitalWrite(_pinR2, valR2 ? HIGH : LOW);

      digitalWrite(_pinClk, HIGH);
    }

    digitalWrite(_pinA, (line & 0x01) ? HIGH : LOW);
    digitalWrite(_pinB, (line & 0x02) ? HIGH : LOW);
    digitalWrite(_pinC, (line & 0x04) ? HIGH : LOW);
    digitalWrite(_pinD, (line & 0x08) ? HIGH : LOW);

    digitalWrite(_pinLat, HIGH);
    delayMicroseconds(1);
    digitalWrite(_pinLat, LOW);

    digitalWrite(_pinOe, LOW);
    delayMicroseconds(brightnessLevel);
  }

  digitalWrite(_pinOe, HIGH);
}
