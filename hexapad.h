#pragma once
#include "distance.hpp"         // VL53L0X methods
#include "qtouch.hpp"           // QTouch methods
#include "piezo.hpp"            // Piezo disk methods
#include "Adafruit_ZeroTimer.h" // Optimize analogRead for piezo
#include "midimap.h"            // Types definitions
#include "midimessage.hpp"        // function definitions for sending midi

// initialize VL53L0X objects
distancePB Distance;                
const byte VL53LOX_InterruptPin = 2;  // SAMD21 digital input for VL53LOX GPIO pin
long distanceTimer;                   
volatile byte VL53LOX_State = LOW;

bool buttonState[7] = {false, false, false, false, false, false, false}; // Déclaration des pads off lors du mode button

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
midiMessage MidiMessage;


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
  tableauQtouch[i].calibrate();  // Calibration des pad
  }
}


// This method is trigged at each loop() cycle.
void qTouchUpdate() {
  for (int i = 0; i < 7; i ++) {
    if (tableauQtouch[i].state == qtouch_state::played) { // Pad en train de jouer
      MidiMessage.sendAfterTouch(padSettings[i],tableauQtouch[i].afterTouch); // Application de l'AfterTouch
    }
    tableauQtouch[i].update(padSettings[i]); // Mise a jour de l'état des pads
    
// On Qtouch keyboard mode, we need to send a MIDI note off when the pad is released
    if (padSettings[i].trig_mode == trigType::keyboard) { // Pad en mode Keyboard
      if (tableauQtouch[i].noteState) {
        if (tableauQtouch[i].state == qtouch_state::off) { // Pad off
          MidiMessage.sendNoteOff(padSettings[i]); // Envoie NoteOff
          tableauQtouch[i].noteState = 0; // Etat Off
          if (DEBUG == 1)
            Serial.print("Keyboard Off \n \n");
        }
      }
    }
    else tableauQtouch[i].noteState = 0; // Etat Off
    }
  }
  
//Use interrupt to optimize analogRead
int COMPARE_P = 48000; // Set up the flexible divider/compare


//initialize timer 3
Adafruit_ZeroTimer zerotimerP = Adafruit_ZeroTimer(3);
void TC3_Handler() {
  Adafruit_ZeroTimer::timerHandler(3);
}

void hexapadSendNote(int velo){
  for (int i = 0; i < 7 ; i++) {
    if (padSettings[i].trig_mode == trigType::keyboard) { // Mode Keyboard
      if (tableauQtouch[i].state == qtouch_state::touched) {  // Pad touché
        MidiMessage.sendNoteOn(padSettings[i],velo); // Envoie velocité
        tableauQtouch[i].state = qtouch_state::played;  // Statue jouer
        tableauQtouch[i].noteState = 1;
        if (DEBUG == 1)
          Serial.print("Keyboard On \n");
      }
    }
    else if (padSettings[i].trig_mode == trigType::percussion) {  // Mode Percussion
      // Serial.printf("Qtouch state %d \n", tableauQtouch[i].state);
      if (tableauQtouch[i].state == qtouch_state::touched) {  // Pad touché
        if (DEBUG == 1)
          Serial.print("Percussion On \n");
        MidiMessage.sendNoteOn(padSettings[i],velo); // Envoie Note On et Velocité
        MidiMessage.sendNoteOff(padSettings[i]); // Envoie Note Off
      }
    }
    else if (padSettings[i].trig_mode == trigType::button){ // Mode Button
      if (tableauQtouch[i].state == qtouch_state::touched){ // Pad touché
        if (buttonState[i] != false){ // Pad joue
          MidiMessage.sendNoteOff(padSettings[i]); // Envoie Note Off
          tableauQtouch[i].noteState = 0;
          if (DEBUG == 1){
            Serial.print("Button Off \n");
            Serial.printf("Pad %d , state = %d \n \n", i+1, buttonState[i]);
          }
        }
        if (buttonState[i] == false){ // Pad ne joue pas
          MidiMessage.sendNoteOn(padSettings[i],velo); // Envoie Note On
          tableauQtouch[i].noteState = 1;
          if (DEBUG == 1){
            Serial.print("Button On \n");
            Serial.printf("Pad %d , state = %d \n \n", i+1, buttonState[i]);
          }
        }
        buttonState[i] = !buttonState[i]; // Changing pad status
      }
    }
  }  
}

// Methods called in timer's callback are prioritized
void TimerCallback0(){
  for (int i = 0; i < 7 ; i++) {
    if (padSettings[i].piezo == 1){ // Piezo activé 
      Piezo.update();
      if (Piezo.state == SENDNOTE) {
        hexapadSendNote(Piezo.velocity); // Envoie velocité grace au Piezo
        if (DEBUG == 2){
          Serial.printf("Available Piezo %d \n\n", Piezo.velocity);
        }
      }    
      else {
        VL53LOX_State = digitalRead(VL53LOX_InterruptPin);
        if (VL53LOX_State == LOW) {
          if (Distance.RangeStatus != 4) Distance.sendMeasure();
        }
      }
    }
    if (padSettings[i].piezo == 0){ // Piezo désactivé
      hexapadSendNote(tableauQtouch[i].afterTouch); // Envoie velocité grace au Qtouch
      if (DEBUG == 1)
        Serial.print("Disable Piezo \n\n");
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
  zerotimerP.setCallback(true,  TC_CALLBACK_CC_CHANNEL0, TimerCallback0);
  zerotimerP.enable(true);
}