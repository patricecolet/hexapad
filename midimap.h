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
  pad1 = 0, pad2 = 1, pad3 = 2, pad4 = 3, pad5 = 4, pad6 = 5, pad7 = 6, lidar = 7, advanced = 8
};
enum class sysexCommand : const uint8_t {
  set = 1, get = 2, calibrate = 3
};
enum class sysexParam : const uint8_t {
  pad = 1, lidar = 2, advanced = 3
};
enum class padParam : const uint8_t {
  channel = 1,
  note = 2,
  trig_mode = 3, velocity_curve = 4,
  aftertouch_curve = 5, piezo = 6,
  qtouch = 7, qtouch_onset = 8,
  qtouch_offset = 9, qtouch_ceiling = 10
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
  qtouchRoundOff = 7
};


typedef uint8_t midi_channel;
typedef uint8_t midi_note;
typedef uint16_t qtouch_threshold;
typedef long qtouch_timer;

typedef uint8_t midi_byte;


struct pad_note {
  qtouch_threshold qtouchThreshold;
  midi_note note;
};

struct PadSettings {
  midi_channel channel;
  midi_note note;
  trigType trig_mode;
  curveType velocity_curve;
  curveType aftertouch_curve;
  bool piezo;
  bool qtouch;
  uint16_t qtouch_floor;
  uint16_t qtouch_debounce;
  uint16_t qtouch_onset;
  uint16_t qtouch_offset;
  uint16_t qtouch_ceiling;
  };

struct AdvancedSettings {
  midi_byte piezoThresholdLSB;
  midi_byte piezoThresholdMSB;
  midi_byte piezoSensitivityLSB;
  midi_byte piezoSensitivityMSB;
  midi_byte piezoDebounceTimeLSB;
  midi_byte piezoDebounceTimeMSB;
  midi_byte qtouchRoundOff;
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



