#include "midimap.h"
extern PadSettings padSettings[7] =
{
  PadSettings{ .channel = 0, .note = 62,
    .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 62,
      .qtouchThreshold2 = 25,
      .note2 = 62,
      .qtouchThreshold3 = 25,
      .note3 = 62,
      .qtouchThreshold4 = 25,
      .note4 = 62, },
    .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0, .note = 64,
    .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 62,
      .qtouchThreshold2 = 25,
      .note2 = 62,
      .qtouchThreshold3 = 25,
      .note3 = 62,
      .qtouchThreshold4 = 25,
      .note4 = 62, },
    .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0, .note = 65,
      .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 62,
      .qtouchThreshold2 = 25,
      .note2 = 62,
      .qtouchThreshold3 = 25,
      .note3 = 62,
      .qtouchThreshold4 = 25,
      .note4 = 62, },
    .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0, .note = 67,
      .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 62,
      .qtouchThreshold2 = 25,
      .note2 = 62,
      .qtouchThreshold3 = 25,
      .note3 = 62,
      .qtouchThreshold4 = 25,
      .note4 = 62, },
    .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0, .note = 69,    .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 62,
      .qtouchThreshold2 = 25,
      .note2 = 62,
      .qtouchThreshold3 = 25,
      .note3 = 62,
      .qtouchThreshold4 = 25,
      .note4 = 62, },
    .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0, .note = 60,    
  .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 62,
      .qtouchThreshold2 = 25,
      .note2 = 62,
      .qtouchThreshold3 = 25,
      .note3 = 62,
      .qtouchThreshold4 = 25,
      .note4 = 62, }, 
  .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0, .note = 71,
      .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 62,
      .qtouchThreshold2 = 25,
      .note2 = 62,
      .qtouchThreshold3 = 25,
      .note3 = 62,
      .qtouchThreshold4 = 25,
      .note4 = 62, },
  .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1}
};

extern AdvancedSettings advancedSettings =
{
  AdvancedSettings{ .threshold = 40, .sensitivityM = 31, .sensitivityL = 31, .debounceTime = 30, .roundOff = 15}
};