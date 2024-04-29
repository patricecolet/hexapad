#include "midimap.h"


class sysex {    
  public:
    sysex();
    void update();
    void sysexID(); // Déclaration de la fonction SendNote
    void set(PadSettings); // Déclaration de la fonction SendNoteOn
    void dump(PadSettings); // Déclaration de la fonction SendNoteOff
    void parseMethod();
  private:
};