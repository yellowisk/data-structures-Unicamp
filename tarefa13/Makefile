CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: improbabilidade

improbabilidade: improbabilidade.c
	gcc $(CFLAGS) improbabilidade.c -o improbabilidade $(LDFLAGS)

clean:
	rm -f improbabilidade
