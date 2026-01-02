CC = gcc
# -O3 este esential pentru benchmark (viteza maxima)
CFLAGS = -Wall -O3

# Numele fisierului care genereaza testele (fara .c)
GENERATOR = generator_teste

# Fisierul in care se salveaza testul generat
TEST_FILE = teste.in

# 1. Gaseste toate fisierele .c din folderul curent
SOURCES = $(wildcard *.c)

# 2. Creeaza lista de executabile (scoate extensia .c)
EXECS = $(SOURCES:.c=)

# Regula default: Cand scrii 'make', compileaza TOATE fisierele .c gasite
all: $(EXECS)
	@echo "--------------------------------------------------"
	@echo "Succes! Au fost compilate urmatoarele executabile:"
	@echo "  $(EXECS)"
	@echo "--------------------------------------------------"

# regula generica: transforma orice .c in executabil
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# regula GEN: Genereaza un test nou
gen: $(GENERATOR)
	@echo "Rulare generator..."
	./$(GENERATOR) > $(TEST_FILE)
	@echo "Fisierul $(TEST_FILE) a fost creat."

# utilizare: make run ALG=nume_algoritm
run:
	@if [ -z "$(ALG)" ]; then \
		echo "EROARE: Trebuie sa specifici algoritmul!"; \
		echo "Exemplu: make run ALG=welsh_powell"; \
	else \
		echo "Rulare $(ALG) cu input din $(TEST_FILE)..."; \
		./$(ALG) < $(TEST_FILE); \
	fi

# regula CLEAN: Sterge toate executabilele si fisierele temporare
clean:
	rm -f $(EXECS) $(TEST_FILE) *.o *.exe
	@echo "Curatenie completa."

# regula INFO: Arata ce fisiere a gasit
info:
	@echo "Fisiere sursa gasite: $(SOURCES)"
	@echo "Executabile de creat: $(EXECS)"