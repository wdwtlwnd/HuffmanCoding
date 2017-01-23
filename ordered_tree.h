//Written by Johan Eliasson <johane@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) at Ume� University.
//Usage exept those listed above requires permission by the author.

#include <stdbool.h>

#ifndef __DATA
#define __DATA
typedef void *data;
#endif

#ifndef __MEMFREEDATAFUNC
#define __MEMFREEDATAFUNC
typedef void memFreeFunc(data);
#endif

typedef struct otree_node {
   struct otree_node *parent;
   struct otree_node *nextSibling;
   struct otree_node *firstChild;
   data label;
} otree_node; 

typedef otree_node * otree_pos;

typedef struct {
    otree_pos root;
    memFreeFunc *freeFunc;
} otree;

/*
Syfte: Skapa ett nytt tr�d med en rotnod
Returv�rde: Tr�det
Kommentarer:
*/
otree * otree_create();

/*
Syfte: Installera en minneshanterare f�r tr�det s� att den kan ta �ver
       ansvaret f�r att avallokera minnet f�r v�rdena d� de ej finns kvar
       i tr�det mer.
Parametrar: t - tr�det
            f - en funktionspekare till en funktion som tar in ett v�rde
                av typen data (void pekare) och avallokerar minnet f�r v�rdet
                den pekar p� (ett av den typ av v�rden som lagras i tr�det).
Kommentarer: B�r anropas direkt efter att tr�det skapats om funktionaliteten
             ska anv�ndas. Tr�det funkar �ven utan att denna funktion anropas,
             men det �r d� upp till anv�ndaren av datatypen att avallokera allt
             minne f�r datat som lagras i tr�det.
*/
void otree_setMemHandler(otree *t, memFreeFunc *f);

/*
Syfte: H�mta en nods etikett
Parametrar: tree - tr�det
            p - positionen f�r noden
Returv�rde: v�rdet p� etiketten
Kommentarer:
*/
data otree_inspectLabel(otree *tree,otree_pos p);

/*
Syfte: S�tta en etikett f�r en nod
Parametrar: tree - tr�det
            label - etiketten f�r noden
            p - positionen f�r noden
Kommentarer:
*/
void otree_setLabel(otree *tree,data d,otree_pos p);

/*
Syfte: H�mta positionen f�r rotnoden
Parametrar: tr�det
Returv�rde: positionen f�r rotnoden
Kommentarer:
*/
otree_pos otree_root(otree *tree);

/*
Syfte: S�tta in ett f�rsta barn f�r en nod.
Parametrar: tree - tr�det
            p - positionen f�r node
Returv�rde: positionen f�r den insatta noden
Kommentarer: Tidigare f�rsta nod kommer om en s�dan finns efter
             anropet vara barn nummer 2.
*/
otree_pos otree_insertFirstChild(otree *tree,otree_pos p);

/*
Syfte: s�tta in ett syskon till efter den givna noden
Parametrar: tree - tr�det
            p - positionen f�r node
Returv�rde: positionen f�r den insatta noden
Kommentarer:
*/
otree_pos otree_insertNextSibling(otree *tree,otree_pos p);

/*
Syfte: Ta bort en nod ur tr�det
Parametrar: tree - tr�det
            p - positionen f�r noden
Returv�rde: position f�r f�r�ldranoden till noden som togs bort
Kommentarer: Om noden som ska tas bort har barn kommer �ven dessa tas bort
*/
otree_pos otree_deleteNode(otree *tree,otree_pos p);

/*
Syfte: H�mtar positionen f�r en nods f�rsta barn
Parametrar: tree - tr�det
            p - positionen f�r noden
Returv�rde: positionen f�r det f�rsta barnet eller NULL
            om ett f�rsta barn ej finns
Kommentarer:
*/
otree_pos otree_firstChild(otree *tree,otree_pos p);

/*
Syfte: H�ftar en nods n�sta syskon
Parametrar: tree - tr�det
            p - positionen f�r noden
Returv�rde: positionen f�r syskonet eller NULL om det inte finns fler syskon
Kommentarer:
*/
otree_pos otree_nextSibling(otree *tree,otree_pos p);

/*
Syfte: H�mta positionen f�r f�r�ldern
Parametrar: tree - tr�det
            n - positionen vars f�r�lder man vill h�mta
Returv�rde: positionen f�r f�r�ldern
Kommentarer: Ej definierad f�r rotnoden
*/
otree_pos otree_parent(otree *tree,otree_pos p);

/*
Syfte: Kontrollera om en etikett finns i noden
Parametrar: tree - tr�det
            p - positionen f�r noden
Returv�rde: true om noden har en etikett annars false
Kommentarer:
*/
bool otree_hasLabel(otree *tree,otree_pos p);

/*
Syfte: Avallokerar minnet som anv�nts av tr�det
Parametrar: tree - tr�det
Kommentarer: Tr�det �r ej l�ngre definierat efter anrop till denna
             funktion
*/
void otree_free(otree *tree);
