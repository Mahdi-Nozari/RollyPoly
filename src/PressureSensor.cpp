#include <Arduino.h>
#include <Wire.h>
#include <Vcc.h>
#include "PressureSensor.h"

// Divider: Rtop = 3.3k, Rbot = 10k
const float DIVIDER_SCALE = 10.0f / (3.3f + 10.0f);

// ADS1110 reference and scaling
const float ADS_REF = 2.048f;          // ADS1110 internal reference
const float LSB = ADS_REF / 32768.0f;  // 16-bit signed

Vcc vcc;  // Vcc measurement object

// --- Configure ADS1110 ---
void ads1110_init() {
  Wire.beginTransmission(ADS1110_ADDR);
  /*
   * Config byte:
   *  Bit7-5: Not used (0)
   *  Bit4: Conversion mode (0=continuous, 1=single-shot)
   *  Bit3-2: Data rate (00=15SPS, 01=30SPS, 10=60SPS, 11=240SPS)
   *  Bit1-0: Gain (00=1x, 01=2x, 10=4x, 11=8x)
   *
   * Config: 0b10001100 = 0x8C
   *  Single-shot, 240SPS, Gain=1
   */
  Wire.write(0x8C);
  Wire.endTransmission();
}

// --- Read raw voltage from ADS1110 ---
float readADS1110() {
  Wire.requestFrom(ADS1110_ADDR, 2);
  if (Wire.available() == 2) {
    byte highByte = Wire.read();
    byte lowByte = Wire.read();
    int16_t adc_value = (int16_t)((highByte << 8) | lowByte);  
    float voltage = (float)adc_value * (2.048 / 32768.0);
    return voltage;
  }
  return NAN;
}

// --- Convert to pressure (kPa absolute) ---
float readPressure_kPa() {
  float Vadc = readADS1110();
  if (isnan(Vadc)) return NAN;

  float Vcc_meas = vcc.Read_Volts();       // supply measurement
  float Vsensor = Vadc / DIVIDER_SCALE;    // undo divider

  // MPXH6400A transfer function:
  // Vout = Vs * (0.002421*P + 0.047)
  float P_kPa = (Vsensor / Vcc_meas + 0.047f) / 0.002421f;
  return P_kPa;
}