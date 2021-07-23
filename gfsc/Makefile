CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: banhammer

banhammer: banhammer.o bf.o bv.o hash.o ll.o node.o parser.o speck.o
	$(CC) -o banhammer banhammer.o bf.o bv.o hash.o ll.o node.o parser.o speck.o -lm 

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

bf.o: bf.c bf.h
	$(CC) -c bf.c

bv.o: bv.c bv.h
	$(CC) -c bv.c

hash.o: hash.c hash.h
	$(CC) -c hash.c

ll.o: ll.c ll.h
	$(CC) -c ll.c

node.o: node.c node.h
	$(CC) -c node.c

parser.o: parser.c parser.h
	$(CC) -c parser.c

speck.o: speck.c speck.h
	$(CC) -c speck.c

clean:
	rm -rf main main.o infer-out

infer:
	make clean; scan-build make