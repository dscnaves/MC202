# Nome do executável
EXEC = cache

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

# Arquivos de origem e de cabeçalho
SRC = cache.c cache_tad.c
HEADERS = cache.h

# Indica que 'all' e 'clean' não são arquivos
.PHONY: all clean

# Regra padrão para compilar o programa
all: $(EXEC)

$(EXEC): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC) $(LDFLAGS)

# Limpeza dos arquivos gerados
clean:
	rm -f $(EXEC) *.o
