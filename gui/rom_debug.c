//automated test for rom loader

#include <stdio.h>
#include <stdlib.h>
#include "../src/rom.h"
#include "rom_debug.h"


ROM* build_rom(char* fileName) {
    ROM *rom;
    rom = malloc(sizeof(ROM));
    if (init_rom(fileName, rom) < 0) {
        printf("rom init failed, returning null");
        return NULL;
    }
    return rom;
}

uint8_t read_rom(ROM *rom, int address) {
    return rom->PRG_ROM[address];
}
