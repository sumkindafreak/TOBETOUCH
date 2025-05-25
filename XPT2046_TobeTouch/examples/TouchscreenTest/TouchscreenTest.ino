#include <TFT_eSPI.h>
#include <XPT2046_TobeTouch.h>

TFT_eSPI tft = TFT_eSPI();
XPT2046_TobeTouch touch(32, 39, 25, 33);

void setup() {
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  touch.begin();
}

void loop() {
  if (touch.isPressed()) {
    int x = touch.getX();
    int y = touch.getY();
    Serial.printf("Touch at: %d, %d\n", x, y);
    tft.fillCircle(x, y, 4, TFT_RED);
    delay(100);
  }
}
