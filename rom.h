#ifndef ROM_H__
#define ROM_H__

/****************
*rom parser header file
* author: matthew smith
* rom.h
*****************/

#include <stdint.h>

//sizes in bytes
#define PRG_ROM_MULT 163854
#define CHR_ROM_MULT 8192
#define TRAINER_SIZE 512
#define INST_ROM_SIZE 8192
#define PROM_SIZE 8192

typedef struct{
    uint8_t NES[4];
    uint8_t PRG_ROM_SIZE;
    uint8_t CHR_ROM_SIZE;
    uint8_t Flag_Six;
    uint8_t Flag_Seven;
    uint8_t PRG_RAM_SIZE;
    //uint8_t Flag_Nine; //few honor this flag
    uint8_t Reserved[7];  //should be all 0s
}Header;

typedef struct{
    //Header header;
    uint8_t *trainer;
    uint8_t *PRG_ROM;
    uint8_t *CHR_ROM;
    uint8_t *INST_ROM;
    uint8_t *PROM;
    uint8_t *PRG_RAM;
}ROM;

int getRom(const char* rom, ROM *cart);

int cartInit(ROM *rom, Header *header);

#endif //ROM_H__
