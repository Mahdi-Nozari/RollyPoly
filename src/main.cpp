#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <TimerOne.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include "PressureSensor.h"
#include "Init.h"
#include "Lights.h"


Adafruit_NeoPixel lights(LED_COUNT, LED_IN, NEO_GRB + NEO_KHZ800);

// controller values
float Kp = 20, Ki = 6, Kd = 0.5;
float setpoint = 110; //kPa
float Ts = 0.05; //s

// Errors
float e_k = 0, e_k1 = 0, e_k2 = 0;

// Output
float u_k = 0, u_k1 = 0;
volatile bool controlFlag = false;
volatile float pressure = 0.0;
void controlISR(){
  controlFlag=true;
}


void setup() {
  Serial.begin(115200);
  initPins();             //Initialize GPIO
  initSensors();          //Initialize IMU and PressureSensor
  lights.begin();
  lights.show();
  lights.setBrightness(max_brightness);

  theaterChase(lights, lights.Color(255, 0, 0), 50);
  lights.clear();
  lights.show();
  delay(2000);

  Timer1.initialize(20000);
  Timer1.attachInterrupt(controlISR);
}

void loop() {
//  float P = readPressure_kPa();
//  if (!isnan(P)) {
//    Serial.println(P, 2);
//  } else {
//    Serial.println("ADC read error");
//  }

//  delay(10); // 100 Hz update rate
  if (controlFlag) {
    controlFlag = false;
    pressure = readPressure_kPa();
    e_k = setpoint - pressure;
    u_k =   u_k1
        + Kp * (e_k - e_k1)
        + Ki * Ts * e_k
        + (Kd / Ts) * (e_k - 2 * e_k1 + e_k2);

    if (u_k > 255) u_k = 255;
    if (u_k < 0)   u_k = 0;

    analogWrite(PUMP1, int(u_k));
    analogWrite(PUMP2, int(u_k));
    Serial.print(">");
    Serial.print("P: ");
    Serial.print(pressure, 2);
    Serial.print(",");
    Serial.print("u: ");
    Serial.println(int(u_k));
    e_k2 = e_k1;
    e_k1 = e_k;
    u_k1 = u_k;
  }
}
