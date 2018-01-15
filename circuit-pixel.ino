#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <SPI.h>

#define PIN 12
#define LIGHT_INPUT  A5
#define SOUND_INPUT  A4

int totalPixels = 56;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(totalPixels, PIN, NEO_GRB + NEO_KHZ800);

uint32_t cobalt = pixels.Color(0, 2, 8);
uint32_t sherbet = pixels.Color(40, 2, 0);
uint32_t periwinkle = pixels.Color(2, 0, 80);
uint32_t salmon = pixels.Color(80, 0, 20);
uint32_t aqua = pixels.Color(0, 80, 20, 0);
uint32_t magenta = pixels.Color(80, 0, 20);
uint32_t lime = pixels.Color(20, 127, 0);
uint32_t pomengranite = pixels.Color(127, 0, 2);
uint32_t lemon = pixels.Color(127, 80, 0);

uint32_t colors[] = {cobalt, sherbet, periwinkle, salmon, aqua, magenta, lime, pomengranite, lemon, magenta, lime, pomengranite, lemon};

void setup() {
  Serial.begin(115200);
  CircuitPlayground.begin();
  pixels.begin();
}

void loop() {
  uint8_t wait = 100;

  uint16_t light = analogRead(LIGHT_INPUT);
  light = light * 9 / 800;

  uint16_t sound = 0;
  for (uint16_t i = 0; i < 10; i++) {
    uint16_t x = analogRead(SOUND_INPUT);
    if (x <  330) {
      x = 330;
    }
    if (x >  345) {
      x = 800;
    }
    sound += x;
    delay(wait);
  }
  sound = (sound / 10);
  sound = sound * 9 / 800;

  // light reading: darkness = 30; flashlight at sensor = 800;
  Serial.println("Light reading:");
  Serial.println(light, DEC);

  // sound reading: quiet = 340; conversation = 480; disco = 800
  Serial.println("Sound reading:");
  Serial.println(sound, DEC);

  uint32_t target = (light + sound) / 2;
  if (target > 10) {
    target = 10;
  }

  Serial.println("Target:");
  Serial.println(target);
  colorWipe(colors[target]);
}

void colorWipe(uint32_t color) {
  uint8_t wait = 10;

  // color the lights on the Circuit Playground
  for (uint16_t i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, color);
    delay(wait);
  }

  // color the pixels
  for (uint16_t i = 0; i < totalPixels; i++) {
    pixels.setPixelColor(i, color);
    pixels.show();
    delay(wait);
  }
}
