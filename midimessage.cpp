#include "midimessage.hpp"
#include "sysex.hpp"
sysex SysEx;

USBMIDI_CREATE_DEFAULT_INSTANCE();

//constructeur de la classe midiMessage
midiMessage::midiMessage(){
};

void midiMessage::sendNoteOn(midi_channel channel, midi_byte velocity, midi_note note) {
  //midiEventPacket_t event = {0x09, 0x90 | _address.channel, _address.address, velocity};
  midiEventPacket_t event = { 0x09, 0x90 | channel, note, velocity };
  MidiUSB.sendMIDI(event);
};


void midiMessage::sendNoteOff(midi_channel channel, midi_note note) {
  if (DEBUG == 1)
    Serial.printf("Note off Note: %d \n \n", note);
  midiEventPacket_t event = { 0x08, 0x80 | channel, note, 0 };
  MidiUSB.sendMIDI(event);
};


void midiMessage::sendAfterTouch(midi_channel channel, midi_byte AfterTouch, midi_note note) {
  midiEventPacket_t event = { 0x0A, 0xA0 | channel, note , AfterTouch };
  MidiUSB.sendMIDI(event);
};


void midiMessage::sendController(midi_channel channel, midi_byte controllerNumber, midi_byte ControllerValue) {
//  uint16_t filteredValue = filter.addSample(ControllerValue);
    midiEventPacket_t event = {0x0B, 0xB0 |  channel, controllerNumber, ControllerValue};
    MidiUSB.sendMIDI(event);
}

void midiMessage::begin() {
  Serial.println("MidiMessage begin");
  MIDI.begin();
  MIDI.setHandleSystemExclusive(SysEx.parse);
}



void midiMessage::update() {
  // Listen to incoming notes
  MIDI.read();
//  Serial.print(sysexPacket[0])
}
void midiMessage::sysexSend(byte * data) {
  MIDI.sendSysEx(sizeof(data), data, true);
}
