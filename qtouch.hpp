#pragma once

#define USB_MANUFACTURER "YOUR_NAME"
#define USB_PRODUCT "YOUR_PRODUCT"

#include "Arduino.h"
#include "Adafruit_FreeTouch.h"
#include "MIDIUSB.h"
#include "midimap.h"



enum class qtouch_state : uint8_t {
  off = 0, touched = 1, played = 2
};


class NoteQtouch {    
  public:
   
	  NoteQtouch(qtouch_pin pin, PadSettings &pad);
    void update(PadSettings);
    void begin();
    void calibrate();
    
    int getTouch();
    qtouch_state state;
    bool noteState = 0;
    uint8_t afterTouch;

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
    PadSettings _pad;
};
