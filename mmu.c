/*
 * Memory Managment Unit
 *
 */

#include "mmu.h"

void mmu_ctl(NES* nes){

    //here we will check where in the address range
    //the address bus is pointing to
    //then double check the control bit to see if its a read or write
    //then we can make a determination on whether to store what
    //is in the data bus or load into the data bus
    //
    //maybe there should be a consideration for mapping in this function
    
    switch(nes->rom->mapper) {
        case 0x00:
            printf("Mapper in progress");
            mapper_0(nes);
        case 0x01:
            printf("Mapper in progress");

        default:
            return;

    }
}

int internal_memory(NES* nes){
    uint16_t address = nes->addr_bus;
    uint8_t control = nes->ctrl_bus;
    
    //Internal Ram
    if(address < 0x2000){
        if(control){
            write_internal_ram(nes);
        }else{
            nes->data_bus = nes->int_ram[nes->addr_bus];
        }
    //PPU registers
    }else if(address >= 0x2000 && address <= 0x3FFF){
        if(control){
            nes->ppu_regs[address % 8] = nes->data_bus;
        }else{
            nes->data_bus = nes->ppu_regs[address % 8];
        }

    //APU & I/O regusters
    }else if(address >=0x4000 && address <= 0x4017){

    }else if(address >= 0x4018 && address <- 0x401F){
        //normally disabled APU/IO functionality--nop
        return BAD_ADDRESS;
    }else if(address >= 0x4020){
        //not this functions problem, shouldn't hit this sector
        return BAD_ADDRESS;
    }else{
        return BAD_ADDRESS;
    }
    return SUCCESS;
}

int mapper_0(NES* nes){
    if(nes->addr_bus < 0x4020){
        return internal_memory(nes);
    
    } else {
    
        //PRG_RAM
        if(nes->addr_bus >= 0x6000 && nes->addr_bus <= 0x7FFF){
            
            if(nes->ctrl_bus){
                nes->rom->PRG_RAM[nes->addr_bus] = nes->data_bus;
            
            }else {
                nes->data_bus = nes->rom->PRG_RAM[nes->addr_bus];
            }
            
            //PRG_ROM
        } else if(nes->addr_bus >= 0x8000 && nes->addr_bus <= 0xFFFF){
            uint16_t address = 0;
            //is memory continued or mirror(16KB vs 32KB)
            if(nes->rom->header->PRG_ROM_SIZE == 2){
                address = nes->addr_bus;
            
            } else {
                if(nes->addr_bus > 0xBFFF) address = nes->addr_bus - 0x4000;
            }
            
            nes->data_bus = nes->rom->PRG_ROM[address];
        
        } else {
            return BAD_ADDRESS;
        }
    }
    return SUCCESS;
}

int write_internal_ram(NES* nes){
    uint16_t address = nes->addr_bus;
    uint8_t data = nes->data_bus;
    uint16_t abs_addr = 0;

    if(address <= 0x07FF){
        abs_addr = address;
    
    }else if(address > 0x07FF && address <= 0x0FFF){
        abs_addr = address - 0x800;
    
    } else if(address > 0x0FFF && address <= 0x17FF){
        abs_addr = address - 0x1000;
        
    }else if( address > 0x17FF && address <= 0x1FFF){
        abs_addr = address - 0x1800;
    } else {
        //not ram
        return BAD_ADDRESS;
    }
    
    //mirror ram for reads 
    nes->int_ram[abs_addr] = data;
    nes->int_ram[abs_addr + 0x800] = data;
    nes->int_ram[abs_addr + 0x1000] = data;
    nes->int_ram[abs_addr + 0x1800] = data;
    
    return SUCCESS;
}

