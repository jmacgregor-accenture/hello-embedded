#!/bin/bash

announce(){
    echo $@
    $@
}

printf "\nFinding Your C File...\n\n"

c_file=$(ls *.c)
name_only=${c_file%.*}
machine_code="bin/$name_only.o"
executable="bin/$name_only.elf"
uploadable="bin/$name_only.hex"

printf "\nDoing me some compiles...\n\n"

announce avr-gcc -c -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL $c_file -o $machine_code
announce avr-gcc -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL $machine_code -o $executable
announce avr-objcopy -j .text -j .data -O ihex $executable $uploadable

printf "\nLet's zippity-zap some code to the board...\n\n"

announce avrdude -v -patmega328p -carduino -b115200 -D -Uflash:w:$uploadable:i