#pragma once
#include <Arduino.h>

// #include "MIDIUSB.h"

#define DEBUG 1

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
typedef uint16_t qtouch_threshold;

typedef uint8_t midi_byte;


struct pad_note {
  qtouch_threshold qtouchThreshold1;
  midi_note note1;
  qtouch_threshold qtouchThreshold2;
  midi_note note2;
  qtouch_threshold qtouchThreshold3;
  midi_note note3;
};

struct PadSettings {
  midi_channel channel;
  midi_note padNote;
  trigType trig_mode;
  curveType velocity_curve;
  curveType aftertouch_curve;
  bool piezo;
  bool qtouch;
  };

struct AdvancedSettings {
  midi_byte thresholdL;
  midi_byte thresholdM;
  midi_byte sensitivityL;
  midi_byte sensitivityM;
  midi_byte debounceTimeL;
  midi_byte debounceTimeM;
  midi_byte roundOff;
};

struct Lidar {
  midi_channel channel;
  midi_byte note;
  trigType trig_mode;
  curveType curve;
  midi_byte sensor;
  midi_byte lowThresholdLSB;
  midi_byte lowThresholdMSB;
  midi_byte highThresholdLSB;
  midi_byte highThresholdMSB;
  midi_byte controllerLSB;
  midi_byte controllerMSB;
};
  
extern PadSettings padSettings[7];
extern AdvancedSettings advancedSettings;
extern Lidar lidar;
extern byte sysexPacket[100];

