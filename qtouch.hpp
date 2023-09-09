#ifndef Qtouch_hpp  
#define Qtouch_hpp
#include "Arduino.h"
#include "Adafruit_FreeTouch.h"
//#include "Hysteresis.h"
#include "MIDIUSB.h"

#define QT1 A0
#define QT2 A1
#define QT3 A6
#define QT4 A7
#define QT5 A8
#define QT6 A9
#define QT7 A10


#define QT_TOUCHED 1
#define QT_PLAYED 2
#define QT_OFF 0

#define QT_TRIG_PERCUSSION 0
#define QT_TRIG_KEYBOARD 1
/*
#define CHANNEL_1 0
#define CHANNEL_2 1
#define CHANNEL_3 2
#define CHANNEL_4 4
#define CHANNEL_5 5
#define CHANNEL_6 6
#define CHANNEL_7 7
#define CHANNEL_8 8
#define CHANNEL_9 9
#define CHANNEL_10 10
#define CHANNEL_11 11
#define CHANNEL_12 12
#define CHANNEL_13 13
#define CHANNEL_14 14
#define CHANNEL_15 15
#define CHANNEL_16 16
*/
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
    struct MIDIAddress {
      uint8_t address : 7;
      uint8_t channel : 4;
    };   
	  NoteQtouch(int, MIDIAddress);
    void sendNoteOn(uint8_t);
    void sendNoteOff();
    void sendAfterTouch(uint8_t);
    void update();
    void begin();
    void calibrate();
    uint8_t getState();
    int getTouch();
    uint8_t trigMode;
    uint8_t note;
    uint8_t state;
    bool noteState = 0;
  private:   
    Adafruit_FreeTouch qt;
    uint8_t velocity;
    void setState(uint8_t);
    uint8_t velopiezo;
    MIDIAddress _address;
    int _pin;
    int qt_floor, qt_memory;
    int afterTouch;

};


#endif
