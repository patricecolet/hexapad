#include "midimap.h"
extern PadSettings padSettings[7] =
{
  PadSettings{ 
    .channel = 0,
    .padNote1 = {
      .qtouchThreshold = 0,
      .note = 62
    },
    .padNote2 = {
      .qtouchThreshold = 23,
      .note = 63
    },
    .padNote3 = {
      .qtouchThreshold = 35,
      .note = 74
    },
    .trig_mode = trigType::keyboard,
    .velocity_curve = curveType::linear,
    .aftertouch_curve = curveType::linear,
    .piezo = 1,
    .qtouch = 1
  },
  PadSettings{ 
    .channel = 0,
    .padNote1 = {
      .qtouchThreshold = 0,
      .note = 64
    },
    .padNote2 = {
      .qtouchThreshold = 23,
      .note = 64
    },
    .padNote3 = {
      .qtouchThreshold = 35,
      .note = 76
    },
    .trig_mode = trigType::keyboard,
    .velocity_curve = curveType::linear,
    .aftertouch_curve = curveType::linear,
    .piezo = 1,
    .qtouch = 1
  },
  PadSettings{ 
    .channel = 0,
    .padNote1 = {
      .qtouchThreshold = 0,
      .note = 65
    },
    .padNote2 = {
      .qtouchThreshold = 23,
      .note = 66
    },
    .padNote3 = {
      .qtouchThreshold = 35,
      .note = 78
    },
    .trig_mode = trigType::keyboard,
    .velocity_curve = curveType::linear,
    .aftertouch_curve = curveType::linear,
    .piezo = 1,
    .qtouch = 1},
  PadSettings{ 
    .channel = 0,
    .padNote1 = {
      .qtouchThreshold = 0,
      .note = 67
    },
    .padNote2 = {
      .qtouchThreshold = 23,
      .note = 68
    },
    .padNote3 = {
      .qtouchThreshold = 35,
      .note = 80
    },
    .trig_mode = trigType::keyboard,
    .velocity_curve = curveType::linear,
    .aftertouch_curve = curveType::linear,
    .piezo = 1,
    .qtouch = 1},
  PadSettings{ 
    .channel = 0,
    .padNote1 = {
      .qtouchThreshold = 0,
      .note = 69
    },
    .padNote2 = {
      .qtouchThreshold = 23,
      .note = 70
    },
    .padNote3 = {
      .qtouchThreshold = 35,
      .note = 82
    },
    .trig_mode = trigType::keyboard,
    .velocity_curve = curveType::linear, 
    .aftertouch_curve = curveType::linear,
    .piezo = 1,
    .qtouch = 1},
  PadSettings{ 
    .channel = 0,
    .padNote1 = {
      .qtouchThreshold = 0,
      .note = 60
    },
    .padNote2 = {
      .qtouchThreshold = 23,
      .note = 61
    },
    .padNote3 = {
      .qtouchThreshold = 35,
      .note = 72
    }, 
  .trig_mode = trigType::keyboard,
  .velocity_curve = curveType::linear,
  .aftertouch_curve = curveType::linear, 
  .piezo = 1,
  .qtouch = 1},
  PadSettings{ .channel = 0,
    .padNote1 = {
      .qtouchThreshold = 0,
      .note = 71
    },
    .padNote2 = {
      .qtouchThreshold = 23,
      .note = 71
    },
    .padNote3 = {
      .qtouchThreshold = 35,
      .note = 83
    }, 
  .trig_mode = trigType::keyboard,
  .velocity_curve = curveType::linear,
  .aftertouch_curve = curveType::linear,
  .piezo = 1,
  .qtouch = 1}
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
  .piezoRoundOff = 15}
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

const byte SysexID[8] = {48,45,58,41,50,41,44,0}; // ASCII code for 'HEXAPAD' and 0 for version


void SendMidi(int midi_channel, int controller, int value) {
  if (controller == 1) {
    padSettings[midi_channel].channel = value;
  }
  else if (controller == 2) padSettings[midi_channel].padNote1.note = value;                             // Paramétrage de la courbe de vélocité
  else if (controller == 3) padSettings[midi_channel].trig_mode = static_cast<trigType>(value);          // Paramétrage du mode des pads
  else if (controller == 4) padSettings[midi_channel].velocity_curve = static_cast<curveType>(value);    // Paramétrage de la courbe de vélocité
  else if (controller == 5) padSettings[midi_channel].aftertouch_curve = static_cast<curveType>(value);  // Paramétrage de la courbe d'AfterTouch
  else if (controller == 6) padSettings[midi_channel].piezo = value > 63;                                // Paramétrage du Piezo
  else if (controller == 7) padSettings[midi_channel].qtouch = value > 63;                               // Paramétrage des Qtouch
}




