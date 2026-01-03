# proiect_analiza_algoritmilor

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

=====Algoritm Degree of Saturation=====

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

    Teste:
    ~*~ Se genereaza testele 6 - 16 ~*~
Generat test6.in: N=50, M=588 (Densitate: 50%)
Generat test7.in: N=100, M=2514 (Densitate: 50%)
Generat test8.in: N=500, M=62124 (Densitate: 50%)
Generat test9.in: N=1000, M=249939 (Densitate: 50%)
Generat test10.in: N=1500, M=562262 (Densitate: 50%)
Generat test11.in: N=500, M=12571 (Densitate: 10%)
Generat test12.in: N=500, M=37533 (Densitate: 30%)
Generat test13.in: N=500, M=62544 (Densitate: 50%)
Generat test14.in: N=500, M=87373 (Densitate: 70%)
Generat test15.in: N=500, M=112457 (Densitate: 90%)
Generat test16.in: N=100, M=4950 (Densitate: 100%)
~*~ Testele 6 - 16 au fost generate cu succes! ~*~
~*~ Se genereaza testele 17 - 50: grafuri mici ~*~
Generat test17.in: N=12, M=6 (Densitate: 10%)
Generat test18.in: N=5, M=9 (Densitate: 90%)
Generat test19.in: N=13, M=26 (Densitate: 40%)
Generat test20.in: N=6, M=0 (Densitate: 20%)
Generat test21.in: N=11, M=21 (Densitate: 40%)
Generat test22.in: N=5, M=3 (Densitate: 20%)
Generat test23.in: N=6, M=2 (Densitate: 20%)
Generat test24.in: N=11, M=14 (Densitate: 20%)
Generat test25.in: N=20, M=26 (Densitate: 10%)
Generat test26.in: N=10, M=36 (Densitate: 80%)
Generat test27.in: N=20, M=23 (Densitate: 10%)
Generat test28.in: N=19, M=70 (Densitate: 40%)
Generat test29.in: N=16, M=14 (Densitate: 10%)
Generat test30.in: N=8, M=16 (Densitate: 60%)
Generat test31.in: N=14, M=20 (Densitate: 30%)
Generat test32.in: N=14, M=7 (Densitate: 10%)
Generat test33.in: N=15, M=84 (Densitate: 80%)
Generat test34.in: N=13, M=33 (Densitate: 40%)
Generat test35.in: N=19, M=45 (Densitate: 30%)
Generat test36.in: N=5, M=2 (Densitate: 10%)
Generat test37.in: N=9, M=31 (Densitate: 90%)
Generat test38.in: N=11, M=4 (Densitate: 10%)
Generat test39.in: N=19, M=35 (Densitate: 20%)
Generat test40.in: N=5, M=4 (Densitate: 30%)
Generat test41.in: N=16, M=7 (Densitate: 10%)
Generat test42.in: N=8, M=8 (Densitate: 30%)
Generat test43.in: N=6, M=3 (Densitate: 30%)
Generat test44.in: N=6, M=5 (Densitate: 50%)
Generat test45.in: N=14, M=17 (Densitate: 20%)
Generat test46.in: N=9, M=34 (Densitate: 90%)
Generat test47.in: N=13, M=23 (Densitate: 30%)
Generat test48.in: N=11, M=13 (Densitate: 20%)
Generat test49.in: N=7, M=18 (Densitate: 80%)
Generat test50.in: N=15, M=86 (Densitate: 80%)
~*~ Se genereaza testele 51 - 90: grafuri medii ~*~
Generat test51.in: N=79, M=656 (Densitate: 20%)
Generat test52.in: N=22, M=214 (Densitate: 90%)
Generat test53.in: N=28, M=32 (Densitate: 10%)
Generat test54.in: N=70, M=734 (Densitate: 30%)
Generat test55.in: N=27, M=155 (Densitate: 40%)
Generat test56.in: N=71, M=734 (Densitate: 30%)
Generat test57.in: N=52, M=230 (Densitate: 20%)
Generat test58.in: N=89, M=780 (Densitate: 20%)
Generat test59.in: N=55, M=108 (Densitate: 10%)
Generat test60.in: N=33, M=479 (Densitate: 90%)
Generat test61.in: N=89, M=759 (Densitate: 20%)
Generat test62.in: N=60, M=913 (Densitate: 50%)
Generat test63.in: N=41, M=747 (Densitate: 90%)
Generat test64.in: N=78, M=1844 (Densitate: 60%)
Generat test65.in: N=81, M=2284 (Densitate: 70%)
Generat test66.in: N=41, M=743 (Densitate: 90%)
Generat test67.in: N=44, M=554 (Densitate: 60%)
Generat test68.in: N=38, M=138 (Densitate: 20%)
Generat test69.in: N=88, M=2311 (Densitate: 60%)
Generat test70.in: N=35, M=353 (Densitate: 60%)
Generat test71.in: N=52, M=1053 (Densitate: 80%)
Generat test72.in: N=99, M=4377 (Densitate: 90%)
Generat test73.in: N=85, M=3214 (Densitate: 90%)
Generat test74.in: N=59, M=520 (Densitate: 30%)
Generat test75.in: N=67, M=458 (Densitate: 20%)
Generat test76.in: N=47, M=533 (Densitate: 50%)
Generat test77.in: N=82, M=1632 (Densitate: 50%)
Generat test78.in: N=91, M=1681 (Densitate: 40%)
Generat test79.in: N=54, M=275 (Densitate: 20%)
Generat test80.in: N=29, M=355 (Densitate: 90%)
Generat test81.in: N=54, M=1268 (Densitate: 90%)
Generat test82.in: N=81, M=2576 (Densitate: 80%)
Generat test83.in: N=76, M=829 (Densitate: 30%)
Generat test84.in: N=99, M=4351 (Densitate: 90%)
Generat test85.in: N=49, M=550 (Densitate: 50%)
Generat test86.in: N=47, M=523 (Densitate: 50%)
Generat test87.in: N=83, M=1410 (Densitate: 40%)
Generat test88.in: N=83, M=683 (Densitate: 20%)
Generat test89.in: N=71, M=2220 (Densitate: 90%)
Generat test90.in: N=52, M=1064 (Densitate: 80%)
~*~ Se genereaza testele 91 - 140: grafuri mari, densitate mica ~*~
Generat test91.in: N=356, M=9498 (Densitate: 15%)
Generat test92.in: N=355, M=6290 (Densitate: 10%)
Generat test93.in: N=306, M=13935 (Densitate: 30%)
Generat test94.in: N=352, M=9281 (Densitate: 15%)
Generat test95.in: N=216, M=5712 (Densitate: 25%)
Generat test96.in: N=186, M=2586 (Densitate: 15%)
Generat test97.in: N=404, M=16468 (Densitate: 20%)
Generat test98.in: N=432, M=18472 (Densitate: 20%)
Generat test99.in: N=252, M=1650 (Densitate: 5%)
Generat test100.in: N=472, M=22408 (Densitate: 20%)
Generat test101.in: N=455, M=25582 (Densitate: 25%)
Generat test102.in: N=335, M=8385 (Densitate: 15%)
Generat test103.in: N=322, M=7773 (Densitate: 15%)
Generat test104.in: N=109, M=1454 (Densitate: 25%)
Generat test105.in: N=221, M=7271 (Densitate: 30%)
Generat test106.in: N=487, M=23597 (Densitate: 20%)
Generat test107.in: N=182, M=4053 (Densitate: 25%)
Generat test108.in: N=204, M=1025 (Densitate: 5%)
Generat test109.in: N=403, M=20189 (Densitate: 25%)
Generat test110.in: N=379, M=3629 (Densitate: 5%)
Generat test111.in: N=247, M=1491 (Densitate: 5%)
Generat test112.in: N=387, M=11204 (Densitate: 15%)
Generat test113.in: N=455, M=5125 (Densitate: 5%)
Generat test114.in: N=274, M=11037 (Densitate: 30%)
Generat test115.in: N=468, M=27426 (Densitate: 25%)
Generat test116.in: N=187, M=3526 (Densitate: 20%)
Generat test117.in: N=332, M=11035 (Densitate: 20%)
Generat test118.in: N=128, M=1210 (Densitate: 15%)
Generat test119.in: N=120, M=2076 (Densitate: 30%)
Generat test120.in: N=456, M=31140 (Densitate: 30%)
Generat test121.in: N=364, M=3339 (Densitate: 5%)
Generat test122.in: N=302, M=11427 (Densitate: 25%)
Generat test123.in: N=166, M=2720 (Densitate: 20%)
Generat test124.in: N=472, M=11280 (Densitate: 10%)
Generat test125.in: N=302, M=2249 (Densitate: 5%)
Generat test126.in: N=206, M=6361 (Densitate: 30%)
Generat test127.in: N=140, M=2414 (Densitate: 25%)
Generat test128.in: N=340, M=14429 (Densitate: 25%)
Generat test129.in: N=322, M=13013 (Densitate: 25%)
Generat test130.in: N=222, M=2412 (Densitate: 10%)
Generat test131.in: N=485, M=5797 (Densitate: 5%)
Generat test132.in: N=295, M=8818 (Densitate: 20%)
Generat test133.in: N=408, M=8253 (Densitate: 10%)
Generat test134.in: N=123, M=704 (Densitate: 10%)
Generat test135.in: N=175, M=3796 (Densitate: 25%)
Generat test136.in: N=236, M=5541 (Densitate: 20%)
Generat test137.in: N=203, M=6165 (Densitate: 30%)
Generat test138.in: N=421, M=26343 (Densitate: 30%)
Generat test139.in: N=420, M=8639 (Densitate: 10%)
Generat test140.in: N=234, M=8199 (Densitate: 30%)
~*~ Se genereaza testele 141 - 180: grafuri mari, densitate medie ~*~
Generat test141.in: N=1353, M=64060 (Densitate: 7%)
Generat test142.in: N=2269, M=77717 (Densitate: 3%)
Generat test143.in: N=982, M=14616 (Densitate: 3%)
Generat test144.in: N=599, M=16139 (Densitate: 9%)
Generat test145.in: N=1508, M=56993 (Densitate: 5%)
Generat test146.in: N=1313, M=77598 (Densitate: 9%)
Generat test147.in: N=1180, M=62826 (Densitate: 9%)
Generat test148.in: N=1965, M=135061 (Densitate: 7%)
Generat test149.in: N=2408, M=261061 (Densitate: 9%)
Generat test150.in: N=2125, M=22908 (Densitate: 1%)
Generat test151.in: N=1898, M=125829 (Densitate: 7%)
Generat test152.in: N=1868, M=157855 (Densitate: 9%)
Generat test153.in: N=1410, M=69474 (Densitate: 7%)
Generat test154.in: N=2001, M=99783 (Densitate: 5%)
Generat test155.in: N=732, M=18634 (Densitate: 7%)
Generat test156.in: N=1312, M=25735 (Densitate: 3%)
Generat test157.in: N=2180, M=214023 (Densitate: 9%)
Generat test158.in: N=1354, M=64112 (Densitate: 7%)
Generat test159.in: N=1385, M=86270 (Densitate: 9%)
Generat test160.in: N=1388, M=67323 (Densitate: 7%)
Generat test161.in: N=2121, M=157005 (Densitate: 7%)
Generat test162.in: N=1952, M=57470 (Densitate: 3%)
Generat test163.in: N=2132, M=67883 (Densitate: 3%)
Generat test164.in: N=1714, M=132338 (Densitate: 9%)
Generat test165.in: N=2026, M=102722 (Densitate: 5%)
Generat test166.in: N=1941, M=18958 (Densitate: 1%)
Generat test167.in: N=1146, M=58982 (Densitate: 9%)
Generat test168.in: N=645, M=6325 (Densitate: 3%)
Generat test169.in: N=659, M=15247 (Densitate: 7%)
Generat test170.in: N=1924, M=129498 (Densitate: 7%)
Generat test171.in: N=1869, M=87252 (Densitate: 5%)
Generat test172.in: N=1686, M=128037 (Densitate: 9%)
Generat test173.in: N=1264, M=40221 (Densitate: 5%)
Generat test174.in: N=536, M=13014 (Densitate: 9%)
Generat test175.in: N=1800, M=80714 (Densitate: 5%)
Generat test176.in: N=515, M=4007 (Densitate: 3%)
Generat test177.in: N=1646, M=94639 (Densitate: 7%)
Generat test178.in: N=1065, M=50876 (Densitate: 9%)
Generat test179.in: N=1447, M=93812 (Densitate: 9%)
Generat test180.in: N=831, M=24247 (Densitate: 7%)
~*~ Se genereaza testele 181 - 200: grafuri cu numar fix de noduri (500) si densitate variabila ~*~
Generat test181.in: N=500, M=6219 (Densitate: 5%)
Generat test182.in: N=500, M=12396 (Densitate: 10%)
Generat test183.in: N=500, M=18856 (Densitate: 15%)
Generat test184.in: N=500, M=25040 (Densitate: 20%)
Generat test185.in: N=500, M=31138 (Densitate: 25%)
Generat test186.in: N=500, M=37371 (Densitate: 30%)
Generat test187.in: N=500, M=43633 (Densitate: 35%)
Generat test188.in: N=500, M=50031 (Densitate: 40%)
Generat test189.in: N=500, M=56071 (Densitate: 45%)
Generat test190.in: N=500, M=62290 (Densitate: 50%)
Generat test191.in: N=500, M=68743 (Densitate: 55%)
Generat test192.in: N=500, M=75026 (Densitate: 60%)
Generat test193.in: N=500, M=80947 (Densitate: 65%)
Generat test194.in: N=500, M=87431 (Densitate: 70%)
Generat test195.in: N=500, M=93292 (Densitate: 75%)
Generat test196.in: N=500, M=100061 (Densitate: 80%)
Generat test197.in: N=500, M=106055 (Densitate: 85%)
Generat test198.in: N=500, M=112205 (Densitate: 90%)
Generat test199.in: N=500, M=118547 (Densitate: 95%)
Generat test200.in: N=500, M=124750 (Densitate: 100%)
~*~ Se genereaza testele 201 - 210: total aleator ~*~
Generat test201.in: N=1214, M=51591 (Densitate: 7%)
Generat test202.in: N=1366, M=335906 (Densitate: 36%)
Generat test203.in: N=1477, M=21790 (Densitate: 2%)
Generat test204.in: N=1660, M=303083 (Densitate: 22%)
Generat test205.in: N=603, M=27244 (Densitate: 15%)
Generat test206.in: N=821, M=114524 (Densitate: 34%)
Generat test207.in: N=1462, M=373572 (Densitate: 35%)
Generat test208.in: N=1469, M=431629 (Densitate: 40%)
Generat test209.in: N=2488, M=1020311 (Densitate: 33%)
Generat test210.in: N=773, M=101398 (Densitate: 34%)
~*~ Se genereaza testele 211 - 217: grafuri speciale ~*~
Generat test211.in: Graf ~complet~, N=100, M=4950 (necesita 100 culori)
Generat test212.in: Graf ~bipartit complet~, N1=1000, N2=1000, Total=2000, M=1000000 (necesita 2 culori)
Generat test213.in: Graf ~planar~ (harta 50x50), N=2500, M=4900 (necesita 2-4 culori)
Generat test214.in: Graf ~cordal~, N=1500, M=1582 (DSATUR ar trebui sa fie OPTIM)
Generat test215.in: N=300, M=38187 (Densitate: 85%)
Generat test216.in: N=500, M=87378 (Densitate: 70%)
Generat test217.in: N=800, M=159660 (Densitate: 50%)
~*~ Testele 17 - 217 au fost generate cu succes! ~*~