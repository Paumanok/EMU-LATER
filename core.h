/*************
* core module header for EMU-LATER
*
*************/

#include "rom.h"
#include "cpu.h"
#include "common.h"

typedef struct NES{
    MOS6502* cpu;
    ROM* rom;
    //PPU* ppu;
    uint8_t  ctrl_bus;
    uint8_t  data_bus;
    uint16_t addr_bus;
}NES;

int init_nes(NES* nes, char* rom_name);



