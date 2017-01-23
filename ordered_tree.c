//Written by Johan Eliasson <johane@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) at Umeå University.
//Usage exept those listed above requires permission by the author.

#include <stdlib.h>
#include "ordered_tree.h"

/*
Syfte: Skapa ett nytt träd med en rotnod
Returvärde: Trädet
Kommentarer:
*/
otree * otree_create() {
    otree *tree=calloc(1,sizeof(otree));
    tree->root=calloc(1,sizeof(otree_node));
    return tree;
}

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
void otree_setMemHandler(otree *t, memFreeFunc *f) {
    t->freeFunc=f;
}

/*
Syfte: Hämta en nods etikett
Parametrar: tree - trädet
            p - positionen för noden
Returvärde: värdet på etiketten
Kommentarer:
*/
data otree_inspectLabel(otree *tree,otree_pos p){
    return p->label;
}

/*
Syfte: Sätta en etikett för en nod
Parametrar: tree - trädet
            label - etiketten för noden
            p - positionen för noden
Kommentarer:
*/
void otree_setLabel(otree *tree,data d,otree_pos p) {
    p->label=d;
}

/*
Syfte: Hämta positionen för rotnoden
Parametrar: trädet
Returvärde: positionen för rotnoden
Kommentarer:
*/
otree_pos otree_root(otree *tree) {
    return tree->root;
}

/*
Syfte: Sätta in ett första barn för en nod.
Parametrar: tree - trädet
            p - positionen för node
Returvärde: positionen för den insatta noden
Kommentarer: Tidigare första nod kommer om en sådan finns efter
             anropet vara barn nummer 2.
*/
otree_pos otree_insertFirstChild(otree *tree,otree_pos p) {
    otree_pos new=calloc(1,sizeof(otree_node));
    new->parent=p;
    new->nextSibling=p->firstChild;
    p->firstChild=new;
    return new;
}

/*
Syfte: sätta in ett syskon till efter den givna noden
Parametrar: tree - trädet
            p - positionen för node
Returvärde: positionen för den insatta noden
Kommentarer: 
*/
otree_pos otree_insertNextSibling(otree *tree,otree_pos p) {
    otree_pos new=calloc(1,sizeof(otree_node));
    new->nextSibling=p->nextSibling;
    new->parent=p->parent;
    p->nextSibling=new;
    return new;
}

/*
Syfte: Ta bort en nod ur trädet
Parametrar: tree - trädet
            p - positionen för noden
Returvärde: position för föräldranoden till noden som togs bort
Kommentarer: Om noden som ska tas bort har barn kommer även dessa tas bort
*/
otree_pos otree_deleteNode(otree *tree,otree_pos p) {
    otree_pos parent=p->parent;
    if(parent->firstChild==p) {
       parent->firstChild=p->nextSibling;
    }
    else {
       otree_pos prevSibling=parent->firstChild;
       while(prevSibling->nextSibling!=p) {
           prevSibling=prevSibling->nextSibling;
       }
       prevSibling->nextSibling=p->nextSibling;
    }
    while(p->firstChild!=NULL)
        otree_deleteNode(tree,p->firstChild);
    if(tree->freeFunc && otree_hasLabel(tree,p))
        tree->freeFunc(p->label);
    free(p);
    return parent;
}

/*
Syfte: Hämtar positionen för en nods första barn
Parametrar: tree - trädet
            p - positionen för noden
Returvärde: positionen för det första barnet eller NULL 
            om ett första barn ej finns
Kommentarer:
*/
otree_pos otree_firstChild(otree *tree,otree_pos p) {
    return p->firstChild;
}

/*
Syfte: Häftar en nods nästa syskon
Parametrar: tree - trädet
            p - positionen för noden
Returvärde: positionen för syskonet eller NULL om det inte finns fler syskon
Kommentarer:
*/
otree_pos otree_nextSibling(otree *tree,otree_pos p) {
    return p->nextSibling;
}

/*
Syfte: Hämta positionen för föräldern
Parametrar: tree - trädet
            n - positionen vars förälder man vill hämta
Returvärde: positionen för föräldern
Kommentarer: Ej definierad för rotnoden
*/
otree_pos otree_parent(otree *tree,otree_pos p) {
    return p->parent;
}

/*
Syfte: Kontrollera om en etikett finns i noden
Parametrar: tree - trädet
            p - positionen för noden
Returvärde: true om noden har en etikett annars false
Kommentarer:
*/
bool otree_hasLabel(otree *tree,otree_pos p) {
    return p->label!=NULL;
}

/*
Syfte: Avallokerar minnet som använts av trädet
Parametrar: tree - trädet
Kommentarer: Trädet är ej längre definierat efter anrop till denna
             funktion
*/
void otree_free(otree *tree) {
    while(otree_firstChild(tree,tree->root)!=NULL)
        otree_deleteNode(tree,tree->root->firstChild);
    if(tree->freeFunc && otree_hasLabel(tree,tree->root))
        tree->freeFunc(tree->root->label);
    free(tree->root);
    free(tree);
}
