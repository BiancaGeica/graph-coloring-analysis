# proiect_analiza_algoritmilor

Acest proiect conține două implementări în limbajul C ale algoritmului DSATUR (Degree of Saturation), o euristică utilizată pentru rezolvarea problemei colorării grafurilor. Scopul algoritmului este de a colora vârfurile unui graf astfel încât două vârfuri adiacente să nu aibă aceeași culoare, încercând să minimizeze numărul total de culori utilizate (numărul cromatic).

Proiectul oferă două abordări distincte în ceea ce privește gestionarea memoriei și reprezentarea grafului:

Varianta Matriceală (Matrice de Adiacență)

    Utilizează o matrice uint8_t de dimensiune N×N.

    Avantaj: Implementare mai directă și acces rapid (O(1)) pentru verificarea existenței unei muchii.

    Dezavantaj: Consum mai mare de memorie O(N²), fiind mai puțin potrivită pentru grafuri foarte mari și rare.
    
Varianta Optimizată (Liste de Adiacență)

    Utilizează liste înlănțuite pentru a stoca vecinii fiecărui vârf.

    Avantaj: Eficientă din punct de vedere al memoriei pentru grafuri rare unde numărul de muchii este mult mai mic decât pătratul numărului de vârfuri.

**Algoritmul DSat pentru grafuri rare, dar cu multe noduri**

*Avantaje:* 

    -Eficienta pe grafuri cu multe noduri si putine muchii (rare), memoria utilizata este proportionala cu numarul de muchii, lucru datorat utilizarii listelor de adiacenta in locul matricii de adiacenta
    -Parcurgerea vecinilor se face folosind lista de adiacenta evitand astfel nodurile neconectate
    -Algoritmul DSatur alege dinamic următorul nod de colorat bazându-se pe gradul de saturație deci obtine frecvent un număr cromatic mai mic (o soluție mai eficientă) comparativ cu algoritmi precum Greedy sau Welsh-Powell, deoarece prioritizează nodurile cu gradul de saturatie cel mai mare.
    
*Dezavantaje*

    -Pe grafuri dense(cu un numar mare de muchii) listele de adiacenta produc un overhead semnificativ
    -Algoritmul nu verifica daca o noua muchie adaugata exista deja deoarece ar consuma foarte multe resurse (Verificarea ar fi O(gradul_nodului))

**Algoritmul DSat pentru grafuri dense, dar cu putine noduri**

*Avantaje:* 

    -Performanta superioara pe grafuri dense
    -Are acces instantaneu la muchii deoarece se verifica direct in matrice
    -Deoarece implementarea folosește tipul de date uint8_t (1 byte) în loc de int (4 bytes) pentru stocarea matricei, memoria este redusa si astfel pot fi procesate grafuri cu dimensiuni mai mari
    
*Dezavantaje*

    -Risipeste multa memorie la grafurile rare deoarece aloca memorie pentru un graf complet indiferent de cate muchii are graful
    -Ineficient in gasirea vecinilor, algoritmul este nevoit sa parcurga toate nodurile grafului pentru fiecare verificare