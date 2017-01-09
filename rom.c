/**************
* ROM parser for EMU-LATER
* Author: Matthew Smith mrs9107@g.rit.edu
*
*
**************/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "rom.h"

int debug = 1;
/*
* main function for rom capture and parsing
* given file name and rom struct, fills rom struct with needed data
*/
int getRom(const char* rom){
    int returnState = 1;
    FILE *fp;   
    Header romHeader;
    
    fp = fopen(rom, "rb");
    if(NULL == fp) return -1; //check file loaded
    fread(&romHeader, 1, sizeof(Header), fp); //read header

    //check for 'NES1A' in header to confirm .nes file   
    if(memcmp(romHeader.NES, "NES\x1A", sizeof(romHeader.NES))) return -1;
    if(debug)  printf("Header:%s\n reading...\n ", romHeader.NES);

    return returnState;
}
