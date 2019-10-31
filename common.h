#ifndef COMMON_H__
#define COMMON_H__
/* common defines
 *
 *
*/

#define WRITE 0
#define READ 1

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
    uint8_t  A;   //Accumulator register
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
    MOS6502* cpu;
    ROM* rom;
    //PPU* ppu;
    uint8_t  ctrl_bus;
    uint8_t  data_bus;
    uint16_t addr_bus;
}NES;

enum ret_flags {
    INIT_FAIL = -10,
    SUCCESS = 1
};

#endif //COMMON_H__
