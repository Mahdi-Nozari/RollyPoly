#include <Arduino.h>
#include "Lights.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif



void theaterChase(Adafruit_NeoPixel &strip, uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

void colorStatic(Adafruit_NeoPixel &strip, uint32_t color) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color); 
  }
  strip.show();  
}

void colorStaticCell(Adafruit_NeoPixel &strip, uint8_t num, uint32_t color) {
  for(int i=(8*(cell[num-1]-1)); i<=(8*(cell[num-1]))-1; i++) {
    strip.setPixelColor(i, color); 
  }
  strip.show();  
}

void colorPulsate(Adafruit_NeoPixel &strip, uint32_t color, int wait) {
  for(int t=0; t<=5; t++) {
    for(int a=0; a<max_brightness; a++) {
      for(int i=0; i<strip.numPixels(); i++) { 
        strip.setPixelColor(i, color);         
      }
      strip.setBrightness(a);
      strip.show();
      delay(wait);
    } 
     for(int a=max_brightness; a>0; a--) {
      for(int i=0; i<strip.numPixels(); i++) { 
        strip.setPixelColor(i, color);         
      strip.setBrightness(a);
      strip.show();
      delay(wait);
    } 
  }
  strip.setBrightness(max_brightness);  
}
}