#pragma once
#include "midimap.h"
#include "midimessage.hpp"

class sysex {    
  public:
    sysex();
    static void parse(byte*,unsigned);
  private:
    static bool checkID(byte*); 
    static void set(byte*);
    static void get(byte*);
    static void calibrate();
    static void pad(byte, byte*);
    static void lidar(byte*);
    static void advanced(byte*);
    static void dump(byte*);
};