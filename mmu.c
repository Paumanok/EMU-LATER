/*
 * Memory Managment Unit
 *
 */

#include "mmu.h"

void mmu_ctl(NES* nes){
    uint16_t address = nes->addr_bus;
    uint8_t control = nes->ctrl_bus;

    //here we will check where in the address range
    //the address bus is pointing to
    //then double check the control bit to see if its a read or write
    //then we can make a determination on whether to store what
    //is in the data bus or load into the data bus
    //
    //maybe there should be a consideration for mapping in this function

}
