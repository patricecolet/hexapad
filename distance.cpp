#include "distance.hpp"
#include "midimap.h"
#include "midimessage.hpp"  // function definitions for sending midi

distancePB::distancePB() {
  Adafruit_VL53L0X distance = Adafruit_VL53L0X();
};
midiMessage MidiMessageLidar;

void distancePB::sendMeasure() {
  VL53L0X_RangingMeasurementData_t measure;
  RangeStatus = measure.RangeStatus;
  uint16_t Value = 0;
  HighestRangeMSB = (lidar.highThresholdMSB << 7) | 127;
  HighestRangeLSB = (lidar.highThresholdLSB) | 896;
  HighestRange = HighestRangeM & HighestRangeL;
  LowestRangeMSB = (lidar.lowThresholdMSB << 7) | 127;
  LowestRangeLSB = (lidar.lowThresholdLSB) | 896;
  LowestRange = LowestRangeM & LowestRangeL;

  //    Serial.print("Reading a measurement... ");
  distance.getRangingMeasurement(&measure, false);              // pass in 'true' to get debug data printout!
  if (measure.RangeStatus != 4) {                               // phase failures have incorrect data
    test = measure.RangeMilliMeter;
    if (test < LowestRange) test = LowestRange;
    if (test > HighestRange) test = HighestRange;
    if (DEBUG == 2) {
      Serial.print("Distance (mm): ");
      Serial.println(test);
    }
    Value = 16384 * (test - LowestRange) / (HighestRange - LowestRange);
    if (Value < 0) Value = 0;
    //line.go(Value, 1000);
    testing = 1;
    mesuring = 1;
  }
  else {
    if (mesuring != 0){
      lidarButton = !lidarButton;
      if (lidar.trig_mode == trigType::keyboard) {
        MidiMessageLidar.sendNoteOffLidar();
      }
    }
    mesuring = 0;
  }
  ControllerValue = Value;
  if (ControllerValue < 16384 || ControllerValue == 0) {
    ControllerValue = 16383;
    //Serial.println(ControllerValue);
    //ControllerValue = filter.addSample(Value);
  }
  if (lidar.sensor == 1){
    MidiMessageLidar.sendControllerLidar(ControllerValue);
    lidarNote();
  }
  distance.clearInterruptMask(false);
}

void distancePB::lidarNote() {
  if (lidar.trig_mode == trigType::keyboard && playing == 0 && mesuring == 1){
    MidiMessageLidar.sendNoteOnLidar(velocity());
    playing = 1;
  }
  if (playing == 1 && lidar.trig_mode == trigType::keyboard && mesuring == 1) {                 
    MidiMessageLidar.sendAfterTouchLidar(velocity());  // Application de l'AfterTouch
  }
  if (playing == 1 && lidar.trig_mode == trigType::keyboard && mesuring == 0) {                 
    MidiMessageLidar.sendNoteOffLidar();
    playing = 0;
  }
  if (lidar.trig_mode == trigType::button && mesuring == 1){
    if (lidarButton == 0 && playing == 0){
      MidiMessageLidar.sendNoteOnLidar(velocity());
      playing = 1;
    }
    else if (lidarButton == 1 && playing == 1){
      MidiMessageLidar.sendNoteOffLidar();
      playing = 0;
    }
  }
}

bool distancePB::begin() {

  Serial.println("VL53L0X begin");
  if (!distance.begin()) {
    Serial.println("begin failed");
    return 0;
  } else {
    Serial.println("begin succeed");


    distance.setGpioConfig(VL53L0X_DEVICEMODE_CONTINUOUS_RANGING,
                           VL53L0X_GPIOFUNCTIONALITY_NEW_MEASURE_READY,
                           VL53L0X_INTERRUPTPOLARITY_LOW);
    FixPoint1616_t LowThreashHold = (LowestRange);
    FixPoint1616_t HighThreashHold = (HighestRange);
    distance.setInterruptThresholds(LowThreashHold, HighThreashHold, true);

    distance.setDeviceMode(VL53L0X_DEVICEMODE_CONTINUOUS_RANGING, false);
    //distance.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_ACCURACY);
    if (DEBUG == 1) Serial.println("StartMeasurement... ");
    distance.startMeasurement();
    return 1;
  }
};

int distancePB::velocity() {
  int velocity = ((127 * test) / (HighestRange - LowestRange)) + (127 - ((127 * HighestRange) / (HighestRange - LowestRange)));
  return velocity;
}

void distancePB::restart() {
  Serial.println("restart distance measurement");
  distance.stopMeasurement();
  delay(1000);
  distance.startMeasurement();
}
