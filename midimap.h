#pragma once
#include <Arduino.h>
#define DEBUG true

enum class qtouch_pin : uint8_t {
  QT1 = A0, QT2 = A1, QT3 = A6, QT4 = A8, QT5 = A7, QT6 = A9, QT7 = A10
};

enum class trigType : uint8_t {
  percussion = 0, keyboard = 1, button = 2 // Mode des pads
};
enum class curveType : uint8_t {
  linear = 0, parabola = 1, hyperbola = 2, sigmoid = 3 // Forme de la vélocité
};

typedef uint8_t midi_channel;
typedef uint8_t midi_note;
typedef uint8_t midi_threshold;
typedef uint8_t midi_sensitivityM;
typedef uint8_t midi_sensitivityL;
typedef uint8_t midi_debounceTime;
typedef uint8_t midi_roundOff;

struct PadSettings {
  midi_channel channel;
  midi_note note;
  trigType trig_mode;
  curveType velocity_curve;
  curveType aftertouch_curve;
  bool piezo_disabled;
  bool qtouch_disabled;
  };

struct AdvancedSettings {
  midi_threshold threshold;
  midi_sensitivityM sensitivityM;
  midi_sensitivityL sensitivityL;
  midi_debounceTime debounceTime;
  midi_roundOff roundOff;
};
  
extern PadSettings padSettings[7];
extern AdvancedSettings advancedSettings;


/*
uint8_t rangeSettings[14] = {
  0,  // ctl 1   MIDI channel
  48, // ctl 2  MIDI note (mode single note or button or first scale note, modulate velocity)
  0,  // ctl 3  Trig mode (range CTL, single note, button, note scale)
  0,  // ctl 4  Curve
  0,  // ctl 5  Disable sensor
  50,  // ctl 6  LOW threshold(mm) LSB
  0, // ctl 7  LOW threshold(mm) MSB
  16,  // ctl 8  HIGH threshold(mm) LSB
  3,  // ctl 9  HIGH threshold(mm) MSB
  14,  // ctl 10 MIDI controller LSB
  46,  // ctl 11 MIDI controller MSB
  0, // ctl 12 Scale LSB
  0,  // ctl 13 Scale MSB
  1  //  ctl 14 SCale octaves
};
*/
