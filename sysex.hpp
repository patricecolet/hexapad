#pragma once
#include "midimap.h"
#include "midimessage.hpp"


class sysex {    
  public:
    sysex();
    static void parse(byte*,unsigned); // Déclaration de la fonction SendNote
  private:
    static bool checkID(byte*); // Déclaration de la fonction SendNoteOn
    static void set(byte*); // Déclaration de la fonction SendNoteOn
    static void pad(byte, byte*); // Déclaration de la fonction SendNoteOn
    static void lidar(byte*); // Déclaration de la fonction SendNoteOn
    static void advanced(byte*); // Déclaration de la fonction SendNoteOn
    static void dump(); // Déclaration de la fonction SendNoteOff
};