CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: improbabilidade

improbabilidade: circuito_backtracking.o circuito_calculo.o circuito_memoria_e_inicializacao.o improbabilidade.o
	gcc $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c improbabilidade.h
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f improbabilidade *.o
