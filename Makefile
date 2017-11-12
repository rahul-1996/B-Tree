CC=gcc
CFLAGS= -c -Dt=3 

all: main

main: bTree.o node.o test.o helper.o
	  $(CC) bTree.o node.o test.o helper.o

bTree.o: lib/bTree.c
		$(CC) $(CFLAGS) lib/bTree.c

node.o: lib/node.c
		$(CC) $(CFLAGS) lib/node.c

test.o: test.c 
		$(CC) $(CFLAGS) test.c

helper.o: lib/helper.c
		$(CC) $(CFLAGS) lib/helper.c

clean: 
	rm -rf *.o