%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%IMPLEMENTARE%%%%%%%%%%%%%%%%%%%%%%%%%%%%

INPUT: FOTOGRAGIILE FOLOSITE
REF: REFERINTE
OUTPUT: SE POATE AFISA OUTPUTUL MODIFICAND FISIERUL TEST.SH

Inainte de toate, am modificat headerele ca sa le apelez direct bmp_infoheader
sau bmp_fileheader, apoi privind citirea imaginei cum ea era rasturata am ales
sa o citesc de la coada la cap avand o matrice care are fix imaginea nerastur-
nata.

AM FOLOSIT FOARTE MULTE COMENTARII IN COD (100-200 DE LINII)
SUNT ORIENTATIVE PENTRU MINE DAR SI PENTRU CINE CITESTE COD
AM SEPARAT TASKURILE PENTRU O CITIRE MAI CLARA
Am creat functii pentru citire, scriere , free , adaugare imagine, exportare
de imagine etc.. ca sa incerc sa nu umplu functia main foarte mult.

TASKUL 1:

Ideea de pe acest task este ca se aplica pe fiecare pixel suma de pe r,b si g
care se imparte la trei apoi se distribuie a fiecare componenta a pixelului.
NU stiu ce as putea spune mai mult despre acest task. Am folosit functii de
prelucrare de cuvinte pentru a creea numele fisierelor.
AM creeat o imagine noua unde salvez valorile de pe fiecare pixel pentru a
nu modifica imaginea initiala sa nu infulenteze restul valorilor iar apoi
copiez valorile de pe imaginiea creeata in imaginea initiala.

TASKUL 2:

Este o functie destul de mare, am ales sa creez un vecotr a care este adaugat
cu valoarea 0 pentru fiecare pozitie de fiecare data cand se intra intr-o noua
pozitie, sunt 9 poziti ale vectorului care in urma conditilor de apartinere la
matricea de pixeli ei pot lua valoarea pixelului de imagine daca apartine de
imagine si nu depaseste marginile sau ramane 0 daca el depaseste marginile si 
se continua prelucrarea.
Aplicarea filturlui se face pe o matrice de 3x3 formata pentru fiecare pixel
aceasta inmultita cu filtrul propriu zis.
La final urmeaza sa copiez noile valori ale pixelilor si imaginea initiala si
sa eliberez imaginea pentru salvarea imaginii cu filtru.

TASKUL 3:

NU l-am facut, in ciuda faptului ca putea sa il fac as fi putut sa creez un fel
de flood fill iterativ unde parcurg linilie si daca gasesc pixeli asemanatori
ii pot baga intro coada care mai apoi cand ajunge la pixelul acela urmand sa 
fie colorat pana cand un pixel e diferint atunci ar devenii noul pixel de 
noua culoare si se parcurge pana cand toti pixelii au fost parcursi apoi copiez
intr-un fisier delimitarile grupurilor de imagine.
DAR CUM AM AVUT O STARE FOAR BUNA DIN CAUZA PARTIALULUI LA MATE1 AM ZIS PAS.

TASKUL 4: 
Inainte copiez headerele din fisiere si ma pozitionez unde trebuie
Aici foarte simplu citeam prima data un pixel + coordonatele apoi dupa asta
adaug o eticheta, apoi citesc inca un pixel + coordonate apoi adaug o conditie
in care ferifica daca culorile corespund cat si linia atunci de la j1 pana la
j2 toti pixelii vor fii colorati cu culoarea respectiva, daca nu atunci pixelul
1 va primii culorile de pe primul pixel citit iar al doilea pixel primeste cu-
lorile de pe al doilea pixel citit, dupa transfer culorile si coordonatele din
pixelul2 in pixelul 1 si apoi ma intreb daca am ajuns la finalul fisierului
daca nu atunci se va duce cu goto la eticheta facuta mai sus si se parcurge
functia mereu pana cand se va ajunge la finalul fisierului, apoi nu am decat
sa creez noua imagine sa copiez headerele apoi sa transcriu imaginea de-
compresata in fisier.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%IMPLEMENTARE%%%%%%%%%%%%%%%%%%%%%%%%%%%%


