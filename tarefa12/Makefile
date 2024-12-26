CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: centros

centros: centros.o cities.o heap.o graph.o
	gcc $(CFLAGS) centros.o cities.o heap.o graph.o $(LDFLAGS) -o centros

centros.o: centros.c cities.h
	gcc $(CFLAGS) -c centros.c

cities.o: cities.c cities.h
	gcc $(CFLAGS) -c cities.c

heap.o: heap.c heap.h
	gcc $(CFLAGS) -c heap.c

graph.o: graph.c graph.h
	gcc $(CFLAGS) -c graph.c

clean:
	rm -f centros *.o