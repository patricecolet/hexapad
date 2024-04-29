#pragma once
#include "Adafruit_VL53L0X.h"
#include "MIDIUSB.h"
// #include "MovingAverage.h"
//#include <Ramp.h> 

class distancePB{
  public:
    distancePB();
    bool begin();
    void update();
    void sendMeasure();
    void restart();
    int velocity() ;
    void lidarNote();
    uint16_t ControllerValue;
    bool testing, playing, mesuring,lidarButton = 0;
    uint8_t RangeStatus;
    float test;
    int HighestRange, LowestRange, HighestRangeL, LowestRangeL, HighestRangeM, LowestRangeM;
  private:
    Adafruit_VL53L0X distance;
    VL53L0X_RangingMeasurementData_t measure;
    const int filterAmount = 5;
    // MovingAverage filter;
    // rampInt line;
    byte channel = 0;
    bool inRange;
};
