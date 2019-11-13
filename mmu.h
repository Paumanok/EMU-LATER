#ifndef MMU_H__
#define MMU_H__
#include "common.h"
#include "core.h"

void mmu_ctrl(NES* nes);

int write_internal_ram(NES* nes);
int internal_memory(NES* nes);
int mapper_0(NES* nes);

// Relative memory offsets for MMU
// This is needed as each section of memory is 
// handled as a distinct buffer in the EMU-Later 
// internal structures, therefore an absolute
// physical address must be adjusted to align with
// the beginning of the C buffer, rather than NES
// physical memory. 
// This may benefit various mapper implementations 
// as each can have offsets designated for various
// memory pages -- we will find out how true this 
// actually is...
#define PPU_OFFSET       0x2000
#define APU_OFFSET       0x4000
#define PRG_ROM_OFFSET   0x4020

//mapper0 offsets
#define M0_PRAM_OFFSET    0x6000
#define M0_ROM_OFFSET     0x8000


#endif //MMU_H__
