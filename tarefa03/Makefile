CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: centroide quase_palindromo recompensa

centroide: centroide.c
	gcc $(CFLAGS) centroide.c -o centroide $(LDFLAGS)

quase_palindromo: quase_palindromo.c
	gcc $(CFLAGS) quase_palindromo.c -o quase_palindromo $(LDFLAGS)

recompensa: recompensa.c
	gcc $(CFLAGS) recompensa.c -o recompensa $(LDFLAGS)

clean:
	rm -f centroide quase_palindromo recompensa
