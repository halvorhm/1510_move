#include <Adafruit_NeoPixel.h>

int stripPIN = 6;
int ledCount = 11;

int third = 33 / ledCount;
int twothirds = 66 / ledCount;

pulseCount = third;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, stripPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(9, OUTPUT);
}

void loop() {
  int i = 100;
  for(; i >= 50; i--) {
    for(int j = 0; j <= pulseCount; j++) {
      strip.setPixelColor(j, strip.Color(i, i, i));
    }
    strip.show();
  }
  for(; i <= 150; i++) {
    for(int j = 0; j <= pulseCount; j++) {
      strip.setPixelColor(j, strip.Color(i, i, i));
    }
    strip.show();
  }
  for(; i >= 100; i--) {
    for(int j = 0; j <= pulseCount; j++) {
      strip.setPixelColor(j, strip.Color(i, i, i));
    }
    strip.show();
  }
}
