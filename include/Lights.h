#ifndef LIGHTS_H
#define LIGHTS_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

void theaterChase(Adafruit_NeoPixel &strip, uint32_t color, int wait);
void colorStatic(Adafruit_NeoPixel &strip, uint32_t color);
void colorStaticCell(Adafruit_NeoPixel &strip, uint8_t num, uint32_t color);
void colorPulsate(Adafruit_NeoPixel &strip, uint32_t color, int wait);

const uint8_t cell[12] = {12, 11, 10, 9, 8, 7, 6, 5, 3, 2, 1, 4};     //Order of LED cells
#define max_brightness 100

#endif 