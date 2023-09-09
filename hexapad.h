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
    QT1,            // QT1 is also pin A0 of SAMD21
    {62, 0 }     // Note Number 60 on MIDI channel 1
  },
  NoteQtouch {
    QT2,            // QT2 is also pin A1 of SAMD21
    {64, 0 }     // Note Number 60 on MIDI channel 1
  },
  NoteQtouch {
    QT3,            // QT3 is also pin A6 of SAMD21
    {65, 0 }     // Note Number 60 on MIDI channel 1
  },
  NoteQtouch {
    QT4,            // QT4 is also pin A7 of SAMD21
    {69, 0 }     // Note Number 60 on MIDI channel 1
  },
  NoteQtouch {
    QT5,            // QT5 is also pin A8 of SAMD21
    {67, 0 }     // Note Number 60 on MIDI channel 1
  },
  NoteQtouch {
    QT6,            // QT6 is also pin A9 of SAMD21
    {60, 0 }     // Note Number 60 on MIDI channel 1
  },
  NoteQtouch{
    QT7,            // QT7 is also pin A10 of SAMD21
    {71, 0 }     // Note Number 60 on MIDI channel 1
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

void qTouchTrigMode(uint8_t mode) {
  for (int i = 0; i < 7; i ++) {
    tableauQtouch[i].trigMode = mode;   
  }
}
// This method is trigged at each loop() cycle.
void qTouchUpdate() {
  for (int i = 0; i < 7; i ++) {
    tableauQtouch[i].update();
// On Qtouch keyboard mode, we need to send a MIDI note off when the pad is released
    if (tableauQtouch[i].trigMode == QT_TRIG_KEYBOARD) {
      if (tableauQtouch[i].noteState) {
        if (tableauQtouch[i].state == QT_OFF) {
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
      if (tableauQtouch[i].trigMode == QT_TRIG_KEYBOARD) {
        if (tableauQtouch[i].state == QT_TOUCHED) {       
          Piezo.noteOn(tableauQtouch[i].note);
          tableauQtouch[i].state = QT_PLAYED;
          tableauQtouch[i].noteState = 1;
//          Serial.print("keyboard_note");
        }
      }
      else if (tableauQtouch[i].trigMode == QT_TRIG_PERCUSSION) {
        if (tableauQtouch[i].state == QT_TOUCHED) {
          Piezo.piezoNote(tableauQtouch[i].note);
//          Serial.print("percu_note");
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
  char channel = (midirx.byte1);
  char midinote =  midirx.byte2;
  char midivelocity =  midirx.byte3;
  switch(midiheader) {
    case 0x0B : // On MIDI controller
      // Serial.print("test ");
      // Serial.print(int(channel & 0XF));
      // Serial.print(", controller ");
      // Serial.print(int(midirx.byte2));
      // Serial.print(": ");
      // Serial.println(int(midirx.byte3));
      // delay(100);
      break;
    case 0x08 : // On MIDI note off
        if (midinote == 0x3c) {             // C4 to calibrate qtouch
          Serial.println("calibrating...");
          delay(100);
          qTouchCalibrate();
          Distance.restart();
        }
        if (midinote == 0x30) {             // C3 to set keyboard mode
          qTouchTrigMode(QT_TRIG_KEYBOARD);      // Serial.print(": ");
       Serial.println("QT_TRIG_KEYBOARD");
        }
        if (midinote == 0x32) {             // D3 to set percussion mode
          qTouchTrigMode(QT_TRIG_PERCUSSION);
          Serial.println("QT_TRIG_PERCUSSION");
        }
    break;
  }     
}


