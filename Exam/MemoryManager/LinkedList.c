#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define TODO NULL;

// retourne vrai si l est vide et faux sinon
bool estVide(Liste l) {
	return l == NULL;
}

// créer une liste d'un seul élément contenant la valeur v
Liste creer(Element v){
	Liste liste = malloc(sizeof(Cellule));
	liste->val= malloc(sizeof(Element));
    liste->val=v;
	liste->suiv=NULL;
	return liste;
}

// ajoute l'élément v en tete de la liste l
Liste ajoutTete(Element v, Liste l) {
    Liste nouvelleCellule = creer(v);
    nouvelleCellule->suiv = l;
    return nouvelleCellule;
}

extern void afficheElement(Element e) {      //affiche un element de type void*

}

// affiche tous les éléments de la liste l
// Attention, cette fonction doit être indépendante du type des éléments de la liste
// utiliser une fonction annexe affiche_element
// Attention la liste peut être vide !
// version itérative
void afficheListe_i(Liste l) {
	printf("[ ");
	while(l != NULL){
		afficheElement(l->val);
		l = l->suiv;
	}printf(" ]");
}

// version recursive
void afficheListe_r(Liste l) {
	if (l != NULL) {
		afficheElement(l->val);
		afficheListe_r(l->suiv);
	}
}

extern void detruireElement(Element e) {
}

// Détruit tous les éléments de la liste l
// version itérative
void detruire_i(Liste l) {
    Liste tmp;
    while (l != NULL) {
        tmp = l;
        l = l->suiv;
        detruireElement(tmp->val);
        free(tmp);
		tmp=NULL;
    }
}

// version récursive
void detruire_r(Liste l) {
    if (l != NULL) {
        detruire_r(l->suiv);
        detruireElement(l->val);
        free(l);
    }
}

// retourne la liste dans laquelle l'élément v a été ajouté en fin
// version itérative
Liste ajoutFin_i(Element v, Liste l) {
	if (l == NULL) {
		return creer(v);
	}
	Liste tmp = l;
	while (tmp->suiv != NULL) {
		tmp = tmp->suiv;
	}
	tmp->suiv = creer(v);
	return l;
}

// version recursive
Liste ajoutFin_r(Element v, Liste l) {
    if (l == NULL) {
        return creer(v);
    }
    l->suiv = ajoutFin_r(v, l->suiv);
    return l;
}

// compare deux elements
extern bool equalsElement(Element e1, Element e2){

}

// Retourne un pointeur sur l'élément de la liste l contenant la valeur v ou NULL
// version itérative
Liste cherche_i(Element v,Liste l) {
	while (l!=NULL){
		if(equalsElement(l->val , v)){
			return l;
		}else{
			l=l->suiv;
		}
	};
	return l;
}

// version récursive
Liste cherche_r(Element v, Liste l) {
    if (l != NULL) {
        if (equalsElement(l->val , v)) {
            return l;
        } else {
            return cherche_r(v, l->suiv);
        }
    }
    return NULL;  
}

// Retourne la liste modifiée dans la laquelle le premier élément ayant la valeur v a été supprimé
// ne fait rien si aucun élément possède cette valeur
// version itérative
Liste retirePremier_i(Element v, Liste l) {
    if (l == NULL) return l;

    Liste prev = NULL;
    Liste curr = l;

    while (curr != NULL) {
        if (equalsElement(curr->val, v)) {
            if (prev == NULL) {
                l = curr->suiv;  
            } else {
                prev->suiv = curr->suiv; 
            }
            detruireElement(curr->val);
            free(curr);
            return l;
        }
        prev = curr;
        curr = curr->suiv;
    }

    return l;
}


Liste retirePremier_r(Element v, Liste l) {
    if (l == NULL) return l;

    if (equalsElement(l->val, v)) {
        Liste tmp = l->suiv;
        detruireElement(l->val);
        free(l);
        return tmp;
    }

    l->suiv = retirePremier_r(v, l->suiv);
    return l;
}


void afficheEnvers_r(Liste l) {
    if (l == NULL) return;
    afficheEnvers_r(l->suiv);
    afficheElement(l->val);
    printf(" ");
}


