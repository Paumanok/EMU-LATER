/**************
* ROM parser for EMU-LATER
* Author: Matthew Smith mrs9107@g.rit.edu
*
*
**************/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "rom.h"

int debug = 1;
/*
* main function for rom capture and parsing
* given file name and rom struct, fills rom struct with needed data
*/
int getRom(const char* rom, ROM *cart){
    int returnState = 1;
    FILE *fp;
    Header romHeader;


    fp = fopen(rom, "rb");
    if(NULL == fp) return -1; //check file loaded
    fread(&romHeader, 1, sizeof(Header), fp); //read header

    //check for 'NES1A' in header to confirm .nes file
    if(memcmp(romHeader.NES, "NES\x1A", sizeof(romHeader.NES))){
      if(debug) printf("Header incorrect, exiting");
      return -1;
    }

    if(debug)  printf("Header:%s\n\rreading...\n\r \
    PRG rom size: %d bytes\n \
    CHR rom size: %d bytes\n ", \
    romHeader.NES, romHeader.PRG_ROM_SIZE*PRG_ROM_MULT, romHeader.CHR_ROM_SIZE*CHR_ROM_MULT);


    if(!cartInit(cart, &romHeader)){
      if(debug) printf("Unable to creat virtual cart, exiting");
      return -1;
    }

    if((romHeader.Flag_Six && 4) >> 3){
     fread(cart->trainer, 1, TRAINER_SIZE, fp);
    }

    fread(cart->PRG_ROM, 1, romHeader.PRG_ROM_SIZE * PRG_ROM_MULT, fp);

    fread(cart->CHR_ROM, 1, romHeader.CHR_ROM_SIZE * CHR_ROM_MULT, fp);

    if(debug) {
      //  printf("some data:\n\r");
      //for(int i=0; i<50; i=i+2){
      //  printf("%02x %02x\n\r", cart->PRG_ROM[i],cart->PRG_ROM[i+1]);
      //}
     
      int jumps = 0;
      int loada = 0;
      printf("finding absolute jump instructions...\n\r");
      for(int i = 0; i < romHeader.PRG_ROM_SIZE*PRG_ROM_MULT; i++){
        if(cart->PRG_ROM[i] == 0x4c){
            printf("jmp absolute: jmp $%x%x\n", cart->PRG_ROM[i+2], cart->PRG_ROM[i+1]);
            printf("-----instruction at jump: %02x\n\r", 
                    cart->PRG_ROM[((cart->PRG_ROM[i+2] << 1) | cart->PRG_ROM[i+1])]);
            jumps++;
        }
        if(cart->PRG_ROM[i] == 0xa1){
            printf("load acc indexed indirect: LDA (%02x, X)\n", cart-> PRG_ROM[i+1]);
            loada++;
        }  
      }
      printf(" total number of jump instructions: %d\n", jumps);
      printf(" total number of load instructions: %d\n", loada);
    }

    fclose(fp);
    return returnState;
}

//initialize cart data structure
//this needs to be filled with error checking
int cartInit(ROM *rom, Header *header){
    int playChoiceINST_ROM, playChoicePROM, trainerExists;

    trainerExists = ((header->Flag_Six && 4) >> 3) ? 1 : 0;
    //implement these later if need be
    playChoicePROM = 0;
    playChoiceINST_ROM = 0;
    
    //retain header info
    rom->header = malloc(sizeof(Header));
    memcpy(rom->header, header, sizeof(Header));

    if(trainerExists)
        rom->trainer = calloc(TRAINER_SIZE, sizeof(uint8_t));
    
    if(debug) 
        printf("trainer initialized\n\r");
    
    rom->PRG_ROM = calloc(header->PRG_ROM_SIZE * PRG_ROM_MULT, sizeof(uint8_t));
    
    rom->CHR_ROM = calloc(header->CHR_ROM_SIZE * CHR_ROM_MULT, sizeof(uint8_t));
    
    if(playChoiceINST_ROM) 
        rom->INST_ROM = calloc(INST_ROM_SIZE, sizeof(uint8_t) );
    
    if(playChoicePROM)
        rom->PROM = calloc( PROM_SIZE, sizeof(uint8_t));


    return 1;//bad news bears,need even more real checks
}
