#pragma once

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
  T state;
  T prevstate;
  T peak;
  T fallingThreshold;
  piezoState()
  {
    fallingThreshold = 40;
    state = UNDERTHRESHOLD; // Initialisation de l'état initial
    prevstate = UNDERTHRESHOLD; // Initialisation de la valeur précédente
    peak = 0;
  }
};

class piezo {
  public:
    piezo(pin_t);
    void update();
    int state;
//    bool sendNote = 0;
    double velocity;
    int level;
    int sensitivityMSB, sensitivityLSB, sensitivity, thresholdMSB, thresholdLSB, threshold, debounceTimeMSB, debounceTimeLSB, debounceTime;
    
  private:
    pin_t _pin;
    unsigned long piezoTimer;
    int prevpiezoRead;
    piezoState<int> Piezo;
    int piezoRead;
    void updateNote();
};
