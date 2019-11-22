#ifndef PPU_H__
#define PPU_H__

#include "common.h"
#include "mmu.h"

#define PPUCTRL 0x2000
#define PPUMASK 0x2001
#define PPUSTAT 0x2002
#define OAMADDR 0x2003
#define OAMADAT 0x2004
#define PPUSCRL 0x2005
#define PPUADDR 0x2006
#define PPUDATA 0x2007

#define OAMDMA  0x4014

void update(NES* nes);

#endif
