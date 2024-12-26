CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: cache

cache: cache.o arranger.o
	gcc $(CFLAGS) cache.o arranger.o $(LDFLAGS) -o cache

cache.o: cache.c arranger.h
	gcc $(CFLAGS) -c cache.c

arranger.o: arranger.c arranger.h
	gcc $(CFLAGS) -c arranger.c

clean:
	rm -f cache *.o