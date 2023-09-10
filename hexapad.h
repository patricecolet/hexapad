#pragma once
#include "distance.hpp"         // VL53L0X methods
#include "qtouch.hpp"           // SAMD21 QTouch methods
#include "piezo.hpp"            // Piezo disk methods
#include "Adafruit_ZeroTimer.h" // Optimize analogRead for piezo
#include "midimap.h"

// initialize VL53L0X objects
distancePB Distance;                
const byte VL53LOX_InterruptPin = 2;  // SAMD21 digital input for VL53LOX GPIO pin
long distanceTimer;                   
volatile byte VL53LOX_State = LOW;


// initialize Qtouch pins
NoteQtouch tableauQtouch[] = {
  NoteQtouch {
    qtouch_pin::QT1,
    padSettings[0]
  },
  NoteQtouch {
    qtouch_pin::QT2,    
    padSettings[1]
  },
  NoteQtouch {
    qtouch_pin::QT3,
    padSettings[2]
  },
  NoteQtouch {
    qtouch_pin::QT4,  
    padSettings[3]
  },
  NoteQtouch {
    qtouch_pin::QT5,
    padSettings[4]
  },
  NoteQtouch {
    qtouch_pin::QT6,
    padSettings[5]
  },
  NoteQtouch{
    qtouch_pin::QT7,
    padSettings[6]
  }
};

// initialize piezo pin
piezo Piezo {
  A3,            // Analog pin
  {48, 0 }      // Note Number 48 on MIDI channel 1
 };

// Enable Qtouch pins
void qTouchBegin() {
  for (int i = 0; i < 7; i ++){
  tableauQtouch[i].begin();   
  }
}

// Calibrate Qtouch pins
void qTouchCalibrate() {
  for (int i = 0; i < 7; i ++){
  tableauQtouch[i].calibrate();  
  }
}
/*
void qTouchTrigMode(uint8_t mode) {
  for (int i = 0; i < 7; i ++) {
    tableauQtouch[i].trigMode = static_cast<trigType>(mode);   
  }
}*/
// This method is trigged at each loop() cycle.
void qTouchUpdate() {
  for (int i = 0; i < 7; i ++) {
    tableauQtouch[i].update();
// On Qtouch keyboard mode, we need to send a MIDI note off when the pad is released
    if (padSettings[i].trig_mode == trigType::keyboard) {
      if (tableauQtouch[i].noteState) {
        if (tableauQtouch[i].state == qtouch_state::off) {
          tableauQtouch[i].sendNoteOff();
          tableauQtouch[i].noteState = 0;
        }
      }
    } else tableauQtouch[i].noteState = 0;
  }
}
//Use interrupt to optimize analogRead
int COMPARE_P = 48000; // Set up the flexible divider/compare

//initialize timer 3
Adafruit_ZeroTimer zerotimerP = Adafruit_ZeroTimer(3);
void TC3_Handler() {
  Adafruit_ZeroTimer::timerHandler(3);
}
// Methods called in timer's callback are prioritized
void TimerCallback0(){
  Piezo.update((uint8_t)(48));
  if (Piezo.state == SENDNOTE) {
    for (int i = 0; i < 7 ; i++) {
      if (padSettings[i].trig_mode == trigType::keyboard) {
        if (tableauQtouch[i].state == qtouch_state::touched) {       
          Piezo.noteOn(padSettings[i].note);
          tableauQtouch[i].state = qtouch_state::played;
          tableauQtouch[i].noteState = 1;
        }
      }
      else if (padSettings[i].trig_mode == trigType::percussion) {
        if (tableauQtouch[i].state == qtouch_state::touched) {
          Piezo.piezoNote(padSettings[i].note);
        }
      }
    }    
  } else {
    VL53LOX_State = digitalRead(VL53LOX_InterruptPin);
    if (VL53LOX_State == LOW) {
      if (Distance.RangeStatus != 4) Distance.sendMeasure();
    }
  }
}

// timer setup
void timerPBegin(){ 
  tc_clock_prescaler prescaler = TC_CLOCK_PRESCALER_DIV1;
  zerotimerP.enable(false);
  zerotimerP.configure(prescaler,       // prescaler
          TC_COUNTER_SIZE_16BIT,       // bit width of timer/counter
          TC_WAVE_GENERATION_MATCH_PWM // frequency or PWM mode
          );
  zerotimerP.setCompare(0, COMPARE_P);
  zerotimerP.setCallback(true, TC_CALLBACK_CC_CHANNEL0, TimerCallback0);
  zerotimerP.enable(true);
}

// hexapad settings can be done with MIDI messages:
void midiInMessages() {
    midiEventPacket_t midirx;
  // read the midi note
  midirx = MidiUSB.read();
  char midiheader = midirx.header;
  uint8_t midi_channel = int(midirx.byte1 & 0XF);
  

  switch(midiheader) {
    case 0x0B : {// On MIDI controller
      uint8_t controller =  int(midirx.byte2);
      uint8_t value =  int(midirx.byte3);
      if (midi_channel < 8 && controller < 8) {
//        padSettings[channel][controller] = value;
        if (controller == 1) padSettings[midi_channel].channel = value;
        else if (controller == 2) padSettings[midi_channel].note = value;
        else if (controller == 3) padSettings[midi_channel].trig_mode = static_cast<trigType>(value);
        else if (controller == 4) padSettings[midi_channel].velocity_curve = value;
        else if (controller == 5) padSettings[midi_channel].aftertouch_curve = value;
        else if (controller == 6) padSettings[midi_channel].piezo_disabled = value > 63;
        else if (controller == 7) padSettings[midi_channel].qtouch_disabled = value > 63;
      }
    }
      break;
    case 0x08 : {// On MIDI note off
      char midinote =  midirx.byte2;
      char midivelocity =  midirx.byte3;
        if (midinote == 0x3c) {             // C4 to calibrate qtouch
          Serial.println("calibrating...");
          delay(100);
          qTouchCalibrate();
          Distance.restart();
        }
    }
      break;
    default:
    break;
  }     
}
