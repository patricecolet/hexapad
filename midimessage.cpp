#include "midimessage.hpp"
#include "USB-MIDI.h"
#include <string>
USBMIDI_CREATE_DEFAULT_INSTANCE();

const char* midiMessage::SysexHeader = "HEXAPAD0";
void SendMidi(int, int, int);
byte padSettingsBytes[sizeof(PadSettings) * 7 + 2];
byte advancedSettingsBytes[sizeof(AdvancedSettings) + 2];
int noteState[7] = { 0, 0, 0, 0, 0, 0, 0 };

midiMessage::midiMessage(){};

void midiMessage::sendNoteOn(PadSettings pad, uint8_t velocity, uint8_t AfterTouch, int channel) {
  uint8_t velo;
  if (pad.velocity_curve == curveType::linear) {  // Type de courbe linéaire
    velo = velocity;
  } else if (pad.velocity_curve == curveType::parabola) {  // Type de courbe parabolique
    velo = (127 * velocity * velocity) / (127 * 127);
  } else if (pad.velocity_curve == curveType::hyperbola) {  // Type de courbe hyoerbolique
    velo = round(127 * (1 - exp(-1.5 * velocity / 40)));
  } else if (pad.velocity_curve == curveType::sigmoid) {  // Type de courbe sigmoide
    velo = round(127 / (1 + exp(-0.08 * (velocity - 65))));
  }
  if (DEBUG == 1) {
    Serial.printf("Note on Note: %d \n", AfterTouchNote(pad, AfterTouch, channel));
    Serial.print("Velocity:");
    Serial.println(velocity);

    if (pad.velocity_curve != curveType::linear) {
      Serial.print("Velocity curve:");
      Serial.println(velo);
    }
  }
  //midiEventPacket_t event = {0x09, 0x90 | _address.channel, _address.address, velocity};
  midiEventPacket_t event = { 0x09, 0x90 | pad.channel, AfterTouchNote(pad, AfterTouch, channel), velo };
  MidiUSB.sendMIDI(event);
};


void midiMessage::sendNoteOff(PadSettings pad, uint8_t AfterTouch, int channel) {
  if (DEBUG == 1)
    Serial.printf("Note off Note: %d \n \n", noteState[channel]);
  midiEventPacket_t event = { 0x08, 0x80 | pad.channel, noteState[channel], 0 };
  MidiUSB.sendMIDI(event);
};


void midiMessage::sendAfterTouch(PadSettings pad, uint8_t AfterTouch) {
  midiEventPacket_t event = { 0x0A, 0xA0 | pad.channel, AfterTouchNote(pad, AfterTouch, 100), AfterTouch };
  MidiUSB.sendMIDI(event);
};


int midiMessage::AfterTouchNote(PadSettings pad, uint8_t afterTouch, int channel) {
  float pourcentage = 127/100;
  int note = 0;
  if (afterTouch >= pad.padNote.qtouchThreshold1*pourcentage && afterTouch < pad.padNote.qtouchThreshold2*pourcentage){
    note = pad.padNote.note1;
  }
  else if (afterTouch >= pad.padNote.qtouchThreshold2*pourcentage && afterTouch < pad.padNote.qtouchThreshold3*pourcentage){
    note = pad.padNote.note2;
  }
  else if (afterTouch >= pad.padNote.qtouchThreshold3*pourcentage){
    note = pad.padNote.note3;
  }
  noteState[channel] = note;
  return note;
}

void midiMessage::sendControllerLidar(int ControllerValue) {
//  uint16_t filteredValue = filter.addSample(ControllerValue);
    byte lowValue = ControllerValue & 0x7F;
    byte highValue = ControllerValue >> 7;
    midiEventPacket_t event_lsb = {0x0B, 0xB0 |  lidar.channel, lidar.controllerL, lowValue};
    MidiUSB.sendMIDI(event_lsb);
    midiEventPacket_t event_msb = {0x0B, 0xB0 |  lidar.channel, lidar.controllerM, highValue};
    MidiUSB.sendMIDI(event_msb);
}

void midiMessage::sendNoteOnLidar(int velocity) {
  uint8_t velo;
  if (lidar.curve == curveType::linear) {  // Type de courbe linéaire
    velo = velocity;
  } else if (lidar.curve == curveType::parabola) {  // Type de courbe parabolique
    velo = (127 * velocity * velocity) / (127 * 127);
  } else if (lidar.curve == curveType::hyperbola) {  // Type de courbe hyoerbolique
    velo = round(127 * (1 - exp(-1.5 * velocity / 40)));
  } else if (lidar.curve == curveType::sigmoid) {  // Type de courbe sigmoide
    velo = round(127 / (1 + exp(-0.08 * (velocity - 65))));
  }
  midiEventPacket_t event = { 0x0C, 0xC0 | lidar.channel, lidar.note, velo };
  MidiUSB.sendMIDI(event);
  printf("Velocity lidar = %d\n", velocity);
}


void midiMessage::sendNoteOffLidar() {
  midiEventPacket_t event = { 0x0D, 0xD0 | lidar.channel, lidar.note, 0 };
  MidiUSB.sendMIDI(event);
}


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
  bool status = 1;
  if (DEBUG == 1) {
    Serial.print(F("SYSEX: ("));
    Serial.print(length);
    Serial.print(F(" bytes) \n"));
    for (uint16_t i = 1; i <= 8; i++) {
      if (status == 1 && (char)data[i] == SysexHeader[i - 1]) {
        Serial.printf("%c", data[i]);
      }
      if ((char)data[i] != SysexHeader[i - 1]) {
        Serial.printf("\nERREUR \n");
        status = 0;
      }
    }
  }
  if (status != 0) {
    commandeSysex = data[9];
    if (commandeSysex == 1 && DEBUG == 1) {
      Serial.printf("\nCommande = SET \n");
    }
    if (commandeSysex == 2 && DEBUG == 1) {
      Serial.printf("\nCommande = GET \n");
    }
    versionSysex = data[10];
    revisionSysex = data[11];
    channelSysex = data[12];
    controllerSysex = data[13];
    valueSysex = data[14];
    if (DEBUG == 1) {
      Serial.printf("Version = %d \nRevision = %d \nChannel = %d \nController = %d \nValue = % d \n \n", versionSysex, revisionSysex, channelSysex, controllerSysex, valueSysex);
    }
    if (channelSysex <= 7 && (controllerSysex < 8 || controllerSysex == 0)) {
      if (controllerSysex == 0 && commandeSysex == 2) {
        padSettingsBytes[0] = 0xF0;                                                                      // Début du message Sysex  
        memcpy(&padSettingsBytes[1], padSettings, sizeof(PadSettings) * 7);                              // Création du tableau AdvancedSettings en Bytes
        padSettingsBytes[sizeof(padSettingsBytes) - 1] = 0xF7;                                           // Fin du message Sysex
        MIDI.sendSysEx(sizeof(padSettingsBytes), padSettingsBytes, true);                                // Envoie du tableau PadSettings en Sysex
        if (DEBUG == 1) {
          Serial.printf("Taille du tableau PadSettingsBytes = %d \n", sizeof(padSettingsBytes));
          Serial.printf("%d \n", padSettingsBytes[0]);
          for (int i = 2; i <= sizeof(padSettingsBytes); i++) {
            Serial.printf("%d, ", padSettingsBytes[i - 1]);                                              // Affichage du tableau PadSettings
            if ((i - 1) % 27 == 0) {
              Serial.printf("\n");
            }
          }
        }
      }
      if (controllerSysex < 8 && commandeSysex == 1) {
        SendMidi(channelSysex - 1, controllerSysex, valueSysex);                                         // Appelle a la fonction SendMidi
      }
    }

    if (channelSysex == 14 && (controllerSysex < 6 || controllerSysex == 0)) {
      if (controllerSysex == 0 && commandeSysex == 2) {
        advancedSettingsBytes[0] = 0xF0;                                                                 // Début du message Sysex
        memcpy(&advancedSettingsBytes[1], &advancedSettings, sizeof(AdvancedSettings));                  // Création du tableau AdvancedSettings en Bytes
        advancedSettingsBytes[sizeof(advancedSettingsBytes) - 1] = 0xF7;                                 // Fin du message Sysex
        MIDI.sendSysEx(sizeof(advancedSettingsBytes), advancedSettingsBytes, true);                      // Envoie du tableau AdvancedSettings en Sysex
        if (DEBUG == 1) {
          Serial.printf("Taille du tableau advancedSettingsBytes = %d \n", sizeof(advancedSettingsBytes));
          for (int i = 1; i <= sizeof(advancedSettingsBytes); i++) {
            Serial.printf("%d, ", advancedSettingsBytes[i - 1]);                                         // Affichage du tableau AdvancedSettings
          }
        }
      } 
      else if (controllerSysex == 1 && commandeSysex == 1) advancedSettings.thresholdL = valueSysex;    // Paramétrage du seuil
      else if (controllerSysex == 2 && commandeSysex == 1) advancedSettings.thresholdM = valueSysex;    // Paramétrage du seuil
      else if (controllerSysex == 3 && commandeSysex == 1) advancedSettings.sensitivityL = valueSysex;   // Paramétrage de la sensitivity
      else if (controllerSysex == 4 && commandeSysex == 1) advancedSettings.sensitivityM = valueSysex;   // Paramétrage de la sensitivity
      else if (controllerSysex == 5 && commandeSysex == 1) advancedSettings.debounceTimeL = valueSysex;   // Paramétrage de la periode des doubles rebons
      else if (controllerSysex == 6 && commandeSysex == 1) advancedSettings.debounceTimeM = valueSysex;   // Paramétrage de la periode des doubles rebons
      else if (controllerSysex == 7 && commandeSysex == 1) advancedSettings.roundOff = valueSysex;       // Paramétrage du roundOff
    }

    if (channelSysex == 16 && controllerSysex < 8 && commandeSysex == 1) {
      for (int i = 0; i <= 6; i++) {
        SendMidi(i, controllerSysex, valueSysex); // Appelle a la fonction SendMidi
      }
    }
  }
}



void SendMidi(int midi_channel, int controller, int value) {
  if (controller == 1) {
    padSettings[midi_channel].channel = value;
  }
  else if (controller == 2) padSettings[midi_channel].padNote.note1 = value;                                      // Paramétrage de la courbe de vélocité
  else if (controller == 3) padSettings[midi_channel].trig_mode = static_cast<trigType>(value);          // Paramétrage du mode des pads
  else if (controller == 4) padSettings[midi_channel].velocity_curve = static_cast<curveType>(value);    // Paramétrage de la courbe de vélocité
  else if (controller == 5) padSettings[midi_channel].aftertouch_curve = static_cast<curveType>(value);  // Paramétrage de la courbe d'AfterTouch
  else if (controller == 6) padSettings[midi_channel].piezo = value > 63;                                // Paramétrage du Piezo
  else if (controller == 7) padSettings[midi_channel].qtouch = value > 63;                               // Paramétrage des Qtouch
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
