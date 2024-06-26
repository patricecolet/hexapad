#pragma once

//#define PLOT 0 //plot piezo reading
#include "MIDIUSB.h"
#include "MovingAverage.h"
#include "midimap.h"

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
		threshold = 35;
    fallingThreshold = 40;     // falling threshold per cent
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
		void update();
    void playnote(int);
    int state;
    bool sendNote = 0;
    uint8_t velocity;
    
	private:
		MIDIAddress _address;
    pin_t _pin;
    unsigned long piezoTimer;
    int prevpiezoRead;
    piezoState<int> Piezo;
};
