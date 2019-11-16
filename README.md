# SMART-Response-XE-Low_level

This is the low level software necessary to operate the SMART Response XE with the Arduino IDE. I have made this repository because when I first try to use the SMART Response XE with the Arduino IDE I spent many time collecting informations here and there.

This repository contains the Optiboot bootloader and the files necessary for the IDE to program the SMART response XE.

The Optiboot was posted by serisman on the [arduboy forum](https://community.arduboy.com/t/smart-response-xe-re-purposed-into-arduboy/6094/176)

The content of this repository shall be extracted in the hardware subdirectory located in your sketchbook directory.
If the hardware subdirectory does not exist you shall create it prior to extract the files

The sketchbook directory tree shall look somethings like this

sketchbook

    |
    | --A_Project
    | --B_Project
    | --libraries
    |     |
    |     | -- A_library
    |     |
    |     | -- Z_library
    |
    | --hardware
    |     |
    |     | -- SMART-Response-XE-Low_level
    |                   | --avr
    |                       | --bootloaders
    |                             | optiboot_atmega128rfa1.hex
    |                       | --variants
    |                       |    | --smartxe
    |                       |         | pins_arduino.h
    |                       | board.txt
    |                       | platform.txt
    |
    | --Z_Project
    
