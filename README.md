# SMART-Response-XE-Low_level

## Foreword

This is the low level software necessary to operate the SMART Response XE with the Arduino IDE. I have made this repository because when I first try to use the SMART Response XE with the Arduino IDE I spent many time collecting informations here and there.

This repository contains the Optiboot bootloader and the files necessary for the IDE to program the SMART response XE.
There is also [bitbank2's library](https://github.com/bitbank2/SmartResponseXE) with which you can print text using different fonts, read the keyboard and do minimal graphics. The limitations of the graphics are caused by to the limitations of the graphic controler used in the display.

The Optiboot was posted by serisman on the [arduboy forum](https://community.arduboy.com/t/smart-response-xe-re-purposed-into-arduboy/6094/176)

For those who need OTA updates there is a bootloader from [bitbank2](https://github.com/bitbank2/SMART_bootloader)

## How to use

The content of this repository shall be extracted in the hardware subdirectory located in your sketchbook directory.
If the hardware subdirectory does not exist you shall create it prior to extract the files

After installation, if you launch Arduino IDE you should have a new platform named SMART Response Terminal in the board manager and a board named SMART Response XE Optiboot.
If you select this board in the board manager, the hello_world example will be displayed in File/Examples menu and the SmartResponseXE library in the Library manager.

The sketchbook directory tree shall look somethings like this

```text
sketchbook\
    |
    |--A_Project\
    |--B_Project\
    |
    |--hardware\
    |     |
    |     |-- SMART-Response-XE-Low_level\
    |                   |--avr\
    |                   |   |--bootloaders\
    |                   |   |     | optiboot_atmega128rfa1.hex
    |                   |   |
    |                   |   |--libraries\
    |                   |   |     |-- SmartResponseXE\
    |                   |   |             |--examples\
    |                   |   |             |     |-- hello_world\
    |                   |   |             |             | hello_world.ino
    |                   |   |             |
    |                   |   |             | LICENSE.md
    |                   |   |             | README.md
    |                   |   |             | SmartResponseXE.cpp
    |                   |   |             | SmartResponseXE.h
    |                   |   |
    |                   |   |--variants\
    |                   |   |    |--smartxe\
    |                   |   |         | pins_arduino.h
    |                   |   |
    |                   |   | board.txt
    |                   |   | platform.txt
    |                   |
    |                   | LICENSE.md
    |                   | README.md
    |
    |--libraries\
    |     |
    |     |-- A_library\
    |     |
    |     |-- Z_library\
    |
    |--Z_Project\
``` 

## Avant-propos

Vous trouverez ici le logiciel bas niveau nécessaire à la mise en oeuvre du SMART Response XE avec l\'IDE Arduino. J\'ai créé ce dépot car lorsque j\'ai voulu commencer à utiliser le SMART Response XE avec l\'IDE Arduino, j\'ai perdu beaucoup de temps à récupérer des informations sur différents sites.

Ce dépot contient le bootloader Optiboot et les fichiers nécessaires à la programmation du SMART Response XE dans l'IDE Arduino.
Il y a aussi la [librairie écrite par bitbank2](https://github.com/bitbank2/SmartResponseXE) qui permet d\'afficher du texte avec plusieurs polices, lire le clavier et afficher un graphisme minimaliste. Les limitations du graphisme sont la conséquence des limitations du contrôleur graphique utilisé par l'écran.

Le bootloader Optiboot a été posté par serisman sur le [forum arduboy](https://community.arduboy.com/t/smart-response-xe-re-purposed-into-arduboy/6094/176)

Pour ceux qui voudrait faire des mises à jour sans fil, il y a un bootloader écrit par [bitbank2](https://github.com/bitbank2/SMART_bootloader)

## Usage

Le contenu de ce dépot doit être extrait dans le sous-répertoire hardware situé dans votre répertoire sketchbook
Si le sous-répertoire hardware n\'existe pas, il faut le créer avant d\'extraire les fichiers

Après installation, vous devriez trouver dans le gestionnaire de carte une nouvelle plateforme nommée SMART Response Terminal et une nouvelle carte nommée SMART Response XE Optiboot
Si vous sélectionnez cette carte dans Outils/Type de cartes le projet hello_world apparaitra dans le menu Fichier/Exemples et la librairie SmartResponseXE sera visible dans Croquis/Inclure une bibliothèque.

L\'arborescence du répertoire sketchbook doit ressembler à celle présentée au-dessus.
