CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: batcomputador

batcomputador: batcomputador.o memory.o
	gcc $(CFLAGS) batcomputador.o memory.o -g $(LDFLAGS) -o batcomputador

batcomputador.o: batcomputador.c memory.h
	gcc $(CFLAGS) -c batcomputador.c

memory.o: memory.c memory.h
	gcc $(CFLAGS) -c memory.c

clean:
	rm -f batcomputador *.o