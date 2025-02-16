#include "hexapad.h"

void setup() {
  Serial.begin(9600);
  delay(2000); 
  Serial.println("HEXAPAD SETUP");
  qTouchBegin();
  delay(1000);   
  qTouchCalibrate();
  delay(1000);  
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
