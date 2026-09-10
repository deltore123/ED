CC = gcc
PADRAO_C11 = -std=c11
CFLAGS = $(PADRAO_C11) -Wall -Wextra -O2 -DCAP_TERMOS_211=512 -IPrograma_Principal -I.

# Fontes do programa principal
SRCS_MAIN = $(wildcard Programa_Principal/*.c)
ifeq ($(strip $(SRCS_MAIN)),)
    SRCS_MAIN = $(filter-out gerador.c, $(wildcard *.c))
endif

# Executáveis
MAIN_EXEC = poliesparso
GERADOR_EXEC = gerador

.PHONY: all testes clean

all: $(MAIN_EXEC) $(GERADOR_EXEC)

$(MAIN_EXEC): $(SRCS_MAIN)
	$(CC) $(CFLAGS) $^ -o $@

$(GERADOR_EXEC): gerador.c
	$(CC) $(CFLAGS) $< -o $@

testes: all
	@echo "Executando testes com o gerador..."
	@if [ -x ./$(GERADOR_EXEC) ]; then \
		./$(GERADOR_EXEC) > entrada.txt 2>/dev/null || true; \
		if [ -s entrada.txt ]; then \
			./$(MAIN_EXEC) < entrada.txt; \
		else \
			echo "Aviso: entrada.txt vazia ou gerador ainda não implementado."; \
		fi \
	fi

clean:
	rm -f $(MAIN_EXEC) $(GERADOR_EXEC) *.o entrada.txt
