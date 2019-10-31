/**************
* ROM parser for EMU-LATER
* Author: Matthew Smith mrs9107@g.rit.edu
*
*
**************/

#include "rom.h"

/*
* main function for rom capture and parsing
* given file name and rom struct, fills rom struct with needed data
*/
int init_rom(const char* rom, ROM *cart){
    int returnState = 1;
    FILE *fp;
    Header romHeader;

    fp = fopen(rom, "rb");
    if(NULL == fp) return -1; //check file loaded
    fread(&romHeader, 1, sizeof(Header), fp); //read header

    //check for 'NES1A' in header to confirm .nes file
    if(memcmp(romHeader.NES, "NES\x1A", sizeof(romHeader.NES))){
      if(DEBUG) printf("Header incorrect, exiting");
      return -1;
    }

    if(DEBUG)  printf("Header:%s\n\rreading...\n\r \
    PRG rom size: %d bytes\n \
    CHR rom size: %d bytes\n",
    romHeader.NES, romHeader.PRG_ROM_SIZE*PRG_ROM_MULT,
    romHeader.CHR_ROM_SIZE*CHR_ROM_MULT);
    if(!cart_init(cart, &romHeader)){
      if(DEBUG) printf("Unable to create virtual cart, exiting");
      return -1;
    }

    if((romHeader.Flag_Six && 4) >> 3){
     fread(cart->trainer, 1, TRAINER_SIZE, fp);
    }

    fread(cart->PRG_ROM, 1, romHeader.PRG_ROM_SIZE * PRG_ROM_MULT, fp);

    fread(cart->CHR_ROM, 1, romHeader.CHR_ROM_SIZE * CHR_ROM_MULT, fp);

    fclose(fp);
    return returnState;
}

//initialize cart data structure
int cart_init(ROM *rom, Header *header){
    int playChoiceINST_ROM, playChoicePROM, trainerExists;

    trainerExists = ((header->Flag_Six && 4) >> 3) ? 1 : 0;
    //implement these later if need be
    playChoicePROM = 0;
    playChoiceINST_ROM = 0;
    
    //retain header info
    rom->header = malloc(sizeof(Header));
    if(rom->header == NULL) return INIT_FAIL;
    rom->header = header;

    if(trainerExists){
        rom->trainer = calloc(TRAINER_SIZE, sizeof(uint8_t));
        if(rom->trainer == NULL) return INIT_FAIL;
    }

    if(DEBUG) 
        printf("trainer initialized\n\r");
    
    rom->PRG_ROM = calloc(header->PRG_ROM_SIZE * PRG_ROM_MULT, sizeof(uint8_t));
    if(rom->PRG_ROM == NULL) return INIT_FAIL;
    
    rom->CHR_ROM = calloc(header->CHR_ROM_SIZE * CHR_ROM_MULT, sizeof(uint8_t));
    if(rom->CHR_ROM == NULL) return INIT_FAIL;
    
    if(playChoiceINST_ROM){ 
        rom->INST_ROM = calloc(INST_ROM_SIZE, sizeof(uint8_t) );
        if(rom->INST_ROM == NULL) return INIT_FAIL;
    }

    if(playChoicePROM){
        rom->PROM = calloc( PROM_SIZE, sizeof(uint8_t));
        if(rom->PROM == NULL) return INIT_FAIL;
    }

    rom->mapper = (header->Flag_Seven & 0xF0) || ((header->Flag_Six & 0xF0) >> 4);  
    
    return SUCCESS;
}
