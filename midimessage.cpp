#include "midimessage.hpp"

midiMessage::midiMessage()  {
};

void midiMessage::sendNoteOn(PadSettings pad, uint8_t velocity) {
 
  uint8_t velo = 0;
  if(pad.velocity_curve == curveType::linear) { // Type de courbe linéaire
    velo = velocity;
  }
  else if(pad.velocity_curve == curveType::parabola) { // Type de courbe parabolique
    velo = (127*velocity*velocity)/(127*127);
  }
  else if(pad.velocity_curve == curveType::hyperbola) { // Type de courbe hyoerbolique
    velo = round(127*(1-exp(-1.5*velocity/40)));
  }
  else if(pad.velocity_curve == curveType::sigmoid) { // Type de courbe sigmoide
    velo = round(127/(1+exp(-0.08*(velocity-65))));
  }
          Serial.printf("Note on Note: %d \n", pad.note);
          Serial.print("Velocity:");
          Serial.println(velocity);
          if (pad.velocity_curve != curveType::linear){
            Serial.print("Velocity curve:");
            Serial.println(velo);
          }
      //midiEventPacket_t event = {0x09, 0x90 | _address.channel, _address.address, velocity};
      midiEventPacket_t event = {0x09, 0x90 | pad.channel, pad.note, velo};
      MidiUSB.sendMIDI(event);
};


void midiMessage::sendNoteOff(PadSettings pad) {

          Serial.printf("Note off Note: %d \n", pad.note);
      midiEventPacket_t event = {0x08, 0x80 | pad.channel, pad.note, 0};
      MidiUSB.sendMIDI(event);
};


void midiMessage::sendAfterTouch(PadSettings pad, uint8_t afterTouch) {
      midiEventPacket_t event = {0x0A, 0xA0 | pad.channel, pad.note, afterTouch};
      MidiUSB.sendMIDI(event);
};
