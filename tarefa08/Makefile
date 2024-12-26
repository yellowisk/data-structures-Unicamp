CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: cidades

cidades: cidades.c
	gcc $(CFLAGS) cidades.c -o cidades $(LDFLAGS)

clean:
	rm -f cidades
