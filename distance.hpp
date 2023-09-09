#include "Adafruit_VL53L0X.h"
#include "MIDIUSB.h"
#include "MovingAverage.h"
//#include <Ramp.h> 
#define HIGHEST_RANGE_MM 400
#define LOWEST_RANGE_MM 50
#define CONTROLER_LSB 46
#define CONTROLER_MSB 14

class distancePB{
  public:
    distancePB(byte);
    bool begin();
    void update();
    void sendController();
    void sendMeasure();
    void restart();
    uint16_t ControllerValue;
    bool testing;
  private:
    Adafruit_VL53L0X distance;
    const int filterAmount = 5;
    MovingAverage filter;
//    rampInt line;
    byte _channel;
    VL53L0X_RangingMeasurementData_t measure;
    bool inRange;
};
