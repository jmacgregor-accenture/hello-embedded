# Hello World: The Half-Second Blink

This repo is the result of roughly following these [instructions](https://github.com/rubberduck203/embedded-101/blob/master/01-hello-world.md).

Pay attention to the hardware and software requirements listed in the [README](https://github.com/rubberduck203/embedded-101) for the repo above.

## To Compile

```sh
avr-gcc -c -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.c -o bin/hello-world.o

avr-gcc -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL bin/hello-world.o -o bin/hello-world.elf

avr-objcopy -j .text -j .data -O ihex bin/hello-world.elf bin/hello-world.hex
```

## To Flash to Board

```sh
avrdude -v -patmega328p -carduino -b115200 -D -Uflash:w:bin/hello-world.hex:i
```