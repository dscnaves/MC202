CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: banco

banco: cidades.o cidades_tad.o
	
	gcc $(CFLAGS) cidades.o cidades_tad.o -o cidades $(LDFLAGS)

cidades.o: cidades.c cidades.h
	gcc $(CFLAGS) -c cidades.c

cidades_tad.o: cidades_tad.c cidades.h
	gcc $(CFLAGS) -c cidades_tad.c

clean:
	rm -f cidades *.o
