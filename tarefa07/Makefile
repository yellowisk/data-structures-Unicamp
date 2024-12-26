CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: otimizar

otimizar: otimizar.o expression.o
	gcc $(CFLAGS) otimizar.o expression.o -g $(LDFLAGS) -o otimizar

otimizar.o: otimizar.c expression.h
	gcc $(CFLAGS) -c otimizar.c

expression.o: expression.c expression.h
	gcc $(CFLAGS) -c expression.c

clean:
	rm -f otimizar *.o