#include "midimap.h"
extern PadSettings padSettings[7] =
{
  PadSettings{ .channel = 0,
    .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 62,
      .qtouchThreshold2 = 25,
      .note2 = 72,
      .qtouchThreshold3 = 38,
      .note3 = 82,
      .qtouchThreshold4 = 50,
      .note4 = 92, },
    .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0,
    .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 64,
      .qtouchThreshold2 = 25,
      .note2 = 74,
      .qtouchThreshold3 = 38,
      .note3 = 84,
      .qtouchThreshold4 = 50,
      .note4 = 94, },
    .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0,
      .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 65,
      .qtouchThreshold2 = 25,
      .note2 = 75,
      .qtouchThreshold3 = 38,
      .note3 = 85,
      .qtouchThreshold4 = 50,
      .note4 = 95, },
    .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0,
      .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 67,
      .qtouchThreshold2 = 25,
      .note2 = 77,
      .qtouchThreshold3 = 38,
      .note3 = 87,
      .qtouchThreshold4 = 50,
      .note4 = 97, },
    .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0,
      .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 69,
      .qtouchThreshold2 = 25,
      .note2 = 79,
      .qtouchThreshold3 = 38,
      .note3 = 89,
      .qtouchThreshold4 = 50,
      .note4 = 99, },
    .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0,   
  .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 60,
      .qtouchThreshold2 = 25,
      .note2 = 70,
      .qtouchThreshold3 = 38,
      .note3 = 80,
      .qtouchThreshold4 = 50,
      .note4 = 90, }, 
  .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1},
  PadSettings{ .channel = 0,
      .padNote = {
      .qtouchThreshold1 = 0,
      .note1 = 71,
      .qtouchThreshold2 = 25,
      .note2 = 81,
      .qtouchThreshold3 = 38,
      .note3 = 91,
      .qtouchThreshold4 = 50,
      .note4 = 101, },
  .trig_mode = trigType::keyboard, .velocity_curve = curveType::linear, .aftertouch_curve = curveType::linear, .piezo = 1, .qtouch = 1}
};

extern AdvancedSettings advancedSettings =
{
  AdvancedSettings{ .threshold = 40, .sensitivityM = 31, .sensitivityL = 31, .debounceTime = 45, .roundOff = 15}
};