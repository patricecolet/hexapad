#pragma once

#include "midimap.h"             // Types definitions
#include "distance.hpp"          // VL53L0X methods
#include "qtouch.hpp"            // QTouch methods
#include "piezo.hpp"             // Piezo disk methods
#include "Adafruit_ZeroTimer.h"  // Optimize analogRead for piezo
#include "midimessage.hpp"       // function definitions for sending midi
#include "sysex.hpp"

// initialize VL53L0X objects
distancePB Distance;
const byte VL53LOX_InterruptPin = 2;  // SAMD21 digital input for VL53LOX GPIO pin
long distanceTimer;
volatile byte VL53LOX_State = LOW;

bool buttonState[7] = { false, false, false, false, false, false, false };  // Déclaration des pads off lors du mode button
int noteState[7] = { 0, 0, 0, 0, 0, 0, 0 };

int Velocity_curve(PadSettings, int);
int AfterTouchNote(PadSettings, int, int);

// initialize Qtouch pins
NoteQtouch tableauQtouch[] = {
  NoteQtouch{
    qtouch_pin::QT1,
    padSettings[0] },
  NoteQtouch{
    qtouch_pin::QT2,
    padSettings[1] },
  NoteQtouch{
    qtouch_pin::QT3,
    padSettings[2] },
  NoteQtouch{
    qtouch_pin::QT4,
    padSettings[3] },
  NoteQtouch{
    qtouch_pin::QT5,
    padSettings[4] },
  NoteQtouch{
    qtouch_pin::QT6,
    padSettings[5] },
  NoteQtouch{
    qtouch_pin::QT7,
    padSettings[6] }
};
midiMessage MidiMessage;
sysex Sysex;

// initialize piezo pin
piezo Piezo{
  A3,        // Analog pin
  { 48, 0 }  // Note Number 48 on MIDI channel 1
};


// Enable Qtouch pins
void qTouchBegin() {
  for (int i = 0; i < 7; i++) {
    tableauQtouch[i].begin();
  }
}


// Calibrate Qtouch pins
void qTouchCalibrate() {
  for (int i = 0; i < 7; i++) {
    tableauQtouch[i].calibrate();  // Calibration des pad
  }
}


// This method is trigged at each loop() cycle.
void qTouchUpdate() {
  int note;
  for (int i = 0; i < 7; i++) {
    if (tableauQtouch[i].state == qtouch_state::played) {   
      note = AfterTouchNote(padSettings[i], tableauQtouch[i].afterTouch, i);                    // Pad en train de jouer
      MidiMessage.sendAfterTouch(padSettings[i], tableauQtouch[i].afterTouch, note);  // Application de l'AfterTouch
    }
    tableauQtouch[i].update(padSettings[i]);  // Mise a jour de l'état des pads

    // On Qtouch keyboard mode, we need to send a MIDI note off when the pad is released
    if (padSettings[i].trig_mode == trigType::keyboard) {  // Pad en mode Keyboard
      if (tableauQtouch[i].noteState) {
        if (tableauQtouch[i].state == qtouch_state::off) {  // Pad off
          MidiMessage.sendNoteOff(padSettings[i], noteState[i]);         // Envoie NoteOff
          tableauQtouch[i].noteState = 0;                   // Etat Off
          if (DEBUG == 1)
            Serial.print("Keyboard Off \n \n");
        }
      }
    } else tableauQtouch[i].noteState = 0;  // Etat Off
  }
}

//Use interrupt to optimize analogRead
int COMPARE_P = 48000;  // Set up the flexible divider/compare


//initialize timer 3
Adafruit_ZeroTimer zerotimerP = Adafruit_ZeroTimer(3);
void TC3_Handler() {
  Adafruit_ZeroTimer::timerHandler(3);
}

void hexapadSendNote(int velo) {
  int velocity, note;
  for (int i = 0; i < 7; i++) {
    if (padSettings[i].trig_mode == trigType::keyboard) {     // Mode Keyboard
      if (tableauQtouch[i].state == qtouch_state::touched) {  // Pad touché
        velocity = Velocity_curve(padSettings[i], velo);
        note = AfterTouchNote(padSettings[i], tableauQtouch[i].afterTouch, i);
        MidiMessage.sendNoteOn(padSettings[i], velocity, note);         // Envoie velocité
        tableauQtouch[i].state = qtouch_state::played;        // Statue jouer
        tableauQtouch[i].noteState = 1;
        if (DEBUG == 1)
          Serial.print("Keyboard On \n");
      }
    } else if (padSettings[i].trig_mode == trigType::percussion) {  // Mode Percussion
      // Serial.printf("Qtouch state %d \n", tableauQtouch[i].state);
      if (tableauQtouch[i].state == qtouch_state::touched) {  // Pad touché
        if (DEBUG == 1)
          Serial.print("Percussion On \n");
        velocity = Velocity_curve(padSettings[i], velo);
        note = AfterTouchNote(padSettings[i], tableauQtouch[i].afterTouch, i);
        MidiMessage.sendNoteOn(padSettings[i], velocity, note);   // Envoie Note On et Velocité
        MidiMessage.sendNoteOff(padSettings[i], noteState[i]);       // Envoie Note Off
      }
    } else if (padSettings[i].trig_mode == trigType::button) {  // Mode Button
      if (tableauQtouch[i].state == qtouch_state::touched) {    // Pad touché
        if (buttonState[i] != false) {                          // Pad joue
          velocity = Velocity_curve(padSettings[i], velo);
          note = AfterTouchNote(padSettings[i], tableauQtouch[i].afterTouch, i);
          MidiMessage.sendNoteOff(padSettings[i], noteState[i]);              // Envoie Note Off
          tableauQtouch[i].noteState = 0;
          if (DEBUG == 1) {
            Serial.print("Button Off \n");
            Serial.printf("Pad %d , state = %d \n \n", i + 1, buttonState[i]);
          }
        }
        if (buttonState[i] == false) {                   // Pad ne joue pas
          velocity = Velocity_curve(padSettings[i], velo);
          note = AfterTouchNote(padSettings[i], tableauQtouch[i].afterTouch, i);
          MidiMessage.sendNoteOn(padSettings[i], velocity, note);   // Envoie Note On
          tableauQtouch[i].noteState = 1;
          if (DEBUG == 1) {
            Serial.print("Button On \n");
            Serial.printf("Pad %d , state = %d \n \n", i + 1, buttonState[i]);
          }
        }
        buttonState[i] = !buttonState[i];  // Changing pad status
      }
    }
  }
}

int Velocity_curve(PadSettings pad, int velocity){
  uint8_t velo;
  if (pad.velocity_curve == curveType::linear) {  // Type de courbe linéaire
    velo = velocity;
  } else if (pad.velocity_curve == curveType::parabola) {  // Type de courbe parabolique
    velo = (127 * velocity * velocity) / (127 * 127);
  } else if (pad.velocity_curve == curveType::hyperbola) {  // Type de courbe hyoerbolique
    velo = round(127 * (1 - exp(-1.5 * velocity / 40)));
  } else if (pad.velocity_curve == curveType::sigmoid) {  // Type de courbe sigmoide
    velo = round(127 / (1 + exp(-0.08 * (velocity - 65))));
  }
  return velo;
}

int AfterTouchNote(PadSettings pad, int afterTouch, int channel) {
  float pourcentage = 127/100;
  int note = 0;
  if (afterTouch >= pad.padNote.qtouchThreshold1*pourcentage && afterTouch < pad.padNote.qtouchThreshold2*pourcentage){
    note = pad.padNote.note1;
  }
  else if (afterTouch >= pad.padNote.qtouchThreshold2*pourcentage && afterTouch < pad.padNote.qtouchThreshold3*pourcentage){
    note = pad.padNote.note2;
  }
  else if (afterTouch >= pad.padNote.qtouchThreshold3*pourcentage){
    note = pad.padNote.note3;
  }
  noteState[channel] = note;
  return note;
}



// Methods called in timer's callback are prioritized
void TimerCallback0() {
  for (int i = 0; i < 7; i++) {
    if (padSettings[i].piezo == 1) {  // Piezo activé
      Piezo.update();
      if (Piezo.state == SENDNOTE) {
        hexapadSendNote(Piezo.velocity);  // Envoie velocité grace au Piezo
        if (DEBUG == 2) {
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
    if (padSettings[i].piezo == 0) {                 // Piezo désactivé
      hexapadSendNote(tableauQtouch[i].afterTouch);  // Envoie velocité grace au Qtouch
      if (DEBUG == 1)
        Serial.print("Disable Piezo \n\n");
    }
  }
}

// timer setup
void timerPBegin() {
  tc_clock_prescaler prescaler = TC_CLOCK_PRESCALER_DIV1;
  zerotimerP.enable(false);
  zerotimerP.configure(prescaler,                    // prescaler
                       TC_COUNTER_SIZE_16BIT,        // bit width of timer/counter
                       TC_WAVE_GENERATION_MATCH_PWM  // frequency or PWM mode
  );
  zerotimerP.setCompare(0, COMPARE_P);
  zerotimerP.setCallback(true, TC_CALLBACK_CC_CHANNEL0, TimerCallback0);
  zerotimerP.enable(true);
}