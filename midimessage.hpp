#pragma once

#include "midimap.h"
#include "USB-MIDI.h"
#include "sysex.hpp"



class midiMessage {    
  public:
    midiMessage();
    void begin();
    void update();
    void sendNote(midi_channel,midi_byte); // Déclaration de la fonction SendNote
    void sendNoteOn(midi_channel,midi_note, midi_byte); // Déclaration de la fonction SendNoteOn
    void sendNoteOff(midi_channel, midi_note); // Déclaration de la fonction SendNoteOff
    void sendAfterTouch(midi_channel, midi_byte, midi_note); // Déclaration de la fonction SendAfterTouch
    void sendController(midi_channel, midi_byte, midi_byte);
    void sysexSend(byte *);
  private:
    static void OnMidiSysEx(byte*, unsigned);
    //void midiInMessages();
};