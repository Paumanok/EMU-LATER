/*************
* core module for EMU-LATER
*
*************/


#include "core.h"


int main(int argc, char* argv[]){
    char* romName = "roms/SuperMarioBros.nes";
    NES* nes = malloc(sizeof(NES));
    if(init_nes(nes, romName) != SUCCESS) return INIT_FAIL;
    return SUCCESS;
}

int init_nes(NES* nes, char* rom_name){
    ROM* rom = malloc(sizeof(ROM));
    if(rom == NULL) return INIT_FAIL;
    if(!init_rom(rom_name, rom)) return INIT_FAIL;

    MOS6502* cpu = malloc(sizeof(MOS6502));
    if(cpu == NULL) return INIT_FAIL;
    if(!init_cpu(cpu)) return INIT_FAIL;

    nes->rom = rom;
    nes->cpu = cpu;
    nes->ctrl_bus = 0;
    nes->data_bus = 0;
    nes->addr_bus = 0;


    return SUCCESS;
}   

