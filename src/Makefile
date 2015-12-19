ROOTDIR = $(N64_INST)
CFLAGS = -std=gnu99 -O2 -G0 -Wall -Werror -mtune=vr4300 -march=vr4300 -I$(CURDIR)/include -I$(ROOTDIR)/mips64-elf/include
ASFLAGS = -mtune=vr4300 -march=vr4300
N64PREFIX = $(N64_INST)/bin/mips64-elf-
INSTALLDIR = $(N64_INST)
CC = $(N64PREFIX)gcc
AS = $(N64PREFIX)as
LD = $(N64PREFIX)ld
AR = $(N64PREFIX)ar

all:  spritemap milestest
clean: spritemap-clean milestest-clean

milestest:
	make -C milestest
	make -C milestest copy
milestest-clean:
	make -C milestest clean

spritemap:
	make -C spritemap
	make -C spritemap copy
spritemap-clean:
	make -C spritemap clean

.PHONY: milestest milestest-clean spritemap spritemap-clean
