CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: corretor

corretor: corretor.c
	gcc $(CFLAGS) corretor.c -o corretor $(LDFLAGS)

clean:
	rm -f corretor
