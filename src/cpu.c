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
    cpu->pc = 0x0;
    cpu->A  = 0x0;
    cpu->Y  = 0x0;
    cpu->X  = 0x0;
    cpu->S  = 0x0;
    cpu->P  = 0x0;

    return SUCCESS; 
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

int cpu(NES* nes){
    int8_t acmb = 0; //defined acm backup
    uint8_t ins = pcra(nes, 0);
    if(DEBUG) printf("instruction: %x\n", ins);
    int cycles = 0;
    switch(ins){
        ////ALU Operations////
//ORA 
        case 0x01:
            //indexed indirect ($aa, X)
            //A |= absolute_read(zero_page_read(x + $aa))
            nes->addr_bus = pcra(nes, 1) + nes->cpu->X; //ab= X+$aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)); //ab= *(X+$aa)
            nes->cpu->A |= absolute_read(nes);           //A |= **(X+$aa)
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 6;
            break;
        case 0x05:
            //zero page $aa
            nes->addr_bus = pcra(nes, 1);
            nes->cpu->A |= zero_page_read(nes);
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 3;
            break;
        case 0x09:
            //immediate #aa
            nes->cpu->A |= pcra(nes, 1);
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 2;
            break;
        case 0x0D:
            //absolute #aaaa
            nes->addr_bus = addr_es(nes);
            nes->cpu->A |= absolute_read(nes);
            nes->cpu->pc += 3;
            set_flags(nes);
            cycles = 4;
            break;
        case 0x11:
            //indirect indexed (#aa), Y
            nes->addr_bus = pcra(nes, 1); //ab=$aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)) + nes->cpu->Y; //ab=*($aa)+Y
            nes->cpu->A |= absolute_read(nes); //A |= *(*($aa) + Y)
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = ((nes->addr_bus & 0xFF) > nes->cpu->Y) ? 5 : 6; //boundry cross check
            break;
        case 0x15:
            //zero page indexed $aa, X
            nes->addr_bus = (pcra(nes, 1) + nes->cpu->X);
            nes->cpu->A |= zero_page_read(nes);
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 4;
            break;
        case 0x19:
            //absolute indexed Y $aaaa, Y
            nes->addr_bus = addr_es(nes) + nes->cpu->Y;
            nes->cpu->A |= absolute_read(nes);
            nes->cpu->pc += 3;
            set_flags(nes);
            cycles = (nes->addr_bus & 0xFF) > nes->cpu->Y ? 4 : 5;
            break;
        case 0x1D:
            //absolute indexed X $aaaa, X
            nes->addr_bus = addr_es(nes) + nes->cpu->X;
            nes->cpu->A |= absolute_read(nes);
            nes->cpu->pc += 3;
            set_flags(nes);
            cycles = (nes->addr_bus & 0xFF) > nes->cpu->X ? 4 : 5;
            break;
//AND
        case 0x21:
            //indexed indirect ($aa, X)
            nes->addr_bus = pcra(nes, 1) + nes->cpu->X; //ab= X+$aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)); //ab= *(X+$aa)
            nes->cpu->A &= absolute_read(nes);           //A &= **(X+$aa)
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 6;
            break;
        case 0x25:
            //zero page $aa
            nes->addr_bus = pcra(nes, 1);
            nes->cpu->A &= zero_page_read(nes);
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 3;
            break;
        case 0x29:
            //immediate #aa
            nes->cpu->A &= pcra(nes, 1);
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 2;
            break;
        case 0x2D:
            //absolute #aaaa
            nes->addr_bus = addr_es(nes);
            nes->cpu->A &= absolute_read(nes);
            nes->cpu->pc += 3;
            set_flags(nes);
            cycles = 4;
            break;
        case 0x31:
            //indirect indexed (#aa), Y
            nes->addr_bus = pcra(nes, 1); //ab=$aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)) + nes->cpu->Y; //ab=*($aa)+Y
            nes->cpu->A &= absolute_read(nes); //A |= *(*($aa) + Y)
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = ((nes->addr_bus & 0xFF) > nes->cpu->Y) ? 5 : 6; //boundry cross check
            break;
        case 0x35:
            //zero page indexed $aa, X
            nes->addr_bus = (pcra(nes, 1) + nes->cpu->X);
            nes->cpu->A &= zero_page_read(nes);
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 4;
            break;
        case 0x39:
            //absolute indexed Y $aaaa, Y
            nes->addr_bus = addr_es(nes) + nes->cpu->Y;
            nes->cpu->A &= absolute_read(nes);
            nes->cpu->pc += 3;
            set_flags(nes);
            cycles = (nes->addr_bus & 0xFF) > nes->cpu->Y ? 4 : 5;
            break;
        case 0x3D:
            //absolute indexed X $aaaa, X
            nes->addr_bus = addr_es(nes) + nes->cpu->X;
            nes->cpu->A &= absolute_read(nes);
            nes->cpu->pc += 3;
            set_flags(nes);
            cycles = (nes->addr_bus & 0xFF) > nes->cpu->X ? 4 : 5;
            break;
//EOR
        case 0x41:
            //indexed indirect ($aa, X)
            nes->addr_bus = pcra(nes, 1) + nes->cpu->X; //ab= X+$aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)); //ab= *(X+$aa)
            nes->cpu->A ^= absolute_read(nes);           //A &= **(X+$aa)
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 6;
            break;
        case 0x45:
            //zero page $aa
            nes->addr_bus = pcra(nes, 1);
            nes->cpu->A ^= zero_page_read(nes);
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 3;
            break;
        case 0x49:
            //immediate #aa
            nes->cpu->A ^= pcra(nes, 1);
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 2;
            break;
        case 0x4D:
            //absolute #aaaa
            nes->addr_bus = addr_es(nes);
            nes->cpu->A ^= absolute_read(nes);
            nes->cpu->pc += 3;
            set_flags(nes);
            cycles = 4;
            break;
        case 0x51:
            //indirect indexed (#aa), Y
            nes->addr_bus = pcra(nes, 1); //ab=$aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)) + nes->cpu->Y; //ab=*($aa)+Y
            nes->cpu->A ^= absolute_read(nes); //A |= *(*($aa) + Y)
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = ((nes->addr_bus & 0xFF) > nes->cpu->Y) ? 5 : 6; //boundry cross check
            break;
        case 0x55:
            //zero page indexed $aa, X
            nes->addr_bus = (pcra(nes, 1) + nes->cpu->X);
            nes->cpu->A ^= zero_page_read(nes);
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 4;
            break;
        case 0x59:
            //absolute indexed Y $aaaa, Y
            nes->addr_bus = addr_es(nes) + nes->cpu->Y;
            nes->cpu->A ^= absolute_read(nes);
            nes->cpu->pc += 3;
            set_flags(nes);
            cycles = (nes->addr_bus & 0xFF) > nes->cpu->Y ? 4 : 5;
            break;
        case 0x5D:
            //absolute indexed X $aaaa, X
            nes->addr_bus = addr_es(nes) + nes->cpu->X;
            nes->cpu->A ^= absolute_read(nes);
            nes->cpu->pc += 3;
            set_flags(nes);
            cycles = (nes->addr_bus & 0xFF) > nes->cpu->X ? 4 : 5;
            break;
//ADC
        case 0x61:
            //indexed indirect ($aa, X)
            nes->addr_bus = pcra(nes, 1) + nes->cpu->X; //ab= X+$aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)); //ab= *(X+$aa)
            nes->cpu->A += absolute_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);           //A += **(X+$aa)
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 6;
        case 0x65:
            //zero page $aa
            nes->addr_bus = pcra(nes, 1);
            nes->cpu->A += zero_page_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 3;
            break;
        case 0x69:
            //immediate #aa
            nes->cpu->A += pcra(nes, 1) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 2;
            break;
        case 0x6D:
            //absolute #aaaa
            nes->addr_bus = addr_es(nes);
            nes->cpu->A += absolute_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            nes->cpu->pc += 3;
            set_flags(nes);
            cycles = 4;
            break;
        case 0x71:
            //indirect indexed (#aa), Y
            nes->addr_bus = pcra(nes, 1); //ab=$aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)) + nes->cpu->Y; //ab=*($aa)+Y
            nes->cpu->A += absolute_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0); //A |= *(*($aa) + Y)
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = ((nes->addr_bus & 0xFF) > nes->cpu->Y) ? 5 : 6; //boundry cross check
            break;
        case 0x75:
            //zero page indexed $aa, X
            nes->addr_bus = (pcra(nes, 1) + nes->cpu->X);
            nes->cpu->A += zero_page_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 4;
            break;
        case 0x79:
            //absolute indexed Y $aaaa, Y
            nes->addr_bus = addr_es(nes) + nes->cpu->Y;
            nes->cpu->A += absolute_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            nes->cpu->pc += 3;
            set_flags(nes);
            cycles = (nes->addr_bus & 0xFF) > nes->cpu->Y ? 4 : 5;
            break;
        case 0x7D:
            //absolute indexed X $aaaa, X
            nes->addr_bus = addr_es(nes) + nes->cpu->X;
            nes->cpu->A += absolute_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            nes->cpu->pc += 3;
            set_flags(nes);
            cycles = (nes->addr_bus & 0xFF) > nes->cpu->X ? 4 : 5;
            break;
//STA
        case 0x81:
            //indexed indirect ($aa, X)
            nes->addr_bus = pcra(nes, 1) + nes->cpu->X; //ab= X+$aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)); //ab= *(X+$aa)
            nes->data_bus = nes->cpu->A;
            nes->ctrl_bus = WRITE;
            mmu_ctrl(nes);
            nes->cpu->pc += 2;
            cycles = 6;
            break;
        case 0x85:
            //zero page $aa
            nes->addr_bus = pcra(nes, 1);
            nes->data_bus = nes->cpu->A;
            nes->ctrl_bus = WRITE;
            mmu_ctrl(nes);
            nes->cpu->pc += 2;
            cycles = 3;
            break;
        case 0x89:
            //NOP
            break;
        case 0x8D:
            //absolute #aaaa
            nes->addr_bus = addr_es(nes);
            nes->data_bus = nes->cpu->A;
            nes->ctrl_bus = WRITE;
            mmu_ctrl(nes);
            nes->cpu->pc += 3;
            cycles = 4;
            break;
        case 0x91:
            //indirect indexed (#aa), Y
            nes->addr_bus = pcra(nes, 1); //ab=$aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)) + nes->cpu->Y; //ab=*($aa)+Y
            nes->data_bus = nes->cpu->A;
            nes->ctrl_bus = WRITE;
            mmu_ctrl(nes);
            nes->cpu->pc += 2;
            cycles = 6;
            break;
        case 0x95:
            //zero page indexed $aa, X
            nes->addr_bus = (pcra(nes, 1) + nes->cpu->X);
            nes->data_bus = nes->cpu->A;
            nes->ctrl_bus = WRITE;
            mmu_ctrl(nes);
            nes->cpu->pc += 2;
            cycles = 4;
            break;
        case 0x99:
            //absolute indexed Y $aaaa, Y
            nes->addr_bus = addr_es(nes) + nes->cpu->Y;
            nes->data_bus = nes->cpu->A;
            nes->ctrl_bus = WRITE;
            mmu_ctrl(nes);
            nes->cpu->pc += 3;
            cycles = 5;
            break;
        case 0x9D:
            //absolute indexed X $aaaa, X
            nes->addr_bus = addr_es(nes) + nes->cpu->X;
            nes->data_bus = nes->cpu->A;
            nes->ctrl_bus = WRITE;
            mmu_ctrl(nes);
            nes->cpu->pc += 3;
            cycles = 5;
            break;
//LDA
        case 0xA1:
            //indexed indirect ($aa, X)
            nes->addr_bus = pcra(nes, 1) + nes->cpu->X; //ab = X+$aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)); //ab= *(X+$aa)
            nes->ctrl_bus = READ;
            mmu_ctrl(nes); //read at address bus and populate databus
            nes->cpu->A = nes->data_bus; 
            set_flags(nes);
            nes->cpu->pc += 2;
            cycles = 6;
            break;
        case 0xA5:
            //zero page $aa
            nes->addr_bus = pcra(nes, 1);
            nes->ctrl_bus = READ;
            mmu_ctrl(nes);
            nes->cpu->A = nes->data_bus;
            set_flags(nes);
            nes->cpu->pc += 2;
            cycles = 3;
            break;
        case 0xA9:
            //immediate #aa
            nes->cpu->A = pcra(nes, 1);
            set_flags(nes);
            nes->cpu->pc += 2;
            cycles = 2;
            break;
        case 0xAD:
            //absolute #aaaa
            nes->addr_bus = addr_es(nes);
            nes->ctrl_bus = READ;
            mmu_ctrl(nes);
            nes->cpu->A = nes->data_bus;
            set_flags(nes);
            nes->cpu->pc += 3;
            cycles = 4;
            break;
        case 0xB1:
            //indirect indexed (#aa), Y
            nes->addr_bus = pcra(nes, 1); //ab = $aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)) + nes->cpu->Y;
            nes->ctrl_bus = READ;
            mmu_ctrl(nes);
            nes->cpu->A = nes->data_bus;
            set_flags(nes);
            nes->cpu->pc += 2;
            cycles = ((nes->addr_bus & 0xFF) > nes->cpu->Y) ? 5 : 6; //boundry cross check
            break;
        case 0xB5:
            //zero page indexed $aa, X
            nes->addr_bus = (pcra(nes, 1) + nes->cpu->X);
            nes->ctrl_bus = READ;
            mmu_ctrl(nes);
            nes->cpu->A = nes->data_bus;
            set_flags(nes);
            nes->cpu->pc += 2;
            cycles = 4;
            break;
        case 0xB9:
            //absolute indexed Y $aaaa, Y
            nes->addr_bus = addr_es(nes) + nes->cpu->Y;
            nes->ctrl_bus = READ;
            mmu_ctrl(nes);
            nes->cpu->A = nes->data_bus;
            set_flags(nes);
            nes->cpu->pc += 3;
            cycles = ((nes->addr_bus & 0xFF) > nes->cpu->Y) ? 4 : 5; //boundry cross check
            break;
        case 0xBD:
            //absolute indexed X $aaaa, X
            nes->addr_bus = addr_es(nes) + nes->cpu->X;
            nes->ctrl_bus = READ;
            mmu_ctrl(nes);
            nes->cpu->A = nes->data_bus;
            set_flags(nes);
            nes->cpu->pc += 3;
            cycles = ((nes->addr_bus & 0xFF) > nes->cpu->Y) ? 4 : 5; //boundry cross check
            break;

//CMP
        //CMP instruction doesn't affect accumulator state so backup/restore of acm register needed
        //in order for set_flags to operate properly
        case 0xC1:
            //indexed indirect ($aa, X)
            nes->addr_bus = pcra(nes, 1) + nes->cpu->X; //ab= X+$aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)); //ab= *(X+$aa)
            acmb = nes->cpu->A; //accumulator backup
            nes->cpu->A -= absolute_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);           //A += **(X+$aa)
            nes->cpu->pc += 2;
            set_flags(nes);
            nes->cpu->A = acmb; //accumulator restore
            cycles = 6;
        case 0xC5:
            //zero page $aa
            nes->addr_bus = pcra(nes, 1);
            acmb = nes->cpu->A; //accumulator backup
            nes->cpu->A -= zero_page_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            nes->cpu->pc += 2;
            set_flags(nes);
            nes->cpu->A = acmb; //accumulator restore
            cycles = 3;
            break;
        case 0xC9:
            //immediate #aa
            nes->cpu->A -= pcra(nes, 1) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            acmb = nes->cpu->A; //accumulator backup
            nes->cpu->pc += 2;
            set_flags(nes);
            nes->cpu->A = acmb; //accumulator restore
            cycles = 2;
            break;
        case 0xCD:
            //absolute #aaaa
            nes->addr_bus = addr_es(nes);
            acmb = nes->cpu->A; //accumulator backup
            nes->cpu->A -= absolute_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            nes->cpu->pc += 3;
            set_flags(nes);
            nes->cpu->A = acmb; //accumulator restore
            cycles = 4;
            break;
        case 0xD1:
            //indirect indexed (#aa), Y
            nes->addr_bus = pcra(nes, 1); //ab=$aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)) + nes->cpu->Y; //ab=*($aa)+Y
            acmb = nes->cpu->A; //accumulator backup
            nes->cpu->A -= absolute_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0); //A |= *(*($aa) + Y)
            nes->cpu->pc += 2;
            set_flags(nes);
            nes->cpu->A = acmb; //accumulator restore
            cycles = ((nes->addr_bus & 0xFF) > nes->cpu->Y) ? 5 : 6; //boundry cross check
            break;
        case 0xD5:
            //zero page indexed $aa, X
            nes->addr_bus = (pcra(nes, 1) + nes->cpu->X);
            nes->cpu->A -= zero_page_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            acmb = nes->cpu->A; //accumulator backup
            nes->cpu->pc += 2;
            set_flags(nes);
            nes->cpu->A = acmb; //accumulator restore
            cycles = 4;
            break;
        case 0xD9:
            //absolute indexed Y $aaaa, Y
            nes->addr_bus = addr_es(nes) + nes->cpu->Y;
            nes->cpu->A -= absolute_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            acmb = nes->cpu->A; //accumulator backup
            nes->cpu->pc += 3;
            set_flags(nes);
            nes->cpu->A = acmb; //accumulator restore
            cycles = (nes->addr_bus & 0xFF) > nes->cpu->Y ? 4 : 5;
            break;
        case 0xDD:
            //absolute indexed X $aaaa, X
            nes->addr_bus = addr_es(nes) + nes->cpu->X;
            acmb = nes->cpu->A; //accumulator backup
            nes->cpu->A -= absolute_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            nes->cpu->pc += 3;
            set_flags(nes);
            nes->cpu->A = acmb; //accumulator restore
            cycles = (nes->addr_bus & 0xFF) > nes->cpu->X ? 4 : 5;
            break;
//SBC
        case 0xE1:
            //indexed indirect ($aa, X)
            nes->addr_bus = pcra(nes, 1) + nes->cpu->X; //ab= X+$aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)); //ab= *(X+$aa)
            nes->cpu->A -= absolute_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);           //A += **(X+$aa)
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 6;
        case 0xE5:
            //zero page $aa
            nes->addr_bus = pcra(nes, 1);
            nes->cpu->A += zero_page_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 3;
            break;
        case 0xE9:
            //immediate #aa
            nes->cpu->A -= pcra(nes, 1) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 2;
            break;
        case 0xED:
            //absolute #aaaa
            nes->addr_bus = addr_es(nes);
            nes->cpu->A -= absolute_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            nes->cpu->pc += 3;
            set_flags(nes);
            cycles = 4;
            break;
        case 0xF1:
            //indirect indexed (#aa), Y
            nes->addr_bus = pcra(nes, 1); //ab=$aa
            nes->addr_bus = rafm(nes, (uint16_t)zero_page_read(nes)) + nes->cpu->Y; //ab=*($aa)+Y
            nes->cpu->A -= absolute_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0); //A |= *(*($aa) + Y)
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = ((nes->addr_bus & 0xFF) > nes->cpu->Y) ? 5 : 6; //boundry cross check
            break;
        case 0xF5:
            //zero page indexed $aa, X
            nes->addr_bus = (pcra(nes, 1) + nes->cpu->X);
            nes->cpu->A -= zero_page_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            nes->cpu->pc += 2;
            set_flags(nes);
            cycles = 4;
            break;
        case 0xF9:
            //absolute indexed Y $aaaa, Y
            nes->addr_bus = addr_es(nes) + nes->cpu->Y;
            nes->cpu->A -= absolute_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            nes->cpu->pc += 3;
            set_flags(nes);
            cycles = (nes->addr_bus & 0xFF) > nes->cpu->Y ? 4 : 5;
            break;
        case 0xFD:
            //absolute indexed X $aaaa, X
            nes->addr_bus = addr_es(nes) + nes->cpu->X;
            nes->cpu->A -= absolute_read(nes) + (nes->cpu->P && CARRY_FLAG ? 1 : 0);
            nes->cpu->pc += 3;
            set_flags(nes);
            cycles = (nes->addr_bus & 0xFF) > nes->cpu->X ? 4 : 5;
            break;
        default:
            return 0;
    }
    return cycles;
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
