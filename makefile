CC=gcc
FLAGS=-Wall -g -o

all: cmp copy codecA codecB encode decode

cmp: cmp.c
	$(CC) $(FLAGS) cmp cmp.c
copy: copy.c
	$(CC) $(FLAGS) copy copy.c
codecA: codecA.c
	$(CC) -shared -fPIC -o libcodecA.so codecA.c
codecB: codecB.c
	$(CC) -shared -fPIC -o libcodecB.so codecB.c
encode: encode.c codec.h
	$(CC) $(FLAGS) encode encode.c ./libcodecA.so ./libcodecB.so
decode: decode.c codec.h
	$(CC) $(FLAGS) decode decode.c ./libcodecA.so ./libcodecB.so
clean:
	rm cmp copy encode decode