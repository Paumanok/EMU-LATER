/*************************************************
 * NES EMU-LATER opensource nes emulator
 * Author: Matt Smith mrs9107@g.rit.edu
 * 
 * purpose: to emulate the cpu portion of the nintendo entertainment system
 *
 * Date:
 * *********************************************/

#include "cpu.h"

//initalizes the memory for the cpu registers
//
int init_cpu(MOS6502 *cpu ){
    reset(cpu);
    return SUCCESS; 
}

int cpu(NES* nes){
    uint8_t ins = pcra(nes, 0);
    if(DEBUG) printf("instruction: %x\n", ins);
    int cycles = 0;
    eval_addr_mode(nes, ins);
    switch(ins){

    }
    set_flags(nes);

}
void eval_addr_mode(NES* nes, uint8_t ins){
    uint8_t mode = ins && ADDR_MODE_MASK;

    switch(mode){
        case INDEXED_INDIRECT:
            indexed_indirect(nes);
            break;
        case ZERO_PAGE:
            zero_page(nes);
            break;
        case IMMEDIATE:
            immediate(nes);
            break;
        case ABSOLUTE:
            absolute(nes);
            break;
        case INDIRECT_INDEXED:
            indirect_indexed(nes);
            break;
        case ZERO_PAGE_INDEXED:
            zero_page_indexed(nes);
            break;
        case ABSOLUTE_INDEXEDX:
            absolute_indexed_x(nes);
            break;
        case ABSOLUTE_INDEXEDY:
            absolute_indexed_y(nes);
            break;
    }
}
void indexed_indirect(NES* nes){
    nes->addr_bus = pcra(nes, 1) + nes->cpu->X; //ab= X+$aa
    nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)); //ab= *(X+$aa)
}

void zero_page(NES* nes){
    nes->addr_bus = pcra(nes, 1);
}

void immediate(NES* nes){
    //note: not really addressing, use data_bus after using
    pcra(nes, 1);
}

void absolute(NES* nes){
    nes->addr_bus = addr_es(nes);
}

void indirect_indexed(NES* nes){
    nes->addr_bus = pcra(nes, 1); //ab=$aa
    nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)) + nes->cpu->Y; //ab=*($aa)+Y
}

void zero_page_indexed(NES* nes){
    nes->addr_bus = (pcra(nes, 1) + nes->cpu->X);
}

void absolute_indexed_x(NES* nes){
    nes->addr_bus = addr_es(nes) + nes->cpu->X;
}

void absolute_indexed_y(NES* nes){
    nes->addr_bus = addr_es(nes) + nes->cpu->Y;
}

//resets the CPU's registers on boot
//takes a pointer to the cpu struct
void reset(MOS6502 *cpu){
    cpu->pc = 0x0;
    cpu->A  = 0x0;
    cpu->Y  = 0x0;
    cpu->X  = 0x0;
    cpu->S  = 0x0;
    cpu->P  = 0x0;
}

void set_flags(NES* nes){
    //if accumulator is less than both operands, it overflowed
    if(nes->cpu->A < nes->data_bus && nes->cpu->A < absolute_read(nes)) nes->cpu->P |= CARRY_FLAG; 
    if(nes->cpu->A == 0) nes->cpu->P |= ZERO_FLAG;
    //if sign bit set, negative
    if(nes->cpu->A >> 7) nes->cpu->P |= NEGATIVE_FLAG;
}

// address endian swap
// for bytes directly following instruction
uint16_t addr_es(NES* nes){
    return (pcra(nes, 2) << 8 | pcra(nes, 1));
//    return (nes->rom->PRG_ROM[nes->cpu->pc + 2] << 8 | nes->rom->PRG_ROM[nes->cpu->pc + 1]);
}

// generic endian swap
// for bytes in memory
uint16_t generic_es(uint8_t lsb, uint8_t msb){
    uint16_t ret_addr = 0;
    ret_addr = (uint16_t)msb << 8 | lsb;
    return ret_addr;
}

// read address from memory
// will read and endianswap address stored in memory
// es needed for indexing EMU-Later ram/rom 
uint16_t rafm(NES* nes, uint16_t base_addr){
    return generic_es( amrb(nes, base_addr), amrb(nes, base_addr + 1));
}

// program counter read at
uint8_t pcra(NES* nes, uint16_t fo){
    uint8_t db_bak = nes->data_bus; //backup buses
    uint16_t ab_bak = nes->addr_bus; //same
    uint8_t cb_bak = nes->ctrl_bus; //same
    uint8_t ret_byte = 0;

    nes->addr_bus = nes->cpu->pc + fo; //set fetch addr to pc
    nes->ctrl_bus = 0;  //set to read
    if( mmu_ctrl(nes) >= SUCCESS)
        ret_byte = nes->data_bus;

    if(DEBUG) printf("pcra read 0x%x from 0x%x\n",nes->data_bus, nes->addr_bus);
    //regardless of memory read success state, return backups
    nes->data_bus = db_bak;
    nes->addr_bus = ab_bak;
    nes->ctrl_bus = cb_bak;

    return ret_byte;
}


//allow for inline operation with zero_page_read
uint8_t zero_page_read(NES* nes){
    nes->addr_bus &= 0xFF;
    absolute_read(nes);
    return nes->data_bus;
}

uint8_t absolute_read(NES* nes){
    nes->ctrl_bus = 0;
    mmu_ctrl(nes);
    
    if(DEBUG) printf("absolute read 0x%x at 0x%x\n", nes->data_bus, nes->addr_bus);
    return nes->data_bus;
}

void print_cpu_state(NES* nes){
    printf("PC: 0x%04x\n\r" 
           "A : 0x%02x\n\r" 
           "X : 0x%02x\n\r" 
           "Y : 0x%02x\n\r" 
           "AB: 0x%04x\n\r" 
           "DB: 0x%02x\n\r" 
           "CB: 0x%02x\n\n", 
            nes->cpu->pc, nes->cpu->A, nes->cpu->X, 
            nes->cpu->Y, nes->addr_bus, nes->data_bus, 
            nes->ctrl_bus);

}


