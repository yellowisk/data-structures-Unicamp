CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: piscapisca

piscapisca: piscapisca.c
	gcc $(CFLAGS) piscapisca.c -o piscapisca $(LDFLAGS)

clean:
	rm -f piscapisca
