#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Functie auxiliara pentru generarea unui singur fisier de test
// Genereaza un graf neorientat, fara bucle (fara muchii de la nod la el insusi)
void genereaza_test(int test_id, int n, int densitate_procent) {
    char nume_fisier[50];
    sprintf(nume_fisier, "test%d.in", test_id);

    FILE *f = fopen(nume_fisier, "w");
    if (f == NULL) {
        printf("Eroare la crearea fisierului %s\n", nume_fisier);
        exit(1);
    }

    // Pasul 1: Scriem N si lasam spatiu gol pentru M (numarul de muchii)
    // Vom reveni aici cu fseek pentru a scrie M-ul corect la final
    fprintf(f, "%d            \n", n); 

    long m = 0; // Contor pentru muchii

    // Pasul 2: Iteram prin toate perechile posibile (i, j) cu i < j
    // Aceasta asigura ca graful este neorientat si fara duplicate
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            // Generam un numar intre 0 si 99
            int sansa = rand() % 100;
            
            // Daca numarul este mai mic decat densitatea, adaugam muchia
            // Exemplu: densitate 10% -> daca sansa < 10 (0..9), adaugam muchia
            if (sansa < densitate_procent) {
                fprintf(f, "%d %d\n", i, j);
                m++;
            }
        }
    }

    // Pasul 3: Ne intoarcem la inceputul fisierului si scriem N si M corect
    rewind(f);
    fprintf(f, "%d %ld", n, m);

    fclose(f);
    printf("Generat %s: N=%d, M=%ld, Densitate=%d%%\n", nume_fisier, n, m, densitate_procent);
}

int main() {
    // Initializam generatorul de numere aleatorii
    srand(time(NULL));

    int test_counter;

    // --- PILONUL 2: SCALABILITATE (11 - 49) ---
    // N: 100 -> 3900 (Pas 100). Densitate fixa 10%
    test_counter = 11;
    for (int n = 100; n <= 3900; n += 100) {
        // Asigura-te ca nu depasim test49 (desi matematica buclei e corecta)
        if (test_counter > 49) break; 
        
        genereaza_test(test_counter, n, 10);
        test_counter++;
    }

    // --- PILONUL 3: DENSITATE (50 - 69) ---
    // N fix 500. Densitate: 5% -> 100% (Pas 5%)
    test_counter = 50;
    for (int d = 5; d <= 100; d += 5) {
        // Asigura-te ca nu depasim test69
        if (test_counter > 69) break;

        genereaza_test(test_counter, 500, d);
        test_counter++;
    }

    printf("\nToate fisierele au fost generate cu succes!\n");

    return 0;
}