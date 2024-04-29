#include "midimap.h"
extern PadSettings padSettings[7] =
{
  PadSettings{ .channel = 0,
    .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 62,
      .qtouchThreshold2 = 23,
      .note2 = 72,
      .qtouchThreshold3 = 35,
      .note3 = 82,
      },
    .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0,
    .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 64,
      .qtouchThreshold2 = 23,
      .note2 = 74,
      .qtouchThreshold3 = 35,
      .note3 = 84,
      },
    .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0,
      .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 65,
      .qtouchThreshold2 = 23,
      .note2 = 75,
      .qtouchThreshold3 = 35,
      .note3 = 85,
      },
    .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0,
      .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 67,
      .qtouchThreshold2 = 23,
      .note2 = 77,
      .qtouchThreshold3 = 35,
      .note3 = 87,
      },
    .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0,
      .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 69,
      .qtouchThreshold2 = 23,
      .note2 = 79,
      .qtouchThreshold3 = 35,
      .note3 = 89,
      },
    .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0,   
  .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 60,
      .qtouchThreshold2 = 23,
      .note2 = 70,
      .qtouchThreshold3 = 35,
      .note3 = 80,
      }, 
  .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0,
      .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 71,
      .qtouchThreshold2 = 23,
      .note2 = 81,
      .qtouchThreshold3 = 35,
      .note3 = 91,
      },
  .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1}
};

extern AdvancedSettings advancedSettings =
{
  AdvancedSettings{ .thresholdL = 40, .thresholdM = 0, .sensitivityL = 127, .sensitivityM = 7, .debounceTimeL = 40, .debounceTimeM = 0, .roundOff = 15}
};


extern Lidar lidar =
{
  Lidar{ .channel = 0, .note = 36 , .trig_mode = trigType::keyboard, .curve = curveType::linear, .sensor = 1, .lowThresholdL = 60, .lowThresholdM = 0, .highThresholdL = 116, .highThresholdM = 3, .controllerL = 10, .controllerM = 11}
};






