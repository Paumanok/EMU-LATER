/*
 * CPU test module
 * mocks memory and instructions
 *
 */

#include "common.h"
#include "cpu.h"
#include "rom.h"
#include "mmu.h"

int init_nes(NES* nes, char* rom_name);

uint8_t cust_rom[] = {0x01, 0x10, //indexed indirect
                      0x05, 0x12, //zeropage
                      0x09, 0x14, //immediate
                      0x0D, 0x20, 0x01, //absolute #0120
                      0x11, 0x24, //indirect indexed
                      0x15, 0x26,  //zeropage indexed
                      0x19, 0x20, 0x02, //absolute indexed Y
                      0x1D, 0x20, 0x02  //absolute indexed X
};


char* bullshit = "abcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, char* argv[]){
    NES* nes = malloc(sizeof(NES));
    char* romName = "roms/SuperMarioBros.nes"; //doesn't matter, we'll overwrite parts
    
    //initialize with standard params
    init_nes(nes, romName);
    
    //replace rom with dummy
    nes->rom->PRG_ROM = cust_rom;
    
    printf("first place in prg_rom: %x\n", nes->rom->PRG_ROM[0]);
    //fill internal ram with dumbass shit
    nes->ctrl_bus = WRITE;
    for(uint16_t i = 0; i < 0x1000; i++){
        //set ram addr
        nes->addr_bus = i;
        //give data bus a byte from bullshit array
        nes->data_bus = bullshit[i % 62];
        //send away for writin
        mmu_ctrl(nes);
    }
    

    nes->cpu->pc = 0x8000;
    nes->cpu->A = 0xAB;
    nes->cpu->X = 0x8;
    nes->cpu->Y = 0x12;
    nes->ctrl_bus = READ;
    while(nes->cpu->pc < 0x8000 + 19){
        printf("opcode: %x\n", cust_rom[nes->cpu->pc - 0x8000]);
        printf("cylces used: %d\n", cpu(nes));
        print_cpu_state(nes);
        nes->cpu->A = 0xAB;
        sleep(1);  
    }
    
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
    
    //size of ram x 3 mirrors
    nes->int_ram = malloc(sizeof(uint8_t)*0x1FFF);
    if(nes->int_ram == NULL) return INIT_FAIL;
    
    //ppu registers
    nes->ppu_regs = malloc(sizeof(uint8_t)*8);
    if(nes->ppu_regs == NULL) return INIT_FAIL;

    nes->ctrl_bus = 0;
    nes->data_bus = 0;
    nes->addr_bus = 0;


    return SUCCESS;
}   
