#ifndef HUB08_PANEL_H
#define HUB08_PANEL_H

#include <Arduino.h>
#include <Adafruit_GFX.h>

#ifndef PANEL_WIDTH
#define PANEL_WIDTH 64
#endif

#ifndef PANEL_HEIGHT
#define PANEL_HEIGHT 32
#endif

class HUB08Panel : public Adafruit_GFX {
public:
  HUB08Panel(uint8_t pinA, uint8_t pinB, uint8_t pinC, uint8_t pinD,
             uint8_t pinLat, uint8_t pinOe, uint8_t pinClk,
             uint8_t pinR1, uint8_t pinR2);
  
  void begin();
  void drawPixel(int16_t x, int16_t y, uint16_t color) override;
  void scan();
  void clearBuffer();
  void setBrightness(uint8_t brightness);
  void printCentered(String text, int y);

  uint8_t displayBuffer[PANEL_WIDTH * PANEL_HEIGHT / 8];
  uint8_t brightnessLevel;

private:
  uint8_t _pinA, _pinB, _pinC, _pinD;
  uint8_t _pinLat, _pinOe, _pinClk;
  uint8_t _pinR1, _pinR2;
};

#endif
