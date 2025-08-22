#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H

#define ADS1110_ADDR 0x48    // ADS1110 default I2C address

void ads1110_init();
float readADS1110();
float readPressure_kPa();

#endif