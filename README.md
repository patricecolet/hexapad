# hexapad
MIDI USB hexagonal interface made of 7 pads with velocity, aftertouch, and and a distance sensor



#### - Introduction
#### - Hexapad
#### - Schematique
#### - PCB
#### - Firmware
#### - Dependences
#### - MIDI implementation
  
### Introduction

Nous travaillons sur un projet destiné aux enfants et aux malvoyants. Cet appareil est un pad doté de différents capteurs capacitifs sous des surfaces tactiles texturées qui, lorsqu'ils sont déclenchés, envoient du son via une communication midi. 
 
Il peut être utilisé comme instrument de musique ou outil pédagogique pour les enfants. 
 
Le microcontrôleur utilisé est un Seeed Studio XIAO SAMD21 qui est programmé avec l'IDE Arduino. Il dispose de 7 entrées capacitives Qtouch qui servent à déclencher des notes de musique, d'un capteur de vibrations piézoélectriques et d'un capteur de proximité infrarouge pour modifier les sons. 

![Seeeduino broche](https://github.com/patricecolet/hexapad/issues/1#issue-2211002847)

### Hexapad

Nous disposons de 7 broches pour nos capteurs capacitifs, il nous faut maintenant trouver une forme compacte pouvant être divisée en 7 parties toutes de même taille. 

Nous nous sommes orientés vers l'idée d'une forme hexagonale qui serait divisée en 6 parties avec un hexagone plus petit au centre. 

![hexagone prototype](https://github.com/patricecolet/hexapad/issues/1#issuecomment-2022974226)


Il faut maintenant commencer à trouver les bonnes dimensions. Nous voulions que notre hexagone fasse 15,5 cm de haut et que chaque pièce soit espacée de 2 mm pour éviter les perturbations. Nous avons résolu ce problème avec le logiciel geogebra et trouvé les dimensions parfaites.

![hexagone final](https://github.com/patricecolet/hexapad/issues/1#issuecomment-2022974555)


### SCHEMATIQUE 

A présent nous devons concevoir une carte électronique qui accueillerais nos capteurs capacitifs, le microcontrôleur, le capteur de vibration et le capteur de distance.  

Comme conseillé sur la doc technique, nous avons mis des résistances de Pull Up sur chaque broche du capteur de distance (VL53l0X) et nous avons mis des condensateurs de découplage sur AVDD et AVDDVCSEL.

![data sheet VL53L0X](https://github.com/patricecolet/hexapad/issues/1#issuecomment-2022974999)

Nous avons aussi mis des boutons poussoir permettant le reset du microcontrôleur et du VL53L0X. Enfin pour le câblage du piezo, nous avons mis une résistance et une diode en parallèle. 

![Schematique final](https://github.com/patricecolet/hexapad/issues/1#issuecomment-2022984570)

### PCB 

Pour la partie PCB, nous voulions que tous les composants soient tous grouper pour que la carte ne soit pas trop grande. 

Nous avons fait des tests au préalable pour savoir si la longueur des fils/pistes pouvait avoir une influence sur la sensibilité des capteurs. En effet, plus les pistes sont grandes, plus la variation du signal est petite. C’est pourquoi nous devons faire en sorte que les pistes soient les moins longues possibles. 

Pour éviter toute perturbation, nous avons placer tout autour de l’hexagone un plan de masse qui nous protègera des parasites.  

![Exemple plan de masse](https://github.com/patricecolet/hexapad/issues/1#issuecomment-2022975566)

De ce fait il y a moins de charges capacitives entre chaque capteur car elles sont entraînées vers le même potentiel. Il y aura un champ électrique plus fort entre le capteur et l'utilisateur, ce qui augmente la sensibilité des capteurs. 

![Shield](https://github.com/patricecolet/hexapad/issues/1#issuecomment-2022976134)


## Dependences

* MIDIUSB
* Adafruit_FreeTouch
* Adafruit_VL53L0X
* MovingAverage


## MIDI implémentation

* Canal 1 -> Pad 1
* Canal 2 -> Pad 2
* Canal 3 -> Pad 3
* Canal 4 -> Pad 4
* Canal 5 -> Pad 5
* Canal 6 -> Pad 6
* Canal 7 -> Pad 7

|MIDI controller| Description|
|---|---|
| Controleur 1 | MIDI channel | (midi channel 1 value is 0, midi channel 2 value is 1 ...)
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


#TODO
