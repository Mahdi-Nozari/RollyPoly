#include <Arduino.h>
#include <Wire.h>
#include "Init.h"
#include "PressureSensor.h"

void initPins() {
  pinMode(VALVE1, OUTPUT);
  digitalWrite(VALVE1, 0);
  pinMode(VALVE2, OUTPUT);
  digitalWrite(VALVE2, 0);
  pinMode(VALVE3, OUTPUT);
  digitalWrite(VALVE3, 0);
  pinMode(VALVE4, OUTPUT);
  digitalWrite(VALVE4, 0);
  pinMode(VALVE5, OUTPUT);
  digitalWrite(VALVE5, 0);
  pinMode(VALVE6, OUTPUT);
  digitalWrite(VALVE6, 0);
  pinMode(VALVE7, OUTPUT);
  digitalWrite(VALVE7, 0);
  pinMode(VALVE8, OUTPUT);
  digitalWrite(VALVE8, 0);
  pinMode(VALVE9, OUTPUT);
  digitalWrite(VALVE9, 0);
  pinMode(VALVE10, OUTPUT);
  digitalWrite(VALVE10, 0);
  pinMode(VALVE11, OUTPUT);
  digitalWrite(VALVE11, 0);
  pinMode(VALVE12, OUTPUT);
  digitalWrite(VALVE12, 0);
}

void initSensors() {
  // Initialize pressure sensor
  Wire.begin();
  ads1110_init();
}
