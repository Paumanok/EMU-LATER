#ifndef ROM_H__
#define ROM_H__

/****************
*rom parser header file
* author: matthew smith
* rom.h
*****************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "common.h"

//sizes in bytes
#define PRG_ROM_MULT 163854
#define CHR_ROM_MULT 8192
#define TRAINER_SIZE 512
#define INST_ROM_SIZE 8192
#define PROM_SIZE 8192


int init_rom(const char* rom, ROM *cart);

int cart_init(ROM *rom, Header *header);

#endif //ROM_H__
