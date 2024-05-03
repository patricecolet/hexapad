# HEXAPAD
MIDI USB hexagonal interface made of 7 pads with velocity, aftertouch, and and a distance sensor



### [- Introduction](#Introduction)
### [- Description](#Description)
### [- Schematique](#Schematique)
### [- PCB](#PCB)
### [- Firmware](#Firmware)
### [- Dependences](#Dependences)
### [- MIDI implementation](#implementation)
  
### Introduction
<a id="Introduction"></a>

Cet appareil est un hexapad doté de différents capteurs capacitifs qui, lorsqu'ils sont en contract avec des doigts, envoient des signaux ou commandes MIDI à l'aide d'un câble USB vers un ordinateur.
Le MIDI est est un protocole de communication et un format de fichier dédiés à la musique utilisés pour la communication entre instruments électroniques, contrôleurs, séquenceurs, et logiciels de musique.
 
Le microcontrôleur utilisé est un Seeed Studio XIAO SAMD21 qui est programmé avec l'IDE Arduino. Il dispose de 7 entrées capacitives Qtouch qui servent à déclencher des notes de musique, d'un capteur de vibrations piézoélectriques et d'un capteur de proximité infrarouge pour modifier les sons. 
 

![Seeeduino broche](https://github.com/patricecolet/hexapad/blob/stage/images/broche_xiao.png?raw=true)

### Description
<a id="Description"></a>

Nous disposons de 7 broches pour nos capteurs capacitifs qui doivent etre répartie avec la meme surface.

L'idée serait donc une forme hexagonale qui serait divisée en 6 parties, avec un hexagone plus petit au centre.

![hexagone prototype](https://github.com/patricecolet/hexapad/blob/stage/images/hexagone1.png?raw=true)


L'hexagone devra faire 15,5 cm de haut et chaque trapèse doit etre espacé de 2 mm pour éviter les perturbations. C'est a l'aide du logiciel Geogebra que nous avons réussi a trouver les dimensions idéale.

![hexagone final](https://github.com/patricecolet/hexapad/blob/stage-refactoring/images/hexagone2.png?raw=true)


### SCHEMATIQUE 
<a id="SCHEMATIQUE"></a>

Voici l'élaborer de la carte électronique qui accueillera nos capteurs capacitifs, le microcontrôleur, le capteur de vibration et le capteur de distance.

Conformément aux recommandations de la documentation technique, nous avons mis en place des résistances de Pull Up  sur chaque broche du capteur de distance (VL53l0X) et nous avons mis des condensateurs de découplage sur AVDD et AVDDVCSEL.

![data sheet VL53L0X](https://github.com/patricecolet/hexapad/blob/stage/images/broche_vl53l0x.png?raw=true)

Nous avons également installé des boutons poussoir pour réinitialiser le microcontrôleur et le VL53L0X. Enfin pour le câblage du piezo, nous avons mis une résistance et une diode en parallèle. 

![Schematique final](https://github.com/patricecolet/hexapad/blob/stage/images/schematique.png?raw=true)

### PCB 
<a id="PCB"></a>

Pour la partie PCB, les composants devaient etre tous groupés pour que la carte ne soit pas trop grande.

Des tests ont étés réalisé aux préalables pour savoir si la longueur des fils/pistes pouvait avoir une influence sur la sensibilité des capteurs. En réalité, plus les pistes sont étendues, plus la variation du signal est faible. C'est pour cette raison que nous devons nous assurer que les pistes soient les moins longues possibles.

Pour éviter toute perturbation, l'hexagone sera recouvert d'un plan de masse qui nous protègera des parasites.

![Exemple plan de masse](https://github.com/patricecolet/hexapad/blob/stage/images/plan_de_masse_ex.png?raw=true)

De ce fait il y a moins de charges capacitives entre chaque capteur car elles sont entraînées vers le même potentiel. Il y aura un champ électrique plus fort entre le capteur et l'utilisateur, ce qui augmentera la sensibilité des capteurs.

![Shield](https://github.com/patricecolet/hexapad/blob/stage/images/driven_shield_plus.png?raw=true)


### Firmware
<a id="Firmware"></a>

Le programme est composé de 4 grandes parties :

#### [-Capteur de distance](#distance)
#### [-Capteur Piezoelectrique](#Piezoelectrique)
#### [-Capteur capacitif Qtouch](#Qtouch)
#### [-Message Midi](#Midi)

##### Capteur de distance 
<a id="distance"></a>

##### Capteur Piezoelectrique
<a id="Piezoelectrique"></a>

Le capteur piézoélectrique est un capteur de vibration, il va donc nous permettre de détecter l'intensité de nos appuis sur l'hexapad. Nous allons utiliser la fonction TimerCallBack pour faire appel à notre capteur piézo lorsqu'il détectera un changement d'état de sa part. Nous avons choisi de structurer le code du piézo en utilisant un Switch case pour évaluer l'état de notre piezo.

![Machine_Piezo](https://github.com/patricecolet/hexapad/blob/sysex/images/machine_piezo.png?raw=true)

Les doubles rebonds persistaient toujours donc nous avons implanter un seuil glissant qui varirait en fonction de la valeur peak du piézo.

![Machine_Piezo2](https://github.com/patricecolet/hexapad/blob/stage/images/machine_piezo2.png?raw=true)

![Allure_Piezo](https://github.com/patricecolet/hexapad/blob/stage/images/allure_piezo.png?raw=true)


##### Capteur capacitif Qtouch
<a id="Qtouch"></a>

Les hexapad se déclanche lorsqu'un doigt s'approche d'un capteur capacitif, il va perturbe le champ électrique du pad, ce qui est détecté par l'entrée QTouch. Cela permet au microcontroller de déterminer la surface du toucher et va intéragir avec du son plus ou moins déformer. On va nommé cette deformation l'AfterTouch.

##### Message Midi
<a id="Midi"></a>

## Dependences
<a id="Dependences"></a>

* MIDIUSB
* Adafruit_FreeTouch
* Adafruit_VL53L0X
* MovingAverage


## MIDI implémentation
<a id="implementation"></a>

* Canal 1 -> Pad 1
* Canal 2 -> Pad 2
* Canal 3 -> Pad 3
* Canal 4 -> Pad 4
* Canal 5 -> Pad 5
* Canal 6 -> Pad 6
* Canal 7 -> Pad 7
* Canal 8 -> Lidar
* Canal 9 -> Advanced Settings

|STRUCTURE MESSAGE SYSEX|DECHIFFRAGE| Description|
|:---:|:---:|:---:|
|F0|240|Début du message Sysex|
|48|H|Identifiant ASCII|
|45|E|Identifiant ASCII|
|58|X|Identifiant ASCII|
|41|A|Identifiant ASCII|
|50|P|Identifiant ASCII|
|41|A|Identifiant ASCII|
|44|D|Identifiant ASCII|
|30|0|Fin Identifiant ASCII|
|01 ou 02|1(SET) ou 2(GET)|Commande|
|01|1|Version|
|00|0|Révision|
|XX|XX|Channel|
|XX|XX|Numéro de paramètre|
|XX|XX|Value|
|F7|247|Fin du message Sysex|

##### Channel de 1 à 7
|NUMERO DE PARAMETRE|PADSETTINGS|
|:---:|:---:|
|1|Channel|
|2|Note 1|
|3|Seuil 1|
|4|Note 2|
|5|Seuil 2|
|6|Note 3|
|7|Seuil 3|
|8|Trig Mode(0 = Percussion,1 = Keyboard, 2 = Button)|
|9|Vélocity Curve (0 = Linear, 1 = Parabola ,2 = Hyperbola, 3 = Sigmoid)|
|10|AfterTouch Curve (0 = Linear, 1 = Parabola ,2 = Hyperbola, 3 = Sigmoid)|
|11|Piezo (1 = Activate, 0 = Disable)|
|12|QTouch (1 = Activate, 0 = Disable)|

#### EXEMPLE MODIFICATION DU TRIG MODE SUR LE PAD 6 DE PADSETTINGS
|||||||||||||CHANNEL|PARAMETRE|VALUE||
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---::|---:|:---:|:---:|:---:|:---:|:---:|:---:|
|F0|48|45|58|41|50|41|44|30|01|01|00|06|08|02|F7|
|240|H|E|X|A|P|A|D|0|1|1|0|6|8|2|247|

##### Channel 8
|NUMERO DE PARAMETRE|LIDAR|
|:---:|:---:|
|1|Channel|
|2|Note|
|3|Curve (0 = Linear, 1 = Parabola ,2 = Hyperbola, 3 = Sigmoid)|
|4|Low Threshold LSB|
|5|Low Threshold MSB|
|6|High Threshold LSB|
|7|High Threshold MSB|
|8|Controller LSB|
|9|Controller MSB|
|10|Scale|
|11|Scale Low Range|
|12|Scale High Range|
|13|Lidar (1 = Activate, 0 = Disable)|

#### EXEMPLE MODIFICATION DU LOW THRESHOLD MSB SUR LE LIDAR
|||||||||||||CHANNEL|PARAMETRE|VALUE||
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---::|---:|:---:|:---:|:---:|:---:|:---:|:---:|
|F0|48|45|58|41|50|41|44|30|01|01|00|08|05|7F|F7|
|240|H|E|X|A|P|A|D|0|1|1|0|8|5|127|247|

##### Channel 9
|NUMERO DE PARAMETRE|ADVANCED SETTINGS|
|:---:|:---:|
|1|Piezo Threshold LSB|
|2|Piezo Threshold MSB|
|3|Piezo Sensitivity LSB|
|4|Piezo Sensitivity MSB|
|5|Debounce Time LSB|
|6|Debounce Time MSB|
|7|QTouch RoundOff|

#### EXEMPLE MODIFICATION DU ROUNDOFF DANS ADVANCED SETTINGS
|||||||||||||CHANNEL|PARAMETRE|VALUE||
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---::|---:|:---:|:---:|:---:|:---:|:---:|:---:|
|F0|48|45|58|41|50|41|44|30|01|01|00|09|07|0F|F7|
|240|H|E|X|A|P|A|D|0|1|1|0|9|7|15|247|

#TODO
