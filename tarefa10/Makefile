CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: corretor

corretor: corretor.o grammar.o
	gcc $(CFLAGS) corretor.o grammar.o -g $(LDFLAGS) -o corretor

corretor.o: corretor.c grammar.h
	gcc $(CFLAGS) -c corretor.c

grammar.o: grammar.c grammar.h
	gcc $(CFLAGS) -c grammar.c

clean:
	rm -f corretor *.o