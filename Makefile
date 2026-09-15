CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11 -IPrograma_Principal -I.

# Fontes do programa principal
SRCS_MAIN = $(wildcard Programa_Principal/*.c)
ifeq ($(strip $(SRCS_MAIN)),)
    SRCS_MAIN = $(filter-out gerador.c, $(wildcard *.c))
endif

# Executáveis
MAIN_EXEC = exec
GERADOR_EXEC = exec_gerador

.PHONY: all clean

all: $(MAIN_EXEC) $(GERADOR_EXEC)

$(MAIN_EXEC): $(SRCS_MAIN)
	$(CC) $(CFLAGS) $^ -o $@

$(GERADOR_EXEC): gerador.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(MAIN_EXEC) $(GERADOR_EXEC) *.o entrada.txt
