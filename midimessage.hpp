#include "MIDIUSB.h"
#include "midimap.h"

class midiMessage {    
  public:
    midiMessage();
    void sendNote(PadSettings,uint8_t); // Déclaration de la fonction SendNote
    void sendNoteOn(PadSettings,uint8_t); // Déclaration de la fonction SendNoteOn
    void sendNoteOff(PadSettings pad); // Déclaration de la fonction SendNoteOff
    void sendAfterTouch(PadSettings pad, uint8_t); // Déclaration de la fonction SendAfterTouch
};
