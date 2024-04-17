
#include "midimap.h"
extern PadSettings padSettings[7] =
{
  PadSettings{ .channel = 0, .note = 62, .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0, .note = 64, .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0, .note = 65, .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0, .note = 67, .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0, .note = 69, .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0, .note = 60, .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0, .note = 71, .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1}
};

extern AdvancedSettings advancedSettings =
{
  AdvancedSettings{ .threshold = 40, .sensitivityM = 31, .sensitivityL = 31, .debounceTime = 30, .roundOff = 15}
};
