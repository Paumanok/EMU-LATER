/*************
* core module for EMU-LATER
*
*************/


#include "cpu.h"
#include "rom.h"
#include "core.h"


int main(int argc, char* argv{}){
  MOS6502 *cpu = initCPU(cpu); //initialize cpu struct
  ROM *cart;
  int sucessState = 0;

  if( argc == 0){
    fprintf(stderr, "no file specified, exiting");
    return -1;
  }
  else if( argc == 1){
    cart = malloc(sizeof(ROM));
    
    sucessState = getRom(argv[1], cart);
    if(sucessState < 1){
      fprintf(stderr, "error reading rom file");
      exit(1);

  }




}
