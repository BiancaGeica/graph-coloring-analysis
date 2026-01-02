# proiect_analiza_algoritmilor

CUM FOLOSESTI MAKEFILE-UL

1. Compilare (Build All) - Transforma toate fisierele .c din directorul curent in executabile.

$ make


2. Curatare (Clean) - Sterge toate executabilele si fisierele temporare.

$ make clean

Prezentare algoritm Welsh-Powell:
 - Welsh-Powell este o euristică Greedy bazată pe gradul nodurilor
 - Ideea de baza este ca nodurile cu multe conexiuni (grad mare) sunt cele mai dificil de colorat, așa că le colorăm primele.

Am consultat diferite implementari gasite pe github in C [1] si in C++ [2], precum si descrieri ale algoritmului [3], [4].


Despre teste:
Dintre grafurile pentru testare, cele de la 1 la 5 au fost scrise manual, celelalte (6-16) au fost generate automat cu generator_teste.c. Testele se pot imparti in 3 categorii, fiecare categorie cu cate 5 teste:

1. Corectitudine (teste mici)
Fisiere: test1.in ... test5.in

Continut:
test1.in - graf complet minim (K3). Are 3 noduri si fiecare este legat de toate celelalte (triunghi). Verifica daca algoritmul stie sa aloce 3 culori distincte cand toti vecinii se cearta intre ei.

test2.in - ciclu par (C4). Are 4 noduri asezate in cerc. Nodul 0 e legat de 1, 1 de 2, 2 de 3 și 3 înapoi la 0. Verifica alternanta culorilor. Fiind nr par de noduri, ar trebui sa foloseasca doar 2 culori.

test3.in - graf complet (K5)."Worst case". Are 5 noduri si toate sunt conectate intre ele. Ar trebui sa aleaga eexact N culori (5 in cazul asta).

test4.in - graf tip stea. Are un nod central conectat la mai multe noduri periferice care nu au legatura intre ele. Testul perfect pentru Welsh-Powell pt ca algoritmul sorteaza nodurile dupa grad, iar aici nodul central are grad mare (5), restul au grad mic (1). Ar trebui sa coloreze intai centrul si apoi sa refoloseasca o singura culoare pentru toate celelalte noduri din jur (2 culori total).

test5.in - graf cu componente izolate. Testul contine de fapt doua grupuri de noduri care nu au nicio legatura intre ele (un triunghi intr-o parte si alt triunghi in cealalta parte). Daca primul grup foloseste culorile 1, 2, 3 algoritmul ar trebui sa foloseasca tot culorile 1, 2, 3 pentru al doilea grup.

Scop: sa demonstreze ca algoritmul nu "bajbaie" si da rezultatul corect.

Generat: manual

2. Scalabilitate (teste mari - random)
Fisiere: test6.in ... test10.in

Continut: grafuri generate aleator unde N creste progresiv (50 -> 2000)
Scop: sa vad cum se comporta algoritmul la crestera nr de noduri (N)
merge generat un grafic "timp de executie vs. numar de noduri"

Generat: automat

3. Densitate (teste complexe - random)
Fisiere: test11.in ... test16.in
Continut: grafuri cu N = 500, dar cu densitate de la 10% la 100%.
Scop: generare grafic "numar de culori vs. densitate" (sau timp vs densitate)
vad cum se comportă algoritmul cand graful e mai "incalcit" (multe muchii), dar pastrand nr de noduri fix.
Generat: automat


Bibliografie:

[1] https://github.com/leovargasdev/grafos/blob/master/welshPowell.c
[2] https://github.com/aprilcoskun/graph-coloring/blob/master/Welsh-Powell.cpp
[3] https://www.geeksforgeeks.org/dsa/welsh-powell-graph-colouring-algorithm/
[4] https://en.wikipedia.org/wiki/Floyd–Warshall_algorithm
