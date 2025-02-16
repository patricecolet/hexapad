#include "sysex.hpp"

midiMessage _MIDI;

byte padSettingsBytes[sizeof(PadSettings) * 7 + 2];
byte advancedSettingsBytes[sizeof(AdvancedSettings) + 2];

// class sysex constructor
sysex::sysex(){
};

// callback function trigged when a sysex packet is received
void sysex::parse(byte * data, unsigned length){
  for (int i = 0; i < length; i++) Serial.println(data[i]);

  if ((data[0] == 240) && (data[length - 1] == 247) && length > 2) { // check sysex packet
    if(checkID(data) == 1) {                                         // check sysex ID (should be "HEXAPAD1")
      if (data[9] == (byte)sysexCommand::set) set(data);             // command 'set' = 0x1
      if (data[9] == (byte)sysexCommand::get) dump(data);             // command 'get' = 0x2
      if (data[9] == (byte)sysexCommand::calibrate) calibrate();     // command 'calibrate' = 0x3
    }
    else Serial.println("wrong sysex ID");
  }
}
bool sysex::checkID (byte * data) {
  bool status = 1;
  for (int i = 0; i < 8; i++) if(data[i+1] != SysexID[i]) status ==  0;
  return status;
}

void sysex::calibrate() {
  
}
// sysex command to set parameter
void sysex::set(byte * data) {
  if((data[10] == 1) && (data[11] == 0)) {                            // version 1 & revision 0 of set command
    switch (data[12]) {                                               // set target
      case (byte)hexapad::pad1 : pad((byte)hexapad::pad1,data);break;
      case (byte)hexapad::pad2 : pad((byte)hexapad::pad2,data);break;
      case (byte)hexapad::pad3 : pad((byte)hexapad::pad3,data);break;
      case (byte)hexapad::pad4 : pad((byte)hexapad::pad4,data);break;
      case (byte)hexapad::pad5 : pad((byte)hexapad::pad5,data);break;
      case (byte)hexapad::pad6 : pad((byte)hexapad::pad6,data);break;
      case (byte)hexapad::pad7 : pad((byte)hexapad::pad7,data);break;
      case (byte)hexapad::lidar : lidar(data);break;
      case (byte)hexapad::advanced : advanced(data);break;
      default: break;
    }
    Serial.print("target: ");
    Serial.println(data[12]);
  }
};

// update pad parameter state
void sysex::pad(byte pad, byte * data) {
  byte param = data[13];
  byte value = data[14];
  byte value2 = data[15];
  switch (param) {
    case (byte)padParam::channel : padSettings[pad].channel = value;break;
    case (byte)padParam::note : padSettings[pad].note = value;break;
    case (byte)padParam::trig_mode : padSettings[pad].trig_mode = (trigType)value;break;
    case (byte)padParam::velocity_curve : padSettings[pad].velocity_curve = (curveType)value;break;
    case (byte)padParam::aftertouch_curve : padSettings[pad].aftertouch_curve = (curveType)value;break;
    case (byte)padParam::piezo : padSettings[pad].piezo = value;break;
    case (byte)padParam::qtouch : padSettings[pad].qtouch = value;break;
    case (byte)padParam::qtouch_onset : padSettings[pad].qtouch_onset = (value << 7) | value2;break;
    case (byte)padParam::qtouch_offset : padSettings[pad].qtouch_offset = (value << 7) | value2;break;
    case (byte)padParam::qtouch_ceiling : padSettings[pad].qtouch_ceiling = (value << 7) | value2;break;
    default: break;
  }
}

// update lidar parameter state
void sysex::lidar(byte * data) {
  byte param = data[13];
  byte value = data[14];
  switch (param) {
    case (byte)lidarParam::channel : Lidar.channel = value;break;
    case (byte)lidarParam::note : Lidar.note = value;break;
    case (byte)lidarParam::curve : Lidar.curve = (curveType)value;break;
    case (byte)lidarParam::lowThresholdLSB : Lidar.lowThresholdLSB = value;break;
    case (byte)lidarParam::lowThresholdMSB : Lidar.lowThresholdMSB = value;break;
    case (byte)lidarParam::highThresholdLSB : Lidar.highThresholdLSB = value;break;
    case (byte)lidarParam::highThresholdMSB : Lidar.highThresholdMSB = value;break;
    case (byte)lidarParam::controllerLSB : Lidar.controllerLSB = value;break;
    case (byte)lidarParam::controllerMSB : Lidar.controllerMSB = value;break;
    case (byte)lidarParam::enable : Lidar.enable = value;break;
    default: break;
  } 
}
// update advanced parameter state
void sysex::advanced(byte * data) {
  byte param = data[13];
  byte value = data[14];
  switch (param) {
    case (byte)advancedParam::piezoThresholdLSB : advancedSettings.piezoThresholdLSB = value;break;
    case (byte)advancedParam::piezoThresholdMSB : advancedSettings.piezoThresholdMSB = value;break;
    case (byte)advancedParam::piezoSensitivityLSB : advancedSettings.piezoSensitivityLSB = value;break;
    case (byte)advancedParam::piezoSensitivityMSB : advancedSettings.piezoSensitivityMSB = value;break;
    case (byte)advancedParam::piezoDebounceTimeLSB : advancedSettings.piezoDebounceTimeLSB = value;break;
    case (byte)advancedParam::piezoDebounceTimeMSB : advancedSettings.piezoDebounceTimeMSB = value;break;
    case (byte)advancedParam::qtouchRoundOff : advancedSettings.qtouchRoundOff = value;break;
    default: break;
  }   
}

// sysex command to set parameter
void sysex::dump(byte * data) {

  if((data[10] == 1) && (data[11] == 0)) {  // version 1 & revision 0 of get command
    for (int i=0; i<7; i++) {
      int length = 25;
      byte message [length] = {};
      for (int i=0; i<9; i++) message[i]=data[i];
      message[9]=(byte)sysexParam::pad;         
      message[10]=i;
      message[11]=padSettings[i].channel;
      message[12]=padSettings[i].note;
      message[13]=(byte)padSettings[i].trig_mode;
      message[14]=(byte)padSettings[i].velocity_curve;
      message[15]=(byte)padSettings[i].aftertouch_curve;
      message[16]=padSettings[i].piezo;
      message[17]=padSettings[i].qtouch;
      message[18]=(padSettings[i].qtouch_onset >> 7) & 0x7F;
      message[19]=padSettings[i].qtouch_onset & 0x7F;
      message[20]=(padSettings[i].qtouch_offset >> 7) & 0x7F;
      message[21]=padSettings[i].qtouch_offset & 0x7F;
      message[22]=(padSettings[i].qtouch_ceiling >> 7) & 0x7F;
      message[23]=padSettings[i].qtouch_ceiling & 0x7F;
      message[24]=0xF7;
      _MIDI.sysexSend(message, length);
    }           
  }
}

