CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: sequencia

sequencia: sequencia.o linked.o
	gcc sequencia.o linked.o -g $(LDFLAGS) -o sequencia

sequencia.o: sequencia.c linked.h
	gcc $(CFLAGS) -c sequencia.c

linked.o: linked.c linked.h
	gcc $(CFLAGS) -c linked.c

clean:
	rm -f sequencia
