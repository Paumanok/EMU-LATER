#ifndef CORE_H__
#define CORE_H__
/*************
* core module header for EMU-LATER
*
*************/

//#include "rom.h"
//#include "cpu.h"
#include "common.h"
#include "cpu.h"
#include "rom.h"
#include "mmu.h"



int init_nes(NES* nes, char* rom_name);


#endif
