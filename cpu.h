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
#include "mmu.h"

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

//helper functions to abstract repetitive code.
void set_flags(NES* nes);
uint16_t addr_es(NES* nes);
uint16_t generic_es(uint8_t lsb, uint8_t msb);
uint16_t rafm(NES*, uint16_t base_addr);
uint8_t pcra(NES*, uint16_t);
uint8_t zero_page_read(NES* nes);
uint8_t absolute_read(NES* nes);
void print_cpu_state(NES* nes);
#endif //CPU_H__
