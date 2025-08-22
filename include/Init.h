#ifndef INIT_H
#define INIT_H

#include <Arduino.h>

#define VALVE1 22
#define VALVE2 23
#define VALVE3 28
#define VALVE4 34
#define VALVE5 40
#define VALVE6 46
#define VALVE7 48
#define VALVE8 49
#define VALVE9 42
#define VALVE10 47
#define VALVE11 36
#define VALVE12 32
#define PUMP1 5
#define PUMP2 4
#define LED_IN 7
#define LED_OUT 6
#define LED_COUNT 96

void initPins();
void initSensors();

#endif