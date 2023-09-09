# hexapad
MIDI USB hexagonal interface made of 7 pads with velocity, aftertouch, and and a distance sensor

## Dependencies

* MIDIUSB
* Adafruit_FreeTouch
* Adafruit_VL53L0X

#TODO

## MIDI MAP
* Canal 1 -> Pad 1
* Canal 2 -> Pad 2
* Canal 3 -> Pad 3
* Canal 4 -> Pad 4
* Canal 5 -> Pad 5
* Canal 6 -> Pad 6
* Canal 7 -> Pad 7



* Controleur 1 -> MIDI channel
* Controleur 2 -> MIDI note
* Controleur 3 -> trig mode (percu,key,button)
* Controleur 4 -> velocity curve
* Controleur 5 -> aftertouch curve
* Controleur 6 -> disable piezo
* Controleur 7 -> disable QTouch (MIDI note is QT1)

* Canal 15 -> réglages capteur distance

* Controleur 1 -> MIDI channel
* Controleur 2 -> MIDI note (mode single note or button or first scale note, modulate velocity)
* Controleur 3 ->  trig mode (range CTL, single note, button, note scale)
* Controleur 4 -> curve
* Controleur 6 -> disable sensor
* Controleur 8 -> low threshold
* Controleur 9 -> high threshold
* Controleur 10 -> MIDI controller LSB
* Controleur 11 -> MIDI controller MSB
* Controleur 12 -> scale LSB
* Controleur 13 -> scale MSB
* Controleur 14 -> scale octaves

* Canal 16 -> réglages globaux

* Controleur 1 -> MIDI channel (all)
* Controleur 2 -> enable global channel
* Controleur 3 -> trig mode
* Controleur 4 -> velocity curve
* Controleur 5 -> aftertouch curve
* Controleur 6 -> disable piezo
* Controleur 7 -> disable QTouch (MIDI note is QT1)
