# environment variables. Compiler and its flags
# to build a debuggable version call make as: "make G=-g"
# this also can be used to pass custom flags to gcc to build the progam
# be aware that the G flags will also be present on executable builds, so be wise when using it.
CC = gcc
CFLAGS = -c -Wall -x c -I ./include/ -O2 -ffunction-sections -fdata-sections -funit-at-a-time -std=c99 -D_GNU_SOURCE

all : build

build : main.o
	$(CC) $(G) lib/main.o -o bin/spanning-tree # TODO add tags for all necesary libs to make the main
	chmod 774 bin/spanning-tree

main.o :
	$(CC) $(CFLAGS) $(G) src/main.c -o lib/main.o
# TODO insert makefile tasks

clean :
	rm -f bin/*

cleanall :
	rm -f bin/* lib/*

exec :
	bin/spanning-tree

