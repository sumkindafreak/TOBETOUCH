#include "XPT2046_TobeTouch.h"

XPT2046_TobeTouch::XPT2046_TobeTouch(uint8_t mosi, uint8_t miso, uint8_t clk, uint8_t cs)
  : _mosi(mosi), _miso(miso), _clk(clk), _cs(cs) {}

void XPT2046_TobeTouch::begin() {
  pinMode(_mosi, OUTPUT);
  pinMode(_miso, INPUT);
  pinMode(_clk, OUTPUT);
  pinMode(_cs, OUTPUT);
  digitalWrite(_cs, HIGH);
  digitalWrite(_clk, HIGH);
}

bool XPT2046_TobeTouch::isPressed() {
  return getX() > 0 && getY() > 0;
}

int16_t XPT2046_TobeTouch::getX() {
  return spiRead16(0xD0) >> 3;
}

int16_t XPT2046_TobeTouch::getY() {
  return spiRead16(0x90) >> 3;
}

void XPT2046_TobeTouch::spiWrite(uint8_t data) {
  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(_mosi, (data & 0x80));
    digitalWrite(_clk, LOW);
    data <<= 1;
    digitalWrite(_clk, HIGH);
  }
}

uint16_t XPT2046_TobeTouch::spiRead16(uint8_t command) {
  digitalWrite(_cs, LOW);
  spiWrite(command);
  delayMicroseconds(10);

  uint16_t result = 0;
  for (int i = 0; i < 16; i++) {
    digitalWrite(_clk, LOW);
    result <<= 1;
    if (digitalRead(_miso)) result |= 1;
    digitalWrite(_clk, HIGH);
  }

  digitalWrite(_cs, HIGH);
  return result;
}
