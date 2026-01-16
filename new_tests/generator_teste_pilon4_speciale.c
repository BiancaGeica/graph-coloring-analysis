#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// Matrice globala pentru a evita stack overflow la dimensiuni mari (3000+ noduri)
char matrice[3005][3005]; 

// --- Functie generica (folosita pentru Test 16 si 215-217) ---
void genereaza_test(char *nume_fisier, int N, double densitate) {
    FILE *f = fopen(nume_fisier, "w");
    if (!f) {
        printf("Eroare la crearea fisierului %s\n", nume_fisier);
        return;
    }

    // 1. Resetam matricea
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrice[i][j] = 0;

    int M = 0; // contor muchii
    
    // 2. Generam muchiile random
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            double r = (double)rand() / RAND_MAX;
            if (r < densitate) {
                matrice[i][j] = 1;
                matrice[j][i] = 1;
                M++;
            }
        }
    }

    fprintf(f, "%d %d\n", N, M);

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

// --- Functii pentru grafuri speciale (Testele 211-214) ---

void genereaza_test_graf_complet(char *nume_fisier, int N) {
    FILE *f = fopen(nume_fisier, "w");
    if (!f) return;

    int M = N * (N - 1) / 2; 
    fprintf(f, "%d %d\n", N, M);
    
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            fprintf(f, "%d %d\n", i, j);
        }
    }
    fclose(f);
    printf("Generat %s: Graf COMPLET, N=%d\n", nume_fisier, N);
}

void genereaza_test_graf_bipartit_complet(char *nume_fisier, int N1, int N2) {
    FILE *f = fopen(nume_fisier, "w");
    if (!f) return;
    
    int N = N1 + N2;
    int M = N1 * N2;
    
    fprintf(f, "%d %d\n", N, M);
    for (int i = 0; i < N1; i++) {
        for (int j = N1; j < N; j++) {
            fprintf(f, "%d %d\n", i, j);
        }
    }
    fclose(f);
    printf("Generat %s: Graf BIPARTIT COMPLET, N=%d\n", nume_fisier, N);
}

void genereaza_test_graf_planar(char *nume_fisier, int N) {
    FILE *f = fopen(nume_fisier, "w");
    if (!f) return;
    
    int latime = (int)sqrt(N);
    int lungime = (N + latime - 1) / latime;
    N = latime * lungime;
    
    int M = 0;
    // Calculam muchiile in avans
    for (int i = 0; i < lungime; i++) {
        for (int j = 0; j < latime; j++) {
            if (i + 1 < lungime) M++;
            if (j + 1 < latime) M++;
        }
    }
    
    fprintf(f, "%d %d\n", N, M);
    
    for (int i = 0; i < lungime; i++) {
        for (int j = 0; j < latime; j++) {
            int numar_nod = i * latime + j;
            if (j + 1 < latime) fprintf(f, "%d %d\n", numar_nod, numar_nod + 1);
            if (i + 1 < lungime) fprintf(f, "%d %d\n", numar_nod, numar_nod + latime);
        }
    }
    fclose(f);
    printf("Generat %s: Graf PLANAR (Grid), N=%d\n", nume_fisier, N);
}

void genereaza_graf_cordal(char *nume_fisier, int N) {
    FILE *f = fopen(nume_fisier, "w");
    if (!f) return;
    
    // Reset matrice
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrice[i][j] = 0;
    
    // Generare arbore de baza
    for (int i = 1; i < N; i++) {
        int nod_parinte = rand() % i;
        matrice[i][nod_parinte] = 1;
        matrice[nod_parinte][i] = 1;
    }
    
    // Adaugare clici (triunghiulari)
    int nr_clici = 3 + rand() % 5;
    for (int c = 0; c < nr_clici; c++) {
        int dim_clica = 3 + rand() % 5;
        int start = rand() % (N - dim_clica + 1);
        for (int i = start; i < start + dim_clica; i++) {
            for (int j = i + 1; j < start + dim_clica; j++) {
                matrice[i][j] = 1;
                matrice[j][i] = 1;
            }
        }
    }
    
    int M = 0;
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (matrice[i][j] == 1) M++;
    
    fprintf(f, "%d %d\n", N, M);
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (matrice[i][j] == 1) {
                fprintf(f, "%d %d\n", i, j);
            }
        }
    }
    fclose(f);
    printf("Generat %s: Graf CORDAL, N=%d\n", nume_fisier, N);
}

// --- MAIN ---
int main() {
    srand(time(NULL));

    printf("~*~ Generare Grafuri Speciale si Worst Case ~*~\n\n");

    // 1. Worst Case (Graf dens/complet mic)
    genereaza_test("test16.in", 100, 1.0); 

    // 2. Grafuri Speciale
    genereaza_test_graf_complet("test211.in", 100);
    genereaza_test_graf_bipartit_complet("test212.in", 1000, 1000);
    genereaza_test_graf_planar("test213.in", 2500);
    genereaza_graf_cordal("test214.in", 1500);

    // 3. Grafuri 'Hard to Color' (mari si dense)
    genereaza_test("test215.in", 300, 0.85); // 85% densitate
    genereaza_test("test216.in", 500, 0.70); // 70% densitate
    genereaza_test("test217.in", 800, 0.50); // 50% densitate

    printf("\n~*~ Toate fisierele (16, 211-217) au fost generate! ~*~\n");
    return 0;
}