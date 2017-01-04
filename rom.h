/****************
*rom parser header file
* author: matthew smith
*
*****************/


struct romFile{
    uint8_t NES[4];
    uint8_t PRG_ROM_SIZE;
    uint8_t CHR_ROM_SIZE;
    uint8_t INST_ROM;
    uint8_t PROM;
}

struct header{
    uint8_t rom_size_offset;
    uint8_t chr_size_offset;
}

