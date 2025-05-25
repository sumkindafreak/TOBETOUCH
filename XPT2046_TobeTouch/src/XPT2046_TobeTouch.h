#ifndef XPT2046_TOBETOUCH_H
#define XPT2046_TOBETOUCH_H

#include <Arduino.h>

class XPT2046_TobeTouch {
  public:
    XPT2046_TobeTouch(uint8_t mosi, uint8_t miso, uint8_t clk, uint8_t cs);
    void begin();
    bool isPressed();
    int16_t getX();
    int16_t getY();

  private:
    uint8_t _mosi, _miso, _clk, _cs;
    void spiWrite(uint8_t data);
    uint16_t spiRead16(uint8_t command);
};

#endif
