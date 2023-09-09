//Use interrupt to optimize analogRead
//#include "Adafruit_ZeroTimer.h"
//#define COMPARE 48000
#define PLOT 0 //plot piezo reading
#include "MIDIUSB.h"
#include "MovingAverage.h"
#define UNDERTHRESHOLD 0
#define SIGNAL 1
#define RISING 2
#define PEAK 3
#define WINDOWING 4
#define SENDNOTE 5
#define FALLING 6
#define pin_t int

#include <iostream>
using namespace std;

extern bool recheckQt;
extern bool sendNote;
extern bool DoneSendNote[];

template<typename T> 
struct piezoState 
{ 
	T threshold;
  T fallingThreshold;
	T state;
	T prevstate;
	T debounceTime;
	T sensitivity;
	T peak;
	piezoState()
	{
		threshold = 17;
    fallingThreshold = 50;     // falling threshold per cent
    state = UNDERTHRESHOLD;
    prevstate = UNDERTHRESHOLD;
		debounceTime = 20;
		sensitivity = 1023;
		peak = 0;
	}
};

class piezo {
	public:
		struct MIDIAddress {
			uint8_t address : 7;
			uint8_t channel : 4;
		};
		piezo(pin_t, MIDIAddress);
		void update(uint8_t);
		void piezoNote(uint8_t);
		void noteOn(uint8_t);
		void noteOff(uint8_t);
    void playnote(int);
    int state;
    bool sendNote = 0;
	private:
		MIDIAddress _address;
    uint8_t velocity;
    pin_t _pin;
    unsigned long piezoTimer;
    int prevpiezoRead;
    //int SendVelo;
    piezoState<int> Piezo;

    MovingAverage filter;
    const int filterAmount = 2;
};
