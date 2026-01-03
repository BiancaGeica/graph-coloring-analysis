#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// Folosim o matrice globala pentru a nu umple stiva (evitam stack overflow)
// char ocupa 1 byte, deci e safe
char matrice[3005][3005]; 

//Functie pentru generare de grafuri aleatorii cu densitate predefinita
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

/* **************************************************** */
/** ~*~ ~Functii generatoare de grafuri speciale~ ~*~ **/
/* **************************************************** */

void genereaza_test_graf_complet(char *nume_fisier, int N) {
    FILE *f = fopen(nume_fisier, "w");
    if (!f) {
        printf("Eroare la crearea fisierului %s\n", nume_fisier);
        return;
    }

    //calculam nr. de muchii graf complet
    int M = N * (N - 1) / 2; //Combinari de n luate cate 2

    //scriem header-ul: noduri si muchii
    fprintf(f, "%d %d\n", N, M);
    
    //scriem muchiile
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            fprintf(f, "%d %d\n", i, j);
        }
    }
    
    fclose(f);
    printf("Generat %s: Graf ~complet~, N=%d, M=%d (necesita %d culori)\n", 
           nume_fisier, N, M, N);
}

void genereaza_test_graf_bipartit_complet(char *nume_fisier, int N1, int N2) {
    FILE *f = fopen(nume_fisier, "w");
    if (!f) {
        printf("Eroare la crearea fisierului %s\n", nume_fisier);
        return;
    }
    
    int N = N1 + N2; //numarul total de noduri in graful bipartit este suma nr. de noduri din ambele multimi
    int M = N1 * N2; //nr. muchii graf bipartit complet
    
    //scriem header-ul: numarul de noduri si numarul de muchii al grafului
    fprintf(f, "%d %d\n", N, M);
    
    //scriem muchiile in fisier
    for (int i = 0; i < N1; i++) {
        for (int j = N1; j < N; j++) {
            fprintf(f, "%d %d\n", i, j);
        }
    }
    
    fclose(f);
    printf("Generat %s: Graf ~bipartit complet~, N1=%d, N2=%d, Total=%d, M=%d (necesita 2 culori)\n", 
           nume_fisier, N1, N2, N, M);
}

//Fun fact: grafurile planare sunt des intalnite in aplicaii practice precum crearea hartilor
//graf planar = graf care poate fi desenat in plan a.i. muchiile sa nu se intersecteze
void genereaza_test_graf_planar(char *nume_fisier, int N) {
    FILE *f = fopen(nume_fisier, "w");
    if (!f) {
        printf("Eroare la crearea fisierului %s\n", nume_fisier);
        return;
    }
    
    //generam un graf planar care arata ca o plasa de gard pentru ca matematic un grid este 100% planar
    int latime = (int)sqrt(N); //grid-ul este un patrat
    int lungime = (N + latime - 1) / latime; //de cate randuri avem nevoie in grid ca sa incapa n noduri
    //rotunjim in sus lungimea pentru a nu lasa vreun nod pe dinafara, chiar daca nu se completeaza un patrat complet
    N = latime * lungime;//actualizam valoarea lui n pentru un grid destul de mare incat sa cuprinda toate nodurile
    
    //numar muchii necesare
    int M = 0;
    for (int i = 0; i < lungime; i++) {
        for (int j = 0; j < latime; j++) {
            if (i + 1 < lungime) {
                M++; //muchie care se leaga de nodul din dreapta daca exista
            }
            if (j + 1 < latime) {
                M++; //muchie care se leaga de nodul de dedesubt daca exista
            }
        }
    }
    
    //header fisier
    fprintf(f, "%d %d\n", N, M);
    
    for (int i = 0; i < lungime; i++) {
        for (int j = 0; j < latime; j++) {
            int numar_nod = i * latime + j;
            //muchia spre dreapta
            if (j + 1 < latime) {
                fprintf(f, "%d %d\n", numar_nod, numar_nod + 1);
            }
            //muchia spre nodul de jos
            if (i + 1 < lungime) {
                fprintf(f, "%d %d\n", numar_nod, numar_nod + latime);
            }
        }
    }
    
    fclose(f);
    printf("Generat %s: Graf ~planar~ (harta %dx%d), N=%d, M=%d (necesita 2-4 culori)\n", 
           nume_fisier, latime, lungime, N, M);
}

//graf cordal = graf in care avem doar triunghiuri
void genereaza_graf_cordal(char *nume_fisier, int N) {
    FILE *f = fopen(nume_fisier, "w");
    if (!f) {
        printf("Eroare la crearea fisierului %s\n", nume_fisier);
        return;
    }
    
    //initializare matrice
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrice[i][j] = 0;
    
    for (int i = 1; i < N; i++) { //de la 1 pt ca 0 este radacina, generam un arbore random
        //generam arbore pentru a fi siguri ca nu exista noduri izolate
        int nod_parinte = rand() % i;
        matrice[i][nod_parinte] = 1;
        matrice[nod_parinte][i] = 1;
    }
    
    //adaugam coarde unde este necesar
    //clica = multuime de noduri in care toate sunt vecine
    int nr_clici = 3 + rand() % 5; // 3-7 clici
    for (int c = 0; c < nr_clici; c++) {
        int dim_clica = 3 + rand() % 5; // Clici de 3-7 noduri
        int start = rand() % (N - dim_clica + 1);
        
        // Conectează toate nodurile din clica intre ele
        for (int i = start; i < start + dim_clica; i++) {
            for (int j = i + 1; j < start + dim_clica; j++) {
                matrice[i][j] = 1;
                matrice[j][i] = 1;
            }
        }
    }
    
    //numar muchii
    int M = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (matrice[i][j] == 1) M++;
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
    printf("Generat %s: Graf ~cordal~, N=%d, M=%d (DSATUR ar trebui sa fie OPTIM)\n", 
           nume_fisier, N, M);
}

void convertire(int n, char *s) {
    if (n == 0) {
        s[0] = '0';
        s[1] = '\0';
        return;
    }
    int i = 0;
    int aux = n;
    while (aux) {
        aux /= 10;
        i++;
    }
    *(s + i) = '\0';
    while (n > 0) {
        i--;
        *(s + i) = '0' + (n % 10);
        n /= 10;
    }
}



int main() {
    srand(time(NULL)); // Initializare generatorul random cu timpul curent

    printf("~*~ Se genereaza testele 6 - 16 ~*~\n");

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

    printf("~*~ Testele 6 - 16 au fost generate cu succes! ~*~\n");


    printf("~*~ Se genereaza testele 17 - 50: grafuri mici ~*~\n");

    int numar_fisier = 17;
    for (int i = 0; i < 34; i++) {
        char fisier[20];
        char numar_fisier_char[10];
        strcpy(fisier, "test");
        convertire(numar_fisier, numar_fisier_char);
        numar_fisier++;
        strcat(fisier, numar_fisier_char);
        strcat(fisier, ".in");
        int N = 5 + rand() % 16; // 5-20 noduri
        double dens = 0.1 + (rand() % 9) * 0.1;
        genereaza_test(fisier, N, dens);
    }

    printf("~*~ Se genereaza testele 51 - 90: grafuri medii ~*~\n");

    for (int i = 0; i < 40; i++) {
        char fisier[20];
        char numar_fisier_char[10];
        strcpy(fisier, "test");
        convertire(numar_fisier, numar_fisier_char);
        numar_fisier++;
        strcat(fisier, numar_fisier_char);
        strcat(fisier, ".in");
        int N = 20 + rand() % 81; // 20-100 noduri
        double dens = 0.1 + (rand() % 9) * 0.1;
        genereaza_test(fisier, N, dens);
    }

    printf("~*~ Se genereaza testele 91 - 140: grafuri mari, densitate mica ~*~\n");

    for (int i = 0; i < 50; i++) {
        char fisier[20];
        char numar_fisier_char[10];
        strcpy(fisier, "test");
        convertire(numar_fisier, numar_fisier_char);
        numar_fisier++;
        strcat(fisier, numar_fisier_char);
        strcat(fisier, ".in");
        int N = 100 + rand() % 401; // 100-500 noduri
        double dens = 0.05 + (rand() % 6) * 0.05;
        genereaza_test(fisier, N, dens);
    }

    printf("~*~ Se genereaza testele 141 - 180: grafuri mari, densitate medie ~*~\n");

    for (int i = 0; i < 40; i++) {
        char fisier[20];
        char numar_fisier_char[10];
        strcpy(fisier, "test");
        convertire(numar_fisier, numar_fisier_char);
        numar_fisier++;
        strcat(fisier, numar_fisier_char);
        strcat(fisier, ".in");
        int N = 500 + rand() % 2001; // 500-2500 noduri
        double dens = 0.01 + (rand() % 5) * 0.02;
        genereaza_test(fisier, N, dens);
    }

    printf("~*~ Se genereaza testele 181 - 200: grafuri cu numar fix de noduri (500) si densitate variabila ~*~\n");

    for (int i = 0; i < 20; i++) {
        char fisier[20];
        char numar_fisier_char[10];
        strcpy(fisier, "test");
        convertire(numar_fisier, numar_fisier_char);
        numar_fisier++;
        strcat(fisier, numar_fisier_char);
        strcat(fisier, ".in");
        int N = 500;
        double dens = 0.05 * (i + 1);
        genereaza_test(fisier, N, dens);
    }

    printf("~*~ Se genereaza testele 201 - 210: total aleator ~*~\n");

    for (int i = 0; i < 10; i++) {
        char fisier[20];
        char numar_fisier_char[10];
        strcpy(fisier, "test");
        convertire(numar_fisier, numar_fisier_char);
        numar_fisier++;
        strcat(fisier, numar_fisier_char);
        strcat(fisier, ".in");
        int N = 5 + rand() % 2501;
        double dens = 0.01 + (double)(rand() % 40) / 100.0;
        genereaza_test(fisier, N, dens);
    }

    printf("~*~ Se genereaza testele 211 - 217: grafuri speciale ~*~\n");
    genereaza_test_graf_complet("test211.in", 100);
    genereaza_test_graf_bipartit_complet("test212.in", 1000, 1000);
    genereaza_test_graf_planar("test213.in", 2500);
    genereaza_graf_cordal("test214.in", 1500);
    //grafuri hard to color:
    genereaza_test("test215.in", 300, 0.85); //85%
    genereaza_test("test216.in", 500, 0.70); //70%
    genereaza_test("test217.in", 800, 0.50); //50%

    printf("~*~ Testele 17 - 217 au fost generate cu succes! ~*~\n");

    return 0;
}