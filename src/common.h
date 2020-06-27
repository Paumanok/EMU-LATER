#ifndef COMMON_H__
#define COMMON_H__
/* common defines
 *
 *
*/

#include <stdint.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WRITE 1
#define READ 0

#define DEBUG 1
/*
 * iNES file header structure
 * used for parsing iNES file with constant format
 */
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

/*
 * ROM struct
 * contains data that composes NES rom
 * format dictated by header
 */
typedef struct{
    Header* header;
    uint8_t *trainer;
    uint8_t *PRG_ROM;
    uint8_t *CHR_ROM;
    uint8_t *INST_ROM;
    uint8_t *PROM;
    uint8_t *PRG_RAM;
    uint8_t mapper;
}ROM;

/*
 * CPU struct
 * holds CPU registers for context
 */
typedef struct{
    uint16_t pc;  //program counter
    int8_t  A;   //Accumulator register
    uint8_t  Y;   //Index register Y
    uint8_t  X;   //Index register X
    uint8_t  S;   //stack pointer
    uint8_t  P;   //status register
}MOS6502;

/*
 * NES Struct
 * ties together CPU, ROM, MMU, PPU and data busses
 */
typedef struct NES{
    //hardware modules
    MOS6502* cpu;
    ROM* rom;
    //PPU* ppu;
    //internal memory
    uint8_t* int_ram;
    uint8_t* ppu_regs;
    //data bus lines
    uint8_t  ctrl_bus;
    uint8_t  data_bus;
    uint16_t addr_bus;
}NES;

enum ret_flags {
    INIT_FAIL = -10,
    BAD_ADDRESS = -9,
    SUCCESS = 1
};

#endif //COMMON_H__
