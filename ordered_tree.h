//Written by Johan Eliasson <johane@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) at Umeå University.
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
Syfte: Skapa ett nytt träd med en rotnod
Returvärde: Trädet
Kommentarer:
*/
otree * otree_create();

/*
Syfte: Installera en minneshanterare för trädet så att den kan ta över
       ansvaret för att avallokera minnet för värdena då de ej finns kvar
       i trädet mer.
Parametrar: t - trädet
            f - en funktionspekare till en funktion som tar in ett värde
                av typen data (void pekare) och avallokerar minnet för värdet
                den pekar på (ett av den typ av värden som lagras i trädet).
Kommentarer: Bör anropas direkt efter att trädet skapats om funktionaliteten
             ska användas. Trädet funkar även utan att denna funktion anropas,
             men det är då upp till användaren av datatypen att avallokera allt
             minne för datat som lagras i trädet.
*/
void otree_setMemHandler(otree *t, memFreeFunc *f);

/*
Syfte: Hämta en nods etikett
Parametrar: tree - trädet
            p - positionen för noden
Returvärde: värdet på etiketten
Kommentarer:
*/
data otree_inspectLabel(otree *tree,otree_pos p);

/*
Syfte: Sätta en etikett för en nod
Parametrar: tree - trädet
            label - etiketten för noden
            p - positionen för noden
Kommentarer:
*/
void otree_setLabel(otree *tree,data d,otree_pos p);

/*
Syfte: Hämta positionen för rotnoden
Parametrar: trädet
Returvärde: positionen för rotnoden
Kommentarer:
*/
otree_pos otree_root(otree *tree);

/*
Syfte: Sätta in ett första barn för en nod.
Parametrar: tree - trädet
            p - positionen för node
Returvärde: positionen för den insatta noden
Kommentarer: Tidigare första nod kommer om en sådan finns efter
             anropet vara barn nummer 2.
*/
otree_pos otree_insertFirstChild(otree *tree,otree_pos p);

/*
Syfte: sätta in ett syskon till efter den givna noden
Parametrar: tree - trädet
            p - positionen för node
Returvärde: positionen för den insatta noden
Kommentarer:
*/
otree_pos otree_insertNextSibling(otree *tree,otree_pos p);

/*
Syfte: Ta bort en nod ur trädet
Parametrar: tree - trädet
            p - positionen för noden
Returvärde: position för föräldranoden till noden som togs bort
Kommentarer: Om noden som ska tas bort har barn kommer även dessa tas bort
*/
otree_pos otree_deleteNode(otree *tree,otree_pos p);

/*
Syfte: Hämtar positionen för en nods första barn
Parametrar: tree - trädet
            p - positionen för noden
Returvärde: positionen för det första barnet eller NULL
            om ett första barn ej finns
Kommentarer:
*/
otree_pos otree_firstChild(otree *tree,otree_pos p);

/*
Syfte: Häftar en nods nästa syskon
Parametrar: tree - trädet
            p - positionen för noden
Returvärde: positionen för syskonet eller NULL om det inte finns fler syskon
Kommentarer:
*/
otree_pos otree_nextSibling(otree *tree,otree_pos p);

/*
Syfte: Hämta positionen för föräldern
Parametrar: tree - trädet
            n - positionen vars förälder man vill hämta
Returvärde: positionen för föräldern
Kommentarer: Ej definierad för rotnoden
*/
otree_pos otree_parent(otree *tree,otree_pos p);

/*
Syfte: Kontrollera om en etikett finns i noden
Parametrar: tree - trädet
            p - positionen för noden
Returvärde: true om noden har en etikett annars false
Kommentarer:
*/
bool otree_hasLabel(otree *tree,otree_pos p);

/*
Syfte: Avallokerar minnet som använts av trädet
Parametrar: tree - trädet
Kommentarer: Trädet är ej längre definierat efter anrop till denna
             funktion
*/
void otree_free(otree *tree);
