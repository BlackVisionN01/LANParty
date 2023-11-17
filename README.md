# PAHomework

O aplicatie care se ocupa cu aranjarea echipelor in timpul unei competiti dintr-un LanParty.
Sunt realizate toate cele 5 taskuri, task1.c si task2.c folosind functii pentru realizarea primelor 2 cerinta in timp ce task3+4+5.c are functiile pentru realizarea ultimelor 3 cerinte, rezultatul prin checker fiind de 100p.

Pentru task-ul 1:
* se citesc echipele din fisiere si le-am introdus intr-o lista simpla inlantuita de echipe
* se afiseaza toate echipele din lista, numai daca task-ul 1 trebuie sa fie realizat (fisierul c.in este doar de tip 1 0 0 0 0)
  
Pentr task-ul 2:
* se foloseste lista simpla inlantuita de la task-ul 1
* se afla cea mai apropiata putere de a lui 2 mai mica decat numarul total de echipe
* se afla cel mai mic punctaj al unei echipe din lista si se elimina echipa
* se repeta gasirea minimului si eliminarea echipei pana cand numarul de echipe este egal cu puterea apropiata a lui 2
  
Pentru task-ul 3:
* se foloseste lista simpla inlantuita modificata de la task-ul 2
 * se pun echipele intr-o coada, fiecare element din coada fiind format din 2 echipe
 * se afiseaza elementele din coada
 * se impart echipele in 2 stive: echipele castigatoare si echipele invinse
 * determinarea castigatorului si pierzatorului se face prin compararea numarului de puncte al echipei
 * echipele castigatoare sunt afisate si dupa reintroduse in coada
 * echipele invinse sunt eliminate din stiva
* se repeta pana cand mai raman mai raman 2 echipe in coada
* se afiseaza elementel din coada, se muta echipele in una din cele 2 stive fiecare si se afiseaza elementele din stiva de castigatori si se elimina din stiva de invinsi
* cand se ajung la 8 echipe in stiva de castigatori, se retin aceste echipe intr-o stiva noua
  
Pentru task-ul 4:
* se foloseste stiva creata de la task-ul 3 cu ultimele 8 echipe
* se introduc aceste date intr-un arbore astfel incat acesta sa fie un BST(Binary Search Tree)
* se afiseaza in inordine elementele din arborele BST si se retin elementele din arbore in ordinea afisarii intr-o stiva noua
  
Pentr task-ul 5:
* se foloseste stiva creata la task-ul 4 dupa ce au fost afisate elementele din BST
* se creeaza arborele AVL si se introduc elemente din stiva in el, fiind verificata de fiecare data daca arborele este echilibrat sau nu
* se afiseaza elementele de pe nivelul 2 din AVL
OBS TASK 5: Deoarece elementele din stiva creata la task-ul 4 sunt in ordine descrescatoare ordinii dorite pentru adaugarea in arborele AVL, se poate folosi doar mutarea in partea dreapta al arborelui.

La final, sunt inchise toate fisierele utilizate.
Eliberarea spatiului alocat rezolvarii problemei se face pe parcursul intregului program, dar nu este perfecta
  
