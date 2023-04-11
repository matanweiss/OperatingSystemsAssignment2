CC=gcc
FLAGS=-Wall -g -o

all: cmp copy codecA codecB encode

cmp: cmp.c
	$(CC) $(FLAGS) cmp cmp.c
copy: copy.c
	$(CC) $(FLAGS) copy copy.c
codecA: codecA.c
	$(CC) -shared -fPIC -o libcodecA.so codecA.c
codecB: codecB.c
	$(CC) -shared -fPIC -o libcodecB.so codecB.c
encode: encode.o
	$(CC) $(FLAGS) encode encode.o ./libcodecA.so ./libcodecB.so
encode.o: encode.c codec.h
	$(CC) -Wall -c encode.c 
clean:
	rm cmp copy