#include "midimessage.hpp"
#include "USB-MIDI.h"
#include <string>
USBMIDI_CREATE_DEFAULT_INSTANCE();

const char *midiMessage::SysexHeader = "HEXAPAD0";
void SendMidi(int, int, int);

midiMessage::midiMessage()  {
};

void midiMessage::sendNoteOn(PadSettings pad, uint8_t velocity) {
 
  uint8_t velo = 0;
  if(pad.velocity_curve == curveType::linear) { // Type de courbe linéaire
    velo = velocity;
  }
  else if(pad.velocity_curve == curveType::parabola) { // Type de courbe parabolique
    velo = (127*velocity*velocity)/(127*127);
  }
  else if(pad.velocity_curve == curveType::hyperbola) { // Type de courbe hyoerbolique
    velo = round(127*(1-exp(-1.5*velocity/40)));
  }
  else if(pad.velocity_curve == curveType::sigmoid) { // Type de courbe sigmoide
    velo = round(127/(1+exp(-0.08*(velocity-65))));
  }
  if (DEBUG == 1){
          Serial.printf("Note on Note: %d \n", pad.note);
          Serial.print("Velocity:");
          Serial.println(velocity);
  
          if (pad.velocity_curve != curveType::linear){
            Serial.print("Velocity curve:");
            Serial.println(velo);
          }
  }
      
      //midiEventPacket_t event = {0x09, 0x90 | _address.channel, _address.address, velocity};
      midiEventPacket_t event = {0x09, 0x90 | pad.channel, pad.note, velo};
      MidiUSB.sendMIDI(event);
      
};


void midiMessage::sendNoteOff(PadSettings pad) {
      if (DEBUG == 1)
        Serial.printf("Note off Note: %d \n \n", pad.note);
      midiEventPacket_t event = {0x08, 0x80 | pad.channel, pad.note, 0};
      MidiUSB.sendMIDI(event);
};



void midiMessage::sendAfterTouch(PadSettings pad, uint8_t afterTouch) {
      midiEventPacket_t event = {0x0A, 0xA0 | pad.channel, pad.note, afterTouch};
      MidiUSB.sendMIDI(event);
};



void midiMessage::begin() {
    Serial.println("MidiMessage begin");
    MIDI.begin();
    MIDI.setHandleSystemExclusive(OnMidiSysEx);
}



void midiMessage::update() {
  // Listen to incoming notes
  MIDI.read();
}



void midiMessage::OnMidiSysEx(byte* data, unsigned length) {
  int commandeSysex, versionSysex, revisionSysex, channelSysex, controllerSysex, valueSysex;
  Serial.print(F("SYSEX: ("));
  Serial.print(length);
  Serial.print(F(" bytes) \n"));
  for (uint16_t i = 1; i <= 8; i++){
    if ((char)data[i] == SysexHeader[i-1]){
      Serial.printf("%c",data[i]);
    }
    else{
      Serial.printf("ERREUR \n");
    }
  }
  commandeSysex = data[9];

  if (commandeSysex == 1){
    Serial.printf("\nCommande = SET \n");
  }
  if (commandeSysex == 2){
    Serial.printf("\nCommande = GET \n");
  }
  versionSysex = data[10];
  Serial.printf("Version = %d \n", versionSysex);
  revisionSysex = data[11];
  Serial.printf("Revision = %d \n", channelSysex);
  channelSysex = data[12];
  Serial.printf("Channel = %d \n", channelSysex);
  controllerSysex = data[13];
  Serial.printf("Controller = %d \n", controllerSysex);
  valueSysex = data[14];
  Serial.printf("Value = %d \n \n", valueSysex);
  /*
  if (controllerSysex == 0){
    for (int i = 0; i <= 6; i++){
      MIDI.sendSysEx(sizeof(PadSettings), PadSettings, true);
    }
  }
  */
  if (channelSysex < 7 && controllerSysex < 8) {
    SendMidi(channelSysex - 1, controllerSysex, valueSysex);
  }
  if (channelSysex == 14 && controllerSysex < 5) {
    if (controllerSysex == 1) advancedSettings.threshold = valueSysex;
    else if (controllerSysex == 2) advancedSettings.sensitivityM = valueSysex;
    else if (controllerSysex == 3) advancedSettings.sensitivityL = valueSysex;
    else if (controllerSysex == 4) advancedSettings.debounceTime = valueSysex;
    else if (controllerSysex == 5) advancedSettings.roundOff = valueSysex;
  }
  if (channelSysex == 16 && controllerSysex < 8) {
    for (int i = 0; i <= 6; i++){
      SendMidi(i, controllerSysex, valueSysex);
    }
  }
}



void SendMidi(int midi_channel, int controller, int value){
  if (controller == 1) {
       padSettings[midi_channel].channel = value;
  }
  else if (controller == 2) padSettings[midi_channel].note = value; // Paramétrage de la courbe de vélocité
  else if (controller == 3) padSettings[midi_channel].trig_mode = static_cast<trigType>(value); // Paramétrage du mode des pads
  else if (controller == 4) padSettings[midi_channel].velocity_curve = static_cast<curveType>(value); // Paramétrage de la courbe de vélocité
  else if (controller == 5) padSettings[midi_channel].aftertouch_curve = static_cast<curveType>(value); // Paramétrage de la courbe d'AfterTouch
  else if (controller == 6) padSettings[midi_channel].piezo = value > 63; // Paramétrage du Piezo
  else if (controller == 7) padSettings[midi_channel].qtouch = value > 63; // Paramétrage des Qtouch
}

/*
// hexapad settings can be done with MIDI messages:
void midiMessage::midiInMessages() {
    midiEventPacket_t midirx;
  // read the midi note
  midirx = MidiUSB.read();
  char midiheader = midirx.header;
  uint8_t midi_channel = int(midirx.byte1 & 0XF);

  switch(midiheader) {
    case 0x0B : {// On MIDI controller
      uint8_t controller =  int(midirx.byte2);
      uint8_t value =  int(midirx.byte3);
      /*
      Serial.print("Value \n");
      Serial.println(value);
      Serial.print("Controller \n");
      Serial.println(controller);
      Serial.print("Midi Channel \n");
      Serial.println(midi_channel);
    
      if (midi_channel < 8 && controller < 8) {
        SendMidi(midi_channel, controller, value);
      }
      if (midi_channel >= 13 && controller < 5) {
        if (controller == 1) advancedSettings.threshold = value;
        else if (controller == 2) advancedSettings.sensitivityM = value;
        else if (controller == 3) advancedSettings.sensitivityL = value;
        else if (controller == 4) advancedSettings.debounceTime = value;
        else if (controller == 5) advancedSettings.roundOff = value;
      }
      if (midi_channel >= 15 && controller < 8) {
        for (int i = 0; i <= 6; i++){
          SendMidi(i, controller, value);
        }
      }
    }
      break;
    case 0x08 : {// On MIDI note off
      char midinote =  midirx.byte2;
      char midivelocity =  midirx.byte3;
        if (midinote == 0x3c) {             // C4 to calibrate qtouch
          //Serial.println("calibrating...");
          delay(100);
          //qTouchCalibrate();
          //Distance.restart();
        }
    }
      break;
    default:
    break;
  }     
}
*/
