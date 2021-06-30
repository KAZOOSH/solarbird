# solaranimals
zwitschernde Tiere zur Woche des guten Lebens 2021

## How to flash SolarbirdTiny.ino with Arduino IDE

- Get an AVR ISP programmer or a spare Arduino and follow [these instructions](https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829)
- Under Tools, select board “ATtiny25/45/85”, processor “ATtiny85”, and clock “Internal 8 MHz”
- Again under Tools, click Burn Bootloader (won't actually flash the Arduino bootloader but just set the fuses)
- Optional: change the code to include the bird voice of your choice (see following section)
- Flash the Arduino program as usual by clicking the Upload button

## How to change the bird's voice

At the time of writing, we have an imitation of a blackbird, a chiffchaff, a titmouse and a wren. Check the folder [voices](SolarbirdTiny/voices/) for all available bird voices.

In [SolarbirdTiny.ino near line 32](SolarbirdTiny/SolarbirdTiny.ino#L32), find the lines which include the bird voice and create a _Bird_ instance from it:
```c++
#include "voices/blackbird.h"
Blackbird Bird;
```

Change the name of the included file on the first line to the one of your liking. The code follows the convention that the class name (first word on the second line) is the capitalized version of the filename, i.e., the file `chiffchaff.h` contains the class `Chiffchaff`. After changing both lines, you're ready to upload the new voice to the ATtiny.
