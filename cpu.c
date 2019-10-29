/*************************************************
 * NES EMU-LATER opensource nes emulator
 * Author: Matt Smith mrs9107@g.rit.edu
 * 
 * purpose: to emulate the cpu portion of the nintendo entertainment system
 *
 * Date:
 * *********************************************/

#include "cpu.h"

int cpu(){

    return 0;
}

//initalizes the memory for the cpu registers
//
int init_cpu(MOS6502 *cpu ){
    cpu->pc = malloc(sizeof(uint16_t));
    cpu->A  = malloc(sizeof(uint8_t));
    cpu->Y  = malloc(sizeof(uint8_t));
    cpu->X  = malloc(sizeof(uint8_t));
    cpu->S  = malloc(sizeof(uint8_t));
    cpu->P  = malloc(sizeof(uint8_t));

    return (cpu->pc && cpu->A && cpu->Y && cpu->X  && cpu->S && cpu->P); 
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


