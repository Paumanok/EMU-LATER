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
       if(getRom(argv[1], cart) > 0){
            printf("load sucessful\n\r");
        }else{
            printf("load Failed\n\r");
        }
    }
   return 1;

}
