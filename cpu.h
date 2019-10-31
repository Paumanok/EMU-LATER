#ifndef CPU_H__
#define CPU_H__
/**********************************************
 * NES EMU-LATOR cpu header file
 *Author: Matthew Smith mrs9107@g.rit.edu
 *
 * Date: 
 * *********************************************/

#include <stdint.h> 
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

//status flags for the status register(p)
#define CARRY_FLAG (0x1)
#define ZERO_FLAG (0X2)
#define IRQ_DISABLE_FLAG (0x4) //1=disabled
#define DECIMAL_FLAG (0x8) //disabled on actual nes 6502
#define BRK_FLAG (0x10)
#define OVERFLOW_FLAG (0X40)
#define NEGATIVE_FLAG (0x80)

int cpu(NES* nes);
int init_cpu(MOS6502* cpu);
void reset(MOS6502* cpu);
#endif //CPU_H__
