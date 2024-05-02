#include "hexapad.h"

void setup() {
  Serial.begin(9600);
  Serial.println(F("HEXAPAD SETUP"));
  delay(1000);
  qTouchBegin();
  delay(1000);   
  qTouchCalibrate();
  pinMode(VL53LOX_InterruptPin, INPUT_PULLUP);
/*  if (!Distance.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    delay(100);
  }
  */
  timerPBegin();
  MidiMessage.begin();
}

void loop() {
  qTouchUpdate();
  MidiMessage.update();
  // MidiMessage.midiInMessages();
}
