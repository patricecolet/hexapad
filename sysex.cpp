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
    if(checkID(data) == 1) {                                         // check sysex ID (should be "HEXAPAD0")
      if (data[9] == (byte)sysexCommand::set) set(data);             // command 'set'
    }
    else Serial.println("wrong sysex ID");
  }
}

bool sysex::checkID (byte * data) {
  bool status = 1;
  for (int i = 0; i < 8; i++) if(data[i+1] != SysexID[i]) status ==  0;
  return status;
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
  switch (param) {
    case (byte)padParam::channel : padSettings[pad].channel = value;break;
    case (byte)padParam::note1 : padSettings[pad].padNote1.note = value;break;
    case (byte)padParam::qtouchThreshold1 : padSettings[pad].padNote1.qtouchThreshold = value;break;
    case (byte)padParam::note2 : padSettings[pad].padNote2.note = value;break;
    case (byte)padParam::qtouchThreshold2 : padSettings[pad].padNote2.qtouchThreshold = value;break;
    case (byte)padParam::note3 : padSettings[pad].padNote3.note = value;break;
    case (byte)padParam::qtouchThreshold3 : padSettings[pad].padNote3.qtouchThreshold = value;break;
    case (byte)padParam::trig_mode : padSettings[pad].trig_mode = (trigType)value;break;
    case (byte)padParam::velocity_curve : padSettings[pad].velocity_curve = (curveType)value;break;
    case (byte)padParam::aftertouch_curve : padSettings[pad].aftertouch_curve = (curveType)value;break;
    case (byte)padParam::piezo : padSettings[pad].piezo = value;break;
    case (byte)padParam::qtouch : padSettings[pad].qtouch = value;break;
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
    case (byte)advancedParam::piezoRoundOff : advancedSettings.piezoRoundOff = value;break;
    default: break;
  }   
}

// sysex command to set parameter
void sysex::dump() {

}

