#include <Adafruit_NeoPixel.h>

int stripPIN = 6;
int ledCount = 11;

int third = 33 / ledCount;
int twothirds = 66 / ledCount;

int pulseCount = twothirds;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, stripPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(9, OUTPUT);
  strip.begin();
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
    strip.show();
  }
}

void loop() {
  int i = 100;
  for(; i >= 10; i--) {
    for(int j = 0; j <= pulseCount; j++) {
      strip.setPixelColor(j, strip.Color(i, i, i));
    }
    strip.show();
    delay(2);
  }
  for(; i <= 200; i++) {
    for(int j = 0; j <= pulseCount; j++) {
      strip.setPixelColor(j, strip.Color(i, i, i));
    }
    strip.show();
    delay(2);
  }
  for(; i >= 100; i--) {
    for(int j = 0; j <= pulseCount; j++) {
      strip.setPixelColor(j, strip.Color(i, i, i));
    }
    strip.show();
    delay(2);
  }
//  strip.setPixelColor(1, strip.Color(100, 0, 0));
//  strip.setPixelColor(2, strip.Color(0, 100, 0));
//  strip.setPixelColor(3, strip.Color(0, 0, 100));
//  strip.show();
}
