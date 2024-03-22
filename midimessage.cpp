#include "midimessage.hpp"

midiMessage::midiMessage()  {
};

void midiMessage::sendNoteOn(PadSettings pad, uint8_t velocity) {
 
  uint8_t velo = 0;
  if(pad.velocity_curve == curveType::linear) {
    velo = velocity;
  }
  else if(pad.velocity_curve == curveType::parabola) {
    velo = ((127*(velocity)^2)/127^2);
  }
  else if(pad.velocity_curve == curveType::hyperbola) {
    velo = round(127*(1-exp(-1.5*velocity/40)));
  }
  else if(pad.velocity_curve == curveType::sigmoid) {
    velo = round(127/(1+exp(-0.08*(velocity-65))));
  }
          Serial.print("Note on Note: \n");
          Serial.println(pad.note);
          /*
          Serial.print("Channel On: \n");
          Serial.println(pad.channel);*/
      //midiEventPacket_t event = {0x09, 0x90 | _address.channel, _address.address, velocity};
      midiEventPacket_t event = {0x09, 0x90 | pad.channel, pad.note, velo};
      MidiUSB.sendMIDI(event);
};


void midiMessage::sendNoteOff(PadSettings pad) {

          Serial.print("Note Off Note: \n");
          Serial.println(pad.note);
          /*
          Serial.print("Channel Off: \n");
          Serial.println(pad.channel);
          */
      midiEventPacket_t event = {0x08, 0x80 | pad.channel, pad.note, 0};
      MidiUSB.sendMIDI(event);
};


void midiMessage::sendAfterTouch(PadSettings pad, uint8_t afterTouch) {
      midiEventPacket_t event = {0x0A, 0xA0 | pad.channel, pad.note, afterTouch};
      MidiUSB.sendMIDI(event);
};
