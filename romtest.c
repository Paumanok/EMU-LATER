//automated test for rom loader

#include <stdio.h>
#include <stdlib.h>
//#include "rom.c"
#include "rom.h"

int main(int argc, char* argv[]);

int main(int argc, char* argv[]){
    ROM *cart;
    cart = malloc(sizeof(ROM));
    
    if(argc > 1){
       if(init_rom(argv[1], cart) > 0){
            printf("load sucessful\n\r"); 
            //some basic instruction parsing to visually validate
            int jumps = 0;
            int loada = 0;
            printf("finding absolute jump instructions...\n\r");
            for(int i = 0; i < (cart->header->PRG_ROM_SIZE*PRG_ROM_MULT)/64; i++){
              if(cart->PRG_ROM[i] == 0x4c){
                  printf("jmp absolute: jmp $%x%x\n", cart->PRG_ROM[i+2], cart->PRG_ROM[i+1]);
                  printf("-----instruction at jump: %02x\n\r", 
                          cart->PRG_ROM[((cart->PRG_ROM[i+2] << 1) | cart->PRG_ROM[i+1])]);
                  jumps++;
              }
              if(cart->PRG_ROM[i] == 0xa1 && 0){
                  printf("load acc indexed indirect: LDA (%02x, X)\n", cart-> PRG_ROM[i+1]);
                  loada++;
              }  
            }
            printf(" total number of jump instructions seen: %d\n", jumps);
            //printf(" total number of load instructions: %d\n", loada);
      
       }else{
            printf("load Failed\n\r");
        }
    }
   return 1;

}
