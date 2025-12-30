#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Folosim o matrice globala pentru a nu umple stiva (evitam stack overflow)
// char ocupa 1 byte, deci 2005*2005 = ~4MB, ceea ce e safe
char matrice[2005][2005]; 

void genereaza_test(char *nume_fisier, int N, double densitate) {
    FILE *f = fopen(nume_fisier, "w");
    if (!f) {
        printf("Eroare la crearea fisierului %s\n", nume_fisier);
        return;
    }

    // 1. Populam matricea cu 0-uri
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrice[i][j] = 0;

    int M = 0; // contor de muchii
    
    // 2. Generam muchiile random
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // Generam un numar random intre 0.0 si 1.0
            double r = (double)rand() / RAND_MAX;
            
            // Daca numarul e mai mic decat densitatea aleasa, punem muchie
            if (r < densitate) {
                matrice[i][j] = 1;
                matrice[j][i] = 1;
                M++;
            }
        }
    }

    // 3. Scriem headerul (Noduri Muchii)
    fprintf(f, "%d %d\n", N, M);

    // 4. Scriem muchiile
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (matrice[i][j] == 1) {
                fprintf(f, "%d %d\n", i, j);
            }
        }
    }

    fclose(f);
    printf("Generat %s: N=%d, M=%d (Densitate: %.0f%%)\n", nume_fisier, N, M, densitate * 100);
}

int main() {
    srand(time(NULL)); // Initializare generatorul random cu timpul curent

    printf("--- Generarea testelor 6 - 16 ---\n");

    // === SETUL 2: Scalabilitate (Crestem N, Densitate fixa 50%) ===
    genereaza_test("test6.in", 50,   0.5);
    genereaza_test("test7.in", 100,  0.5);
    genereaza_test("test8.in", 500,  0.5);
    genereaza_test("test9.in", 1000, 0.5);
    genereaza_test("test10.in", 1500, 0.5); 

    // === SETUL 3: DENSITATE (N fix 500, variem densitatea) ===
    genereaza_test("test11.in", 500, 0.1); // 10% (rar)
    genereaza_test("test12.in", 500, 0.3); // 30%
    genereaza_test("test13.in", 500, 0.5); // 50% (mediu) - repeta test8, dar e ok pentru claritate
    genereaza_test("test14.in", 500, 0.7); // 70%
    genereaza_test("test15.in", 500, 0.9); // 90% (foarte dens)
    
    // === TEST BONUS: WORST CASE ===
    // Graf complet de 100 noduri (Densitate 1.0 = 100%)
    genereaza_test("test16.in", 100, 1.0); 

    printf("--- Testele 6 - 16 au fost generate cu succes! ---\n");

    return 0;
}
