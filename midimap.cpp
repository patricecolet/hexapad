#include "midimap.h"
extern PadSettings padSettings[7] =
{
  PadSettings{ 
    .channel = 0,
    .note = 62,
    .trig_mode = trigType::keyboard,
    .velocity_curve = curveType::linear,
    .aftertouch_curve = curveType::linear,
    .piezo = 0,
    .qtouch = 1,
    .qtouch_floor = 0,
    .qtouch_debounce = 100,
    .qtouch_onset = 20,
    .qtouch_offset = 0,
    .qtouch_ceiling = 100
  },
  PadSettings{ 
    .channel = 0,
    .note = 64,
    .trig_mode = trigType::keyboard,
    .velocity_curve = curveType::linear,
    .aftertouch_curve = curveType::linear,
    .piezo = 0,
    .qtouch = 1,
    .qtouch_floor = 0,
    .qtouch_debounce = 100,
    .qtouch_onset = 10,
    .qtouch_offset = 0,
    .qtouch_ceiling = 200
  },
  PadSettings{ 
    .channel = 0,
    .note = 65,
    .trig_mode = trigType::keyboard,
    .velocity_curve = curveType::linear,
    .aftertouch_curve = curveType::linear,
    .piezo = 0,
    .qtouch = 1,
    .qtouch_floor = 0,
    .qtouch_debounce = 50,
    .qtouch_onset = 35,
    .qtouch_offset = 20,
    .qtouch_ceiling = 200
    },
  PadSettings{ 
    .channel = 0,
    .note = 67,
    .trig_mode = trigType::keyboard,
    .velocity_curve = curveType::linear,
    .aftertouch_curve = curveType::linear,
    .piezo = 0,
    .qtouch = 1,
    .qtouch_floor = 0,
    .qtouch_debounce = 100,
    .qtouch_onset = 30,
    .qtouch_offset = 0,
    .qtouch_ceiling = 200
    },
  PadSettings{ 
    .channel = 0,
    .note = 69,
    .trig_mode = trigType::keyboard,
    .velocity_curve = curveType::linear, 
    .aftertouch_curve = curveType::linear,
    .piezo = 0,
    .qtouch = 1,
    .qtouch_floor = 0,
    .qtouch_debounce = 100,
    .qtouch_onset = 40,
    .qtouch_offset = 0,
    .qtouch_ceiling = 200
    },
  PadSettings{ 
    .channel = 0,
    .note = 60, 
  .trig_mode = trigType::keyboard,
  .velocity_curve = curveType::linear,
  .aftertouch_curve = curveType::linear, 
  .piezo = 0,
  .qtouch = 1,
  .qtouch_floor = 0,
  .qtouch_debounce = 100,
    .qtouch_onset = 5,
    .qtouch_offset = 0,
    .qtouch_ceiling = 200
  },
  PadSettings{ .channel = 0,
    .note = 71, 
    .trig_mode = trigType::keyboard,
    .velocity_curve = curveType::linear,
    .aftertouch_curve = curveType::linear,
    .piezo = 0,
    .qtouch = 1,
    .qtouch_floor = 0,
    .qtouch_debounce = 200,
    .qtouch_onset = 10,
    .qtouch_offset = 0,
    .qtouch_ceiling = 200
  }
};

extern AdvancedSettings advancedSettings =
{
  AdvancedSettings{ 
  .piezoThresholdLSB = 40,
  .piezoThresholdMSB = 0,
  .piezoSensitivityLSB = 127,
  .piezoSensitivityMSB = 7,
  .piezoDebounceTimeLSB = 40,
  .piezoDebounceTimeMSB = 0,
  .qtouchRoundOff = 15}
};


extern LIDAR Lidar =
{
  LIDAR{ .channel = 0, 
  .note = 36,
  .trig_mode = trigType::keyboard,
  .curve = curveType::linear,
  .lowThresholdLSB = 50,
  .lowThresholdMSB = 0,
  .highThresholdLSB = 116,
  .highThresholdMSB = 3,
  .controllerLSB = 10,
  .controllerMSB = 11 ,
  .enable = 1}
};

const byte SysexID[8] = {48,45,58,41,50,41,44,31}; // hexa code for ascii HEXAPAD and 1 for version




