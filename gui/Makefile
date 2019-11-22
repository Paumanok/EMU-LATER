#----------------------------------
# Makefile for EMU-LATER gui
# Tested under:
#
# author: Matthew Smith mrs9107@g.rit.edu
#----------------------------------


## for GCC
CC = gcc
CFLAGS = -Wall -pedantic
DFLAGS = -g

KISS_SRC = -I../kiss_sdl2/ -I../kiss_sdl2/include/SDL2/
EMU_SRC = ../src/rom.c
GUI_SRC = rom_debug.c rom_debug_kiss_sdl2.c

KISS_LIB_LOC = -L../kiss_sdl2/ -L../kiss_sdl2/lib/
KISS_LIB_INC = -lSDL2 -lSDL2_ttf -lSDL2_image

all: emu_gui


emu_gui:
	$(CC) $(KISS_SRC) $(CFLAGS) $(DFLAGS) $(EMU_SRC) $(GUI_SRC) ../kiss_sdl2/*.c $(KISS_LIB_LOC) $(KISS_LIB_INC) -o ../emu_gui 
#	$(CC) *.o $(KISS_SRC) $(KISS_LIB_LOC) $(KISS_LIB_INC) -o ../emu_gui

clean:
	rm ../emu_gui
