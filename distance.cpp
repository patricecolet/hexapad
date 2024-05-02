#include "distance.hpp"

midiMessage MidiMessageLidar;

distancePB::distancePB() {
  Adafruit_VL53L0X distance = Adafruit_VL53L0X();
};

void distancePB::sendMeasure() {
  VL53L0X_RangingMeasurementData_t measure;
  RangeStatus = measure.RangeStatus;
  uint16_t Value = 0;
  HighestRangeMSB = (Lidar.highThresholdMSB << 7) | 127;
  HighestRangeLSB = Lidar.highThresholdLSB | 896;
  HighestRange = HighestRangeMSB & HighestRangeLSB;
  LowestRangeMSB = (Lidar.lowThresholdMSB << 7) | 127;
  LowestRangeLSB = (Lidar.lowThresholdLSB) | 896;
  LowestRange = LowestRangeMSB & LowestRangeLSB;

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
      if (Lidar.trig_mode == trigType::keyboard) {
        MidiMessageLidar.sendNoteOff(Lidar.channel,Lidar.note);
      }
    }
    mesuring = 0;
  }
  ControllerValue = Value;
  if (ControllerValue < 16384 || ControllerValue == 0) {
    ControllerValue = 16383;
  }
  if (Lidar.enable == 1){
    byte lowValue = ControllerValue & 0x7F;
    byte highValue = ControllerValue >> 7;
    MidiMessageLidar.sendController(Lidar.channel,Lidar.controllerLSB, lowValue);
    MidiMessageLidar.sendController(Lidar.channel,Lidar.controllerMSB, highValue);
    lidarNote();
  }
  distance.clearInterruptMask(false);
}

void distancePB::lidarNote() {
  if (Lidar.trig_mode == trigType::keyboard && playing == 0 && mesuring == 1){
    distancePB::sendNoteOn(velocity());
    playing = 1;
  }
  if (playing == 1 && Lidar.trig_mode == trigType::keyboard && mesuring == 1) {                 
    MidiMessageLidar.sendAfterTouch(Lidar.channel,velocity(),Lidar.note);  // Application de l'AfterTouch
  }
  if (playing == 1 && Lidar.trig_mode == trigType::keyboard && mesuring == 0) {                 
    MidiMessageLidar.sendNoteOff(Lidar.channel,Lidar.note);
    playing = 0;
  }
  if (Lidar.trig_mode == trigType::button && mesuring == 1){
    if (lidarButton == 0 && playing == 0){
      distancePB::sendNoteOn(velocity());
      playing = 1;
    }
    else if (lidarButton == 1 && playing == 1){
      MidiMessageLidar.sendNoteOff(Lidar.channel,Lidar.note);
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
void distancePB::sendNoteOn(midi_byte velocity) {
  uint8_t velo;
  if (Lidar.curve == curveType::linear) {  // Type de courbe linéaire
    velo = velocity;
  } else if (Lidar.curve == curveType::parabola) {  // Type de courbe parabolique
    velo = (127 * velocity * velocity) / (127 * 127);
  } else if (Lidar.curve == curveType::hyperbola) {  // Type de courbe hyperbolique
    velo = round(127 * (1 - exp(-1.5 * velocity / 40)));
  } else if (Lidar.curve == curveType::sigmoid) {  // Type de courbe sigmoide
    velo = round(127 / (1 + exp(-0.08 * (velocity - 65))));
  }
  MidiMessageLidar.sendNoteOn(Lidar.channel, velocity, Lidar.note);
  if(DEBUG == 1) Serial.printf("Velocity lidar = %d\n", velo);
}

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
