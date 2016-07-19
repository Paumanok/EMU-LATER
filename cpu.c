/*************************************************
 * NES EMU-LATER opensource nes emulator
 * Product Owner: 
 * Project Manager: Joseph Diment jvd5839@g.rit.edu
 * Author: Matt Smith mrs9107@g.rit.edu
 * 
 * purpose: to emulate the cpu portion of the nintendo entertainment system
 *
 * Date: 1-24-16
 * *********************************************/

#include <stdio.h>
#include "cpu.h"

int cpu(){

    return 0;
}

//initalizes the memory for the cpu registers
//
int initCPU(MOS6502 *cpu ){
    cpu->pc = malloc(sizeof(uint16_t));
    cpu->A  = malloc(sizeof(uint8_t));
    cpu->Y  = malloc(sizeof(uint8_t));
    cpu->X  = malloc(sizeof(uint8_t));
    cpu->S  = malloc(sizeof(uint8_t));
    cpu->P  = malloc(sizeof(uint8_t));

   return 1; //should add malloc checks to avoid segfaults 
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



//bitwise logic functions
//for most of these, it's safe to assume the register where
//the result is stored, is the accumulator.
//////////////////
//AND two registers
//uint8_t *a: result var, should be the accumulator
//uint8_t *b: second register to be passed in.
//uint8_t *s: pointer to status register
inline void AND_byte(uint8_t *a, uint8_t *b, uint8_t *s){
    *a = *a & *b;
    if(*a == 0){
        //set zero flag for status reg
        *s = *s ^ ZERO_FLAG;
    }
}

inline void OR_byte(uint8_t *a, uint8_t *b, uint8_t *s){
   *a = *a | *b;
   if(*a == 0){
       *s = *s ^ ZERO_FLAG;
   }
}

inline void XOR_byte(uint8_t *a, uint8_t *b, uint8_t *s){
    *a = *a ^ *b;
    if(*a == 0){
        *s = *s ^ ZERO_FLAG;
    }
}

