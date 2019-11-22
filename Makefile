#----------------------------------
# Makefile for EMU-LATER emulator project
# Tested under:
#
# author: Matthew Smith mrs9107@g.rit.edu
#----------------------------------


## for GCC
CC = gcc
CFLAGS = -Wall -pedantic
DFLAGS = -g
SDL_LIB = kiss_sdl2/ kiss_sdl2/include/SDL2

.PHONY: all
all: nes kiss-gui

nes:
	cd src && $(MAKE)

kiss-gui:
	cd gui && $(MAKE)

nes-clean:
	cd src && $(MAKE) clean

gui-clean:
	cd gui && $(MAKE) clean


clean:
	cd src && $(MAKE) clean
	cd gui && $(MAKE) clean
