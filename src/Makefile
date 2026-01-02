CC = gcc
# -O3 este critic pentru viteza algoritmilor
CFLAGS = -Wall -O3

# cauta toate fisierele .c din folder
SOURCES = $(wildcard *.c)

# creeaza executabilele
EXECS = $(SOURCES:.c=)

# ==========================================
# REGULI
# ==========================================


# 1. Regula principala make - compileaza toate fisierele gasite
all: $(EXECS)
	@echo "--------------------------------------------------"
	@echo " Au fost create executabilele:"
	@echo "   $(EXECS)"
	@echo "--------------------------------------------------"

# 2. Regula de compilare (pentru fiecare fisier in parte)
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# 3. Regula clean ('make clean')
clean:
	rm -f $(EXECS) *.o *.exe
	@echo "Director curatat."
	
.PHONY: all clean