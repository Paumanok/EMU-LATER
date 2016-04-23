/**********************************************
 * NES EMU-LATOR cpu header file
 *Author: Matthew Smith mrs9107@g.rit.edu
 *
 * Date 4-23-16
 * *********************************************/

struct cpu{
    uint16_t *pc;  //program counter
    uint8_t  *A;   //Accumulator register
    uint8_t  *Y;   //Index register Y
    uint8_t  *X;   //Index register X
    uint8_t  *S;   //stack pointer
    
    }MOS6502;

