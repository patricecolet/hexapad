#pragma once

#include "Arduino.h"
#include "Adafruit_FreeTouch.h"
#include "MIDIUSB.h"
#include "midimap.h"


enum class qtouch_state : uint8_t {
  off = 0, touched = 1, played = 2
};

class CCQtouch {    
  public:
    struct MIDIAddress {
      uint8_t address : 7;
      uint8_t channel : 4;
    };   
	  CCQtouch(int, MIDIAddress);
    void sendController();
    void loop(); 
    void begin();
    void calibrate();
  private:   
    Adafruit_FreeTouch qt;
    uint8_t CCvalue;
    MIDIAddress _address;
    int qt_floor;
};


class NoteQtouch {    
  public:
   
	  NoteQtouch(qtouch_pin pin, PadSettings &pad);
    void sendNoteOn(uint8_t);
    void sendNoteOff();
    void sendAfterTouch(uint8_t);
    void update();
    void begin();
    void calibrate();
    
    int getTouch();
    qtouch_state state;
    bool noteState = 0;

    enum class parameters : uint8_t {
      channel = 0,
      note = 60,
      trigMode = 1,
      curve = 0,
      disable = 0 
};

  private:   
    Adafruit_FreeTouch qt;
    uint8_t velocity;
    
    uint8_t velopiezo;
    qtouch_pin _pin;
    int qt_floor, qt_memory;
    int afterTouch;
    PadSettings _pad;

};
