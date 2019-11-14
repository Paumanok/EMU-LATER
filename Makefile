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

#build whole project
all: emu-later cpu-test

emu-later: core.o cpu.o rom.o mmu.o
	$(CC) $(CFLAGS) $(DFLAGS)  -o emu-later core.o cpu.o rom.o mmu.o

cpu-test: cputest.c cpu.o rom.o mmu.o
	$(CC) $(CFLAGS) $(DFLAGS) -o cpu-test cputest.c cpu.o rom.o mmu.o

core: core.c core.h common.h cpu.h rom.h
	$(CC) $(CFLAGS) $(DFLAGS) -o core.o

cpu: cpu.c cpu.h common.h
	$(CC) $(CFLAGS) $(DFLAGS) -c cpu.c

rom: rom.c rom.h common.h
	$(CC) $(CFLAGS) $(DFLAGS) -c rom.c

mmu: mmu.c mmu.h common.h
	$(CC) $(CFLAGS) $(DFLAGS) -c mmu.c

clean:
	rm cpu.o
	rm rom.o
	rm core.o
	rm mmu.o
	rm emu-later
	rm cpu-test



