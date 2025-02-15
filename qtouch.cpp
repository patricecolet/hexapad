#include "qtouch.hpp"
MovingAverage filter(10);

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
  if((qt_measure > (qt_floor + advancedSettings.qtouchRoundOff + pad.qtouch_onset)) && qt_memory == 0) { // Si la valeur est suppérieur au seuil
    qt_memory = qt_measure; // Memorisation de la mesure

    if (state == qtouch_state::off && state != qtouch_state::played && (millis() > pad.qtouch_debounce)) state = qtouch_state::touched;
  };
  if((qt_measure < (qt_floor + advancedSettings.qtouchRoundOff + pad.qtouch_offset)) && qt_memory != 0 && (millis() > pad.qtouch_debounce)) {  // Si la valeur est inférieur au seuil et antibounce
    qt_memory = 0; // Aucune mémorisation
    state = qtouch_state::off; // Statue du pad off
    pad.qtouch_debounce = millis();
  }
  if((qt_memory > 0) && (qt_memory != qt_measure)) { // Aftertouch > Premier mesure
      qt_memory = qt_measure;
      // Calcul aftertouch

//      int range = 1014 - qt_floor;
//      velocity = 127 * (qt_measure - qt_floor  + pad.qtouch_offset) / range;
//      afterTouch = velocity;
      Serial.printf("qt_measure: %i \n", qt_measure);
      velocity = map(qt_measure,(qt_floor  + pad.qtouch_offset), (1014 - pad.qtouch_ceiling), 0, 127);
      Serial.printf("velocity: %i \n", velocity);
      if (velocity > 127) velocity = 127; // Saturation de la vélocité a 127
      afterTouch = filter.addSample(velocity);
    }
};

