uint8_t padSettings[7][7] = {
  {
  0,  // ctl 1 MIDI channel
  62, // ctl 2  MIDI note
  1,  // ctl 3  Trig mode (percu,key,button)
  0,  // ctl 4  Velocity curve
  0,  // ctl 5  Aftertouch curve
  0,  // ctl 6  Disable piezo
  0 }, // ctl 7 Disable QTouch (MIDI note is QT1)
  { 0,64,1,0,0,0,0 },
  { 0,65,1,0,0,0,0 },
  { 0,69,1,0,0,0,0 },
  { 0,67,1,0,0,0,0 },
  { 0,60,1,0,0,0,0 },
  { 0,71,1,0,0,0,0 }
};

uint8_t rangeSettings[14] = {
  0,  // ctl 1   MIDI channel
  48, // ctl 2  MIDI note (mode single note or button or first scale note, modulate velocity)
  0,  // ctl 3  Trig mode (range CTL, single note, button, note scale)
  0,  // ctl 4  Curve
  0,  // ctl 5  Disable sensor
  0,  // ctl 6  LOW threshold(mm) LSB
  48, // ctl 7  LOW threshold(mm) MSB
  0,  // ctl 8  HIGH threshold(mm) LSB
  0,  // ctl 9  HIGH threshold(mm) MSB
  0,  // ctl 10 MIDI controller LSB
  0,  // ctl 11 MIDI controller MSB
  48, // ctl 12 Scale LSB
  0,  // ctl 13 Scale MSB
  0  //  ctl 14 SCale octaves
};

