#!/bin/bash
gcc -I kiss_sdl2/ -I kiss_sdl2/include/SDL2/ -Wall -c rom.c rom_debug.c sdl_rom_debug.c kiss_sdl2/*.c

gcc *.o -I kiss_sdl2/ -I kiss_sdl2/include/SDL2/ -L kiss_sdl2/ -L kiss_sdl2/lib/ -l SDL2 -l SDL2_ttf -l SDL2_image -o sdl_test
