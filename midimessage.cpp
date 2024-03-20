#include "midimessage.hpp"
/*
midiMessage::midiMessage()  {
};
*/
void midiMessage::sendNoteOn(PadSettings pad, uint8_t velo) {

          Serial.print("Note on Note: ");
          Serial.println(pad.note);
      //midiEventPacket_t event = {0x09, 0x90 | _address.channel, _address.address, velocity};
      midiEventPacket_t event = {0x09, 0x90 | pad.channel, pad.note, velo};
      MidiUSB.sendMIDI(event);
};

void midiMessage::sendNoteOff(PadSettings pad) {

          Serial.print("Note Off Note:");
          Serial.println(pad.note);
      midiEventPacket_t event = {0x08, 0x80 | pad.channel, pad.note, 0};
      MidiUSB.sendMIDI(event);
};

void midiMessage::sendAfterTouch(PadSettings pad, uint8_t afterTouch) {
      midiEventPacket_t event = {0x0A, 0xA0 | pad.channel, pad.note, afterTouch};
      MidiUSB.sendMIDI(event);
};
