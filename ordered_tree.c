//Written by Johan Eliasson <johane@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) at Ume� University.
//Usage exept those listed above requires permission by the author.

#include <stdlib.h>
#include "ordered_tree.h"

/*
Syfte: Skapa ett nytt tr�d med en rotnod
Returv�rde: Tr�det
Kommentarer:
*/
otree * otree_create() {
    otree *tree=calloc(1,sizeof(otree));
    tree->root=calloc(1,sizeof(otree_node));
    return tree;
}

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
void otree_setMemHandler(otree *t, memFreeFunc *f) {
    t->freeFunc=f;
}

/*
Syfte: H�mta en nods etikett
Parametrar: tree - tr�det
            p - positionen f�r noden
Returv�rde: v�rdet p� etiketten
Kommentarer:
*/
data otree_inspectLabel(otree *tree,otree_pos p){
    return p->label;
}

/*
Syfte: S�tta en etikett f�r en nod
Parametrar: tree - tr�det
            label - etiketten f�r noden
            p - positionen f�r noden
Kommentarer:
*/
void otree_setLabel(otree *tree,data d,otree_pos p) {
    p->label=d;
}

/*
Syfte: H�mta positionen f�r rotnoden
Parametrar: tr�det
Returv�rde: positionen f�r rotnoden
Kommentarer:
*/
otree_pos otree_root(otree *tree) {
    return tree->root;
}

/*
Syfte: S�tta in ett f�rsta barn f�r en nod.
Parametrar: tree - tr�det
            p - positionen f�r node
Returv�rde: positionen f�r den insatta noden
Kommentarer: Tidigare f�rsta nod kommer om en s�dan finns efter
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
Syfte: s�tta in ett syskon till efter den givna noden
Parametrar: tree - tr�det
            p - positionen f�r node
Returv�rde: positionen f�r den insatta noden
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
Syfte: Ta bort en nod ur tr�det
Parametrar: tree - tr�det
            p - positionen f�r noden
Returv�rde: position f�r f�r�ldranoden till noden som togs bort
Kommentarer: Om noden som ska tas bort har barn kommer �ven dessa tas bort
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
Syfte: H�mtar positionen f�r en nods f�rsta barn
Parametrar: tree - tr�det
            p - positionen f�r noden
Returv�rde: positionen f�r det f�rsta barnet eller NULL 
            om ett f�rsta barn ej finns
Kommentarer:
*/
otree_pos otree_firstChild(otree *tree,otree_pos p) {
    return p->firstChild;
}

/*
Syfte: H�ftar en nods n�sta syskon
Parametrar: tree - tr�det
            p - positionen f�r noden
Returv�rde: positionen f�r syskonet eller NULL om det inte finns fler syskon
Kommentarer:
*/
otree_pos otree_nextSibling(otree *tree,otree_pos p) {
    return p->nextSibling;
}

/*
Syfte: H�mta positionen f�r f�r�ldern
Parametrar: tree - tr�det
            n - positionen vars f�r�lder man vill h�mta
Returv�rde: positionen f�r f�r�ldern
Kommentarer: Ej definierad f�r rotnoden
*/
otree_pos otree_parent(otree *tree,otree_pos p) {
    return p->parent;
}

/*
Syfte: Kontrollera om en etikett finns i noden
Parametrar: tree - tr�det
            p - positionen f�r noden
Returv�rde: true om noden har en etikett annars false
Kommentarer:
*/
bool otree_hasLabel(otree *tree,otree_pos p) {
    return p->label!=NULL;
}

/*
Syfte: Avallokerar minnet som anv�nts av tr�det
Parametrar: tree - tr�det
Kommentarer: Tr�det �r ej l�ngre definierat efter anrop till denna
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
