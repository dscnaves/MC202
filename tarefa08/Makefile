CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm
TARGET = cidades
OBJS = cidades.o cidades_tad.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

cidades.o: cidades.c cidades.h
	$(CC) $(CFLAGS) -c cidades.c

cidades_tad.o: cidades_tad.c cidades.h
	$(CC) $(CFLAGS) -c cidades_tad.c

clean:
	rm -f $(TARGET) $(OBJS)
