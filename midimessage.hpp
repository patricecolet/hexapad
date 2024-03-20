#include "MIDIUSB.h"
#include "midimap.h"

class midiMessage {    
  public:
    midiMessage();
    void sendNote(PadSettings,uint8_t);
    void sendNoteOn(PadSettings,uint8_t);
    void sendNoteOff(PadSettings pad);
    void sendAfterTouch(PadSettings pad, uint8_t);
};