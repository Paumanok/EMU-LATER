#ifndef ROM_DEBUG_H__
#define ROM_DEBUG_H__

/****************
*rom parser header file
* author: ryan tompkins
* rom_debug.h
*****************/

#include <stdint.h>
#include "common.h"
#include "rom.h"

ROM* build_rom(char* fileName);

uint8_t read_rom(ROM *rom, int address);

#endif //ROM_DEBUG_H__
