#pragma once
#include "Adafruit_VL53L0X.h"
// #include "MIDIUSB.h"
// #include "MovingAverage.h"
//#include <Ramp.h> 
#define HIGHEST_RANGE_MM 400
#define LOWEST_RANGE_MM 50
#define CONTROLER_LSB 46
#define CONTROLER_MSB 14

class distancePB{
  public:
    distancePB();
    bool begin();
    void update();
    // void sendController();
    void sendMeasure();
    void restart();
    uint16_t ControllerValue;
    bool testing;
    uint8_t RangeStatus;
  private:
    Adafruit_VL53L0X distance;
    VL53L0X_RangingMeasurementData_t measure;
    const int filterAmount = 5;
    // MovingAverage filter;
    // rampInt line;
    byte channel = 0;
    bool inRange;
};
