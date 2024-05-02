#pragma once
#include <Arduino.h>

#define DEBUG 1

enum class qtouch_pin : const uint8_t {
  QT1 = A0, QT2 = A1, QT3 = A6, QT4 = A8, QT5 = A7, QT6 = A9, QT7 = A10
};
enum class trigType : const uint8_t {
  percussion = 0, keyboard = 1, button = 2 // Mode des pads
};
enum class curveType : const uint8_t {
  linear = 0, parabola = 1, hyperbola = 2, sigmoid = 3 // Types de courbes
};
enum class hexapad : const uint8_t {
  pad1 = 1, pad2 = 2, pad3 = 3, pad4 = 4, pad5 = 5, pad6 = 6, pad7 = 7, lidar = 8, advanced = 9
};
enum class sysexCommand : const uint8_t {
  set = 1, get = 2, calibrate = 3
};
enum class padParam : const uint8_t {
  channel = 1,
  note1 = 2, qtouchThreshold1 = 3,
  note2 = 4, qtouchThreshold2 = 5,
  note3 = 6, qtouchThreshold3 = 7,
  trig_mode = 8, velocity_curve = 9, aftertouch_curve = 10, piezo = 11, qtouch = 12
};
enum class lidarParam : const uint8_t {
  channel = 1,
  note = 2,
  curve = 3,
  lowThresholdLSB = 4, lowThresholdMSB = 5,
  highThresholdLSB = 6, highThresholdMSB = 7,
  controllerLSB = 8, controllerMSB = 9,
  scale = 10,
  scaleRangeLow = 11,
  scaleRangeHigh= 12,
  enable = 13
};
enum class advancedParam : const byte {
  piezoThresholdLSB = 1,
  piezoThresholdMSB = 2,
  piezoSensitivityLSB = 3,
  piezoSensitivityMSB = 4,
  piezoDebounceTimeLSB = 5,
  piezoDebounceTimeMSB = 6,
  piezoRoundOff = 7
};


typedef uint8_t midi_channel;
typedef uint8_t midi_note;
typedef uint16_t qtouch_threshold;

typedef uint8_t midi_byte;


struct pad_note {
  qtouch_threshold qtouchThreshold;
  midi_note note;
};

struct PadSettings {
  midi_channel channel;
  pad_note padNote1;
  pad_note padNote2;
  pad_note padNote3;
  trigType trig_mode;
  curveType velocity_curve;
  curveType aftertouch_curve;
  bool piezo;
  bool qtouch;
  };

struct AdvancedSettings {
  midi_byte piezoThresholdLSB;
  midi_byte piezoThresholdMSB;
  midi_byte piezoSensitivityLSB;
  midi_byte piezoSensitivityMSB;
  midi_byte piezoDebounceTimeLSB;
  midi_byte piezoDebounceTimeMSB;
  midi_byte piezoRoundOff;
};

struct LIDAR {
  midi_channel channel;
  midi_note note;
  trigType trig_mode;
  curveType curve;
  midi_byte lowThresholdLSB;
  midi_byte lowThresholdMSB;
  midi_byte highThresholdLSB;
  midi_byte highThresholdMSB;
  midi_byte controllerLSB;
  midi_byte controllerMSB;
  midi_byte enable;
};
  
extern PadSettings padSettings[7];
extern AdvancedSettings advancedSettings;
extern LIDAR Lidar;
extern const byte SysexID[];



