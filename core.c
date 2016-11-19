/*************
* core module for EMU-LATER
*
*************/


#include "cpu.h"
#include "rom.h"
#include "core.h"


int main(int argc, char* argv{}){
  FILE *rom;
  MOS6502 *cpu = initCPU(cpu); //initialize cpu struct

  if( argc == 0){
    fprintf(stderr, "no file specified, exiting");
    return -1;
  }
  else if( argc == 1){
    rom = fopen(argv[1], "r");
    if(rom == NULL){
      fprintf(stderr, "error reading rom file");
      exit(1);
    }else{
      getRom(rom); // this should be returning a rom struct with the various parts stored in memory
    }
  }




}
