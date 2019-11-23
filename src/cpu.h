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

//& with instruction to determine addressing modg
#define ADDR_MODE_MASK (0x1F)

//addressing modes
#define INDEXED_INDIRECT  (0x01) 
#define ZERO_PAGE         (0x05)
#define IMMEDIATE         (0x09)
#define ABSOLUTE          (0x0D)
#define INDIRECT_INDEXED  (0x11)
#define ZERO_PAGE_INDEXED (0x15)
#define ABSOLUTE_INDEXEDX (0x19)
#define ABSOLUTE_INDEXEDY (0x1D)

int cpu(NES* nes);
int init_cpu(MOS6502* cpu);
void reset(MOS6502* cpu);

void eval_addr_mode(NES*, uint8_t);
void indexed_indirect(NES* nes);
void zero_page(NES*);
void immediate(NES*);
void absolute(NES*);
void indirect_indexed(NES*);
void zero_page_indexed(NES*);
void absolute_indexed_x(NES*);
void absolute_indexed_y(NES*);

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
