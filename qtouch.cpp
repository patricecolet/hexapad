#include "qtouch.hpp"

CCQtouch::CCQtouch(int pin, MIDIAddress address) {
  qt = Adafruit_FreeTouch(pin, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
  _address = address;
}

void CCQtouch::begin() {
  qt.begin();
  qt_floor = qt.measure();
};

void CCQtouch::calibrate(){
  qt_floor = qt.measure();
};

void CCQtouch::loop() {
  //int qt_measure = (( N * qt_measure ) + qt.measure() ) / ( N + 1 );
  int qt_measure = qt.measure();
  // set roundoff at instantiation
  int roundOff = 25;
  int range = 1014 - qt_floor + roundOff;
  CCvalue = 127 * (qt_measure - qt_floor + roundOff) / range;
  if(qt_measure > qt_floor + roundOff) {
    sendController();
  };
};

void CCQtouch::sendController() {
      midiEventPacket_t event = {0x0B, 0xB0 | _address.channel, _address.address, CCvalue};
      MidiUSB.sendMIDI(event);
};

NoteQtouch::NoteQtouch(qtouch_pin pin, PadSettings &pad) {
  qt = Adafruit_FreeTouch(static_cast<uint8_t>(pin), OVERSAMPLE_64, RESISTOR_50K, FREQ_MODE_HOP);
  _pin = pin;
  _pad = pad;
  //Hysteresis <uint8_t> hysteresis(10);
};

void NoteQtouch::begin() {
  qt.begin();
  qt_floor = qt.measure();
};

void NoteQtouch::calibrate() {
  qt_floor = qt.measure();
};

void NoteQtouch::update() {
  //int qt_measure = (( N * qt_measure ) + qt.measure() ) / ( N + 1 );
  int qt_measure = qt.measure();
  int roundOff = 10;
  // int range = 1014 - qt_floor + roundOff;
  // velocity = 127 * (qt_measure - qt_floor + roundOff) / range;
  int range = 1014 - qt_floor;
  velocity = 127 * (qt_measure - qt_floor) / range;
  if((qt_measure > qt_floor + roundOff) && qt_memory == 0) {
    qt_memory = qt_measure;
//    sendNoteOn(velocity);
//    Serial.print("Note On"); Serial.println(_pin);
//    IgnoreNote = 0;
    if (state == qtouch_state::off && state != qtouch_state::played) state = qtouch_state::touched;
  };
//  if((qt_measure < (qt_floor + roundOff)) && qt_memory != 0) qt_memory = 0;
  if((qt_measure < (qt_floor + roundOff)) && qt_memory != 0) {
    qt_memory = 0;
//    sendNoteOff();
    state = qtouch_state::off;
//    sendAfterTouch();
  }
  if((qt_memory > 0) && (qt_memory != qt_measure)) {
      qt_memory = qt_measure;
      afterTouch = velocity * 2;
      afterTouch = velocity;
      if (afterTouch > 127) afterTouch = 127;
      if (state == qtouch_state::played) sendAfterTouch(afterTouch);
    }
};

int NoteQtouch::getTouch() {
  int qt_measure = qt.measure();
  int roundOff = 10;
  int range = 1014 - qt_floor + roundOff;
  velocity = 127 * (qt_measure - qt_floor + roundOff) / range;
  return velocity;
};


void NoteQtouch::sendNoteOn(uint8_t velo) {
      //midiEventPacket_t event = {0x09, 0x90 | _address.channel, _address.address, velocity};
      midiEventPacket_t event = {0x09, 0x90 | _pad.channel, _pad.note, velo};
      MidiUSB.sendMIDI(event);
};

void NoteQtouch::sendNoteOff() {
      midiEventPacket_t event = {0x08, 0x80 | _pad.channel, _pad.note, 0};
      MidiUSB.sendMIDI(event);
};

void NoteQtouch::sendAfterTouch(uint8_t afterTouch) {
      midiEventPacket_t event = {0x0A, 0xA0 | _pad.channel, _pad.note, afterTouch};
      MidiUSB.sendMIDI(event);
};
