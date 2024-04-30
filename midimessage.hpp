#pragma once

#include "midimap.h"
#include "USB-MIDI.h"



class midiMessage {    
  public:
    midiMessage();
//    virtual ~midiMessage();
    void init(const byte &cam);
    void begin();
    void update();
    void sendNote(PadSettings,uint8_t); // Déclaration de la fonction SendNote
    void sendNoteOn(PadSettings,uint8_t, uint8_t); // Déclaration de la fonction SendNoteOn
    void sendNoteOff(PadSettings pad, uint8_t); // Déclaration de la fonction SendNoteOff
    void sendAfterTouch(PadSettings pad, uint8_t, uint8_t); // Déclaration de la fonction SendAfterTouch
    void sendControllerLidar(int);
    void sendNoteOnLidar(int);
    void sendAfterTouchLidar(int);
    void sendNoteOffLidar();
    void midiInMessages();
  private:
    static void OnMidiSysEx(byte*, unsigned);
    // byte SysexHeader[13] = {48,45,58,41,50,41,44,30,53,45,54,31,30};
    // byte SysexHeader[13] = 'H','E','X','A','P','A','D','0','S','E','T','1','0'

};