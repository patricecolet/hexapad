# hexapad
MIDI USB hexagonal interface made of 7 pads with velocity, aftertouch, and and a distance sensor

## Dependencies

* MIDIUSB
* Adafruit_FreeTouch
* Adafruit_VL53L0X
* MovingAverage

#TODO

## MIDI MAP

* Canal 1 -> Pad 1
* Canal 2 -> Pad 2
* Canal 3 -> Pad 3
* Canal 4 -> Pad 4
* Canal 5 -> Pad 5
* Canal 6 -> Pad 6
* Canal 7 -> Pad 7

|MIDI controller| Description|
|---|---|
| Controleur 1 | MIDI channel |
| Controleur 2 | MIDI note |
| Controleur 3 | Trig mode (percu,key,button) |
| Controleur 4 | Velocity curve |
| Controleur 5 | Aftertouch curve |
| Controleur 6 | Disable piezo |
| Controleur 7 | Disable QTouch (MIDI note is QT1) |

* Canal 15 -> réglages capteur distance

|MIDI controller| Description|
|---|---|
| Controleur 1 | MIDI channel
| Controleur 2 | MIDI note (mode single note or button or first scale note, modulate velocity)
| Controleur 3 | Trig mode (range CTL, single note, button, note scale)
| Controleur 4 | Curve
| Controleur 5 | Disable sensor
| Controleur 6 | LOW threshold(mm) LSB
| Controleur 7 | LOW threshold(mm) MSB
| Controleur 8 | HIGH threshold(mm) LSB
| Controleur 9 | HIGH threshold(mm) MSB
| Controleur 10 | MIDI controller LSB
| Controleur 11 | MIDI controller MSB
| Controleur 12 | Scale LSB
| Controleur 13 | Scale MSB
| Controleur 14 | Scale octaves

* Canal 16 -> réglages globaux

|MIDI controller| Description|
|---|---|
| Controleur 1 | MIDI channel (all)
| Controleur 2 | Enable global
| Controleur 3 | Trig mode
| Controleur 4 | Velocity curve
| Controleur 5 | Aftertouch curve
| Controleur 6 | Disable piezo
| Controleur 7 | Disable QTouch (MIDI note is QT1)
