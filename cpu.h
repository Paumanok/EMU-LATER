/**********************************************
 * NES EMU-LATOR cpu header file
 *Author: Matthew Smith mrs9107@g.rit.edu
 *
 * Date 4-23-16
 * *********************************************/

#include <stdint.h> 
#include <stdio.h>
#include <stdlib.h>
/***************
  * a data structure used to keep track of
  * the registers used by the cpu
  **************/
typedef struct MOS6502{
    uint16_t *pc;  //program counter
    uint8_t  *A;   //Accumulator register
    uint8_t  *Y;   //Index register Y
    uint8_t  *X;   //Index register X
    uint8_t  *S;   //stack pointer
    uint8_t  *P;   //status register
}MOS6502;

//status flags for the status register(p)
#define CARRY_FLAG (0x1)
#define ZERO_FLAG (0X2)
#define IRQ_DISABLE_FLAG (0x4) //1=disabled
#define DECIMAL_FLAG (0x8) //disabled on actual nes 6502
#define BRK_FLAG (0x10)
#define OVERFLOW_FLAG (0X40)
#define NEGATIVE_FLAG (0x80)

//addressing modes
//non-indexed
inline uint16_t acc(MOS6502* cpu); //accumulator
inline uint16_t imm(MOS6502* cpu); //immediate
inline uint16_t imp(MOS6502* cpu); //implied
inline uint16_t rel(MOS6502* cpu); //relative
inline uint16_t abt(MOS6502* cpu); //absolute
inline uint16_t zpg(MOS6502* cpu); //zero-page
inline uint16_t ind(MOS6502* cpu); //indirect

//indexed
inline uint16_t abt_in(); //absolute indexed
inline uint16_t zpg_in(); //zero-page indexed
inline uint16_t ind_in(); //indirect indexed
inline uint16_t in_ind(); //indexed indirect

//bitwise logic functions
inline void AND_byte(uint8_t *a, uint8_t *b, uint8_t *s);
inline void OR_byte (uint8_t *a, uint8_t *b, uint8_t *s);
inline void XOR_byte(uint8_t *a, uint8_t *b, uint8_t *s);
