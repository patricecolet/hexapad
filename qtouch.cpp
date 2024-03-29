#include "qtouch.hpp"


NoteQtouch::NoteQtouch(qtouch_pin pin, PadSettings &pad) {
  qt = Adafruit_FreeTouch(static_cast<uint8_t>(pin), OVERSAMPLE_64, RESISTOR_50K, FREQ_MODE_HOP);
  _pin = pin;
  _pad = pad;
  //Hysteresis <uint8_t> hysteresis(10);
};


void NoteQtouch::begin() {
  qt.begin();
  qt_floor = qt.measure(); // Initialisation du seuil des pads
};


void NoteQtouch::calibrate() {
  qt_floor = qt.measure();  // Calibration des pads
};


void NoteQtouch::update(PadSettings pad) {
  //int qt_measure = (( N * qt_measure ) + qt.measure() ) / ( N + 1 );
  int qt_measure = qt.measure(); 
  int roundOff; // Initialisation 
  if (pad.piezo_disabled == 0){
    roundOff = 10;
  }
  if (pad.piezo_disabled == 1){
    roundOff = 20;
  }
  // int range = 1014 - qt_floor + roundOff;
  // velocity = 127 * (qt_measure - qt_floor + roundOff) / range;
  int range = 1014 - qt_floor;
  velocity = 127 * (qt_measure - qt_floor) / range; // Calcul vélocité
  if((qt_measure > qt_floor + roundOff) && qt_memory == 0) { // Si la valeur est suppérieur au seuil
    qt_memory = qt_measure; // Memorisation de la mesure
//    sendNoteOn(velocity);
//    Serial.print("Note On"); Serial.println(_pin);
//    IgnoreNote = 0;
    if (state == qtouch_state::off && state != qtouch_state::played) state = qtouch_state::touched;
  };
//  if((qt_measure < (qt_floor + roundOff)) && qt_memory != 0) qt_memory = 0;
  if((qt_measure < (qt_floor + roundOff)) && qt_memory != 0) {  // Si la valeur est inférieur au seuil
    qt_memory = 0; // Aucune mémorisation
//    sendNoteOff();
    state = qtouch_state::off; // Statue du pad off
//    sendAfterTouch();
  }
  if((qt_memory > 0) && (qt_memory != qt_measure)) { // Aftertouch > Premier mesure
      qt_memory = qt_measure;
      afterTouch = velocity * 2; // Amplification de l'aftertouch
      afterTouch = velocity;
      if (afterTouch > 127) afterTouch = 127; // Saturation de la vélocité a 127
    }
};

int NoteQtouch::getTouch() {
  int qt_measure = qt.measure();
  int roundOff = 10;
  int range = 1014 - qt_floor + roundOff; // Calcul seuil
  velocity = 127 * (qt_measure - qt_floor + roundOff) / range;
  return velocity; // Renvoie de la vélocité
};
