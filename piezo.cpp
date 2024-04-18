#include "piezo.hpp"
#include "midimap.h"
piezo::piezo(pin_t pin, MIDIAddress address) {
  _address = address;
  _pin = pin;
};

void piezo::update() {
  MSB = (advancedSettings.sensitivityM << 5) | 31;
  LSB = (advancedSettings.sensitivityL) | 992;
  sensitivity = MSB & LSB;
  piezoRead = analogRead(_pin);  // reading piezo value
  if (DEBUG == 3) {
    Serial.println(piezoRead);
    delay(20000);
  }
  switch (Piezo.state) {
    case UNDERTHRESHOLD:
      if (piezoRead > Piezo.fallingThreshold && piezoRead > prevpiezoRead)
        Piezo.state = SIGNAL;
      if (Piezo.fallingThreshold > advancedSettings.threshold) {
        Piezo.fallingThreshold = Piezo.fallingThreshold - 0.5;
      }
      break;
    case SIGNAL:
      if (piezoRead > Piezo.peak)  // value increasing
        Piezo.state = RISING;
      break;
    case RISING:
      if (piezoRead < prevpiezoRead)  // value at the max
        Piezo.state = PEAK;
      //        sendNote = 1;
      break;
    case PEAK:
      if (DEBUG == 2) {
        Serial.print("PEAK:");
        Serial.print(Piezo.peak);
        Serial.print("->");
        Serial.println(millis() - piezoTimer);
      }
      break;
    case WINDOWING:
      if (millis() - piezoTimer > 7) {
        //        sendNote = 1;
        Piezo.state = SENDNOTE;  // hexapad send a midi note
      } else Piezo.state = PEAK;
      break;
    case SENDNOTE:
      //      if (Piezo.prevstate == SENDNOTE)
      Piezo.state = FALLING;  // a midi should have been sent in previous cycle
      break;
    case FALLING:
      if (piezoRead < Piezo.fallingThreshold && (millis() - piezoTimer) > advancedSettings.debounceTime) {
        Piezo.fallingThreshold = Piezo.peak / 3;
        Piezo.state = UNDERTHRESHOLD;

        // Serial.print("underthreshold: ");
        // Serial.println(millis() - piezoTimer);
      }
      break;
    default:
      break;
  }

  // switch case for actions in each piezo.state
  switch (Piezo.state) {
    case UNDERTHRESHOLD:
      Piezo.peak = 0;
      break;
    case SIGNAL:
      piezoTimer = millis();
      break;
    case RISING:
      //      Piezo.peak = piezoRead;
      break;
    case PEAK:
      if (Piezo.peak < piezoRead) {
        Piezo.peak = piezoRead;
        updateNote();
        if (Piezo.peak == sensitivity) {
          //          sendNote = 1;
          Piezo.state = SENDNOTE;
        }
      }
      Piezo.state = WINDOWING;
      break;
    case WINDOWING:
      //      if (sendNote == 1)
      //      Piezo.state = SENDNOTE;
      break;
    case SENDNOTE:
      //      sendNote = 0;
      break;
    case FALLING:

      break;
    default:
      break;
  }
  prevpiezoRead = piezoRead;
  Piezo.prevstate = Piezo.state;
  state = Piezo.state;
}


void piezo::updateNote() {
  velocity = ((127 * piezoRead) / (sensitivity - advancedSettings.threshold)) + (127 - ((127 * sensitivity) / (sensitivity - advancedSettings.threshold)));
  // velocity = 127 * piezoRead /(sensitivity - advancedSettings.threshold);
  if (velocity > 127) velocity = 127;
  if (velocity < 1) velocity = 1;
  // if (velocity > Piezo.peak) Piezo.peak = velocity;
}
