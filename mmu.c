/*
 * Memory Managment Unit
 * 
 *  Here we will handle various reads and writes to 
 *  various memory structures the NES has access to.
 *
 *  Implementation of Mappers will also exist here.
 *
 *  This will also handle emulating various 
 *  game cart hardware as the NES hardware has no 
 *  understanding of these variations
 */

#include "mmu.h"

// Base of MMU controller
// switch on mapper type to direct
// memory ops correctly depending on the game. 
int mmu_ctrl(NES* nes){
    
    switch(nes->rom->mapper) {
        case 0x00:
            //printf("Mapper in progress");
            return mapper_0(nes);
        case 0x01:
            printf("Mapper in progress");

        default:
            return BAD_ADDRESS ;

    }
}

//arbitrary memory read byte
//reads byte from memory without disturbing cpu state
uint8_t amrb(NES* nes, uint16_t address){
    uint16_t ab_bak = nes->addr_bus;
    uint8_t  db_bak = nes->data_bus;
    uint8_t  cb_bak = nes->ctrl_bus;
    uint8_t  ret_byte = 0;

    nes->addr_bus = address;
    nes->ctrl_bus = READ;
    if(mmu_ctrl(nes) >= SUCCESS)
        ret_byte = nes->data_bus;

    nes->addr_bus = ab_bak;
    nes->data_bus = db_bak;
    nes->ctrl_bus = cb_bak;

    return ret_byte;
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
            nes->ppu_regs[(address % 8) - PPU_OFFSET] = nes->data_bus;
        }else{
            nes->data_bus = nes->ppu_regs[(address % 8) - PPU_OFFSET];
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

// Mapper0/NROM(128/256) implementation
// handles PRG_ROM mirroring switch depending
// on PRG_ROM size.
int mapper_0(NES* nes){
    uint16_t address;
    if(nes->addr_bus < 0x4020){
        return internal_memory(nes);
    
    } else {
    
        //PRG_RAM
        if(nes->addr_bus >= 0x6000 && nes->addr_bus <= 0x7FFF){
            ////comment out for now, sorta broken
            //address = nes->addr_bus - M0_PRAM_OFFSET;
            //if(nes->ctrl_bus){
            //    nes->rom->PRG_RAM[address] = nes->data_bus;
            //
            //}else {
            //    nes->data_bus = nes->rom->PRG_RAM[address];
            //}
            printf("no prg_ram\n"); 
            //PRG_ROM
        } else if(nes->addr_bus >= 0x8000 && nes->addr_bus <= 0xFFFF){
            //is memory continued or mirror(16KB vs 32KB)
            if(nes->rom->header->PRG_ROM_SIZE == 2){
                address = nes->addr_bus - M0_ROM_OFFSET;
            
            } else {
                if(nes->addr_bus > 0xBFFF){ 
                    address = nes->addr_bus - (0x4000 + M0_ROM_OFFSET);
                } else {
                    address = nes->addr_bus - M0_ROM_OFFSET;
                }
            }
            
            nes->data_bus = nes->rom->PRG_ROM[address];
        
        } else {
            return BAD_ADDRESS;
        }
    }
    return SUCCESS;
}
// Writes to internal RAM and handles RAM mirroring
// Doesn't need any relative offsets as ram is at start
// of physical address space.
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

