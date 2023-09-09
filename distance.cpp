#include "distance.hpp"

distancePB::distancePB(byte channel) : filter(filterAmount) {
  Adafruit_VL53L0X distance = Adafruit_VL53L0X();
  _channel = channel;
};

void distancePB::sendMeasure() {
      VL53L0X_RangingMeasurementData_t measure;
      uint16_t Value = 0;
//    Serial.print("Reading a measurement... ");
    distance.getRangingMeasurement(
        &measure, false); // pass in 'true' to get debug data printout!
    if (measure.RangeStatus != 4) { // phase failures have incorrect data
      double test = measure.RangeMilliMeter;
      if(test < LOWEST_RANGE_MM ) test = LOWEST_RANGE_MM;
      if(test > HIGHEST_RANGE_MM ) test = HIGHEST_RANGE_MM;
      Serial.print("Distance (mm): ");
      Serial.println(test);
      Value =  16384 * (test - LOWEST_RANGE_MM) / (HIGHEST_RANGE_MM - LOWEST_RANGE_MM);
      if (Value < 0) Value = 0;
      line.go(Value, 1000);
      testing = 1;
 //     sendController();
    }
    ControllerValue = Value;
              if (ControllerValue < 16384 || ControllerValue == 0) {
          //ControllerValue = 16383;
          // Serial.println(ControllerValue);
//           ControllerValue = filter.addSample(Value);

          sendController();
              }

  distance.clearInterruptMask(false);
}

bool distancePB::begin() {

  Serial.println("VL53L0X begin");
  if(!distance.begin()) {
  Serial.println("begin failed");
    return 0;
  }
  else {
      Serial.println("begin succeed");


  distance.setGpioConfig(VL53L0X_DEVICEMODE_CONTINUOUS_RANGING,
                    VL53L0X_GPIOFUNCTIONALITY_NEW_MEASURE_READY,
                    VL53L0X_INTERRUPTPOLARITY_LOW);
  FixPoint1616_t LowThreashHold = (LOWEST_RANGE_MM);
  FixPoint1616_t HighThreashHold = (HIGHEST_RANGE_MM);
  distance.setInterruptThresholds(LowThreashHold, HighThreashHold, true);

  distance.setDeviceMode(VL53L0X_DEVICEMODE_CONTINUOUS_RANGING, false);
  //distance.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_ACCURACY);
  Serial.println("StartMeasurement... ");
  distance.startMeasurement();

  ControllerValue = 16383;
  sendController();
  return 1;
  }
};
void distancePB::restart()  {
  Serial.println("restart distance measurement");
  distance.stopMeasurement();
  delay(1000);
  distance.startMeasurement();
}

void distancePB::sendController() {
//  uint16_t filteredValue = filter.addSample(ControllerValue);
    byte lowValue = ControllerValue & 0x7F;
    byte highValue = ControllerValue >> 7;
    midiEventPacket_t event_lsb = {0x0B, 0xB0 |  _channel, CONTROLER_LSB, lowValue};
    MidiUSB.sendMIDI(event_lsb);
    midiEventPacket_t event_msb = {0x0B, 0xB0 |  _channel, CONTROLER_MSB, highValue};
    MidiUSB.sendMIDI(event_msb);
}
