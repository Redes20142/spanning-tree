# environment variables. Compiler and its flags
# to build a debuggable version call make as: "make G=-g"
# this also can be used to pass custom flags to gcc to build the progam
# be aware that the G flags will also be present on executable builds, so be wise when using it.
CC = gcc
CFLAGS = -c -Wall -x c -I ./include/ -O2 -ffunction-sections -fdata-sections -funit-at-a-time -std=c99 -D_GNU_SOURCE

all : build

build : random.o socket.o bin.o main.o
	$(CC) $(G) -lm lib/random.o lib/socket.o lib/error.o lib/dectobin.o lib/main.o -o bin/spanning-tree
	chmod 774 bin/spanning-tree

main.o :
	$(CC) $(CFLAGS) $(CFLAGS) $(G) src/main.c -o lib/main.o

socket.o :
	$(CC) $(CFLAGS) $(G) src/socket.c -o lib/socket.o
	$(CC) $(CFLAGS) $(G) src/error.c -o lib/error.o

random.o :
	$(CC) $(CFLAGS) $(G) src/random_lib.c -o lib/random.o

bin.o :
	$(CC) $(CFLAGS) $(G) src/binary_converter.c -o lib/dectobin.o

clean :
	rm -f bin/*

cleanall :
	rm -f bin/* lib/*

exec :
	bin/spanning-tree

