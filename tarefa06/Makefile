CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: cobra

cobra: cobra.c
	gcc $(CFLAGS) cobra.c -o cobra $(LDFLAGS)

clean:
	rm -f cobra
