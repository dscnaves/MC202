CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: cache

cache: cache.c
	gcc $(CFLAGS) cache.c -o cache $(LDFLAGS)

clean:
	rm -f cache
