#include "liste-chainee.h"
#include <stdlib.h>
#include <stdio.h>

#define TODO NULL;

// retourne vrai si l est vide et faux sinon
bool estVide(Liste l) {
	if(l == NULL){
		return true;
	}
	return false;
}

// créer une liste d'un seul élément contenant la valeur v
Liste creer(Element v){
	Liste l = (Liste)malloc(sizeof(Cellule));
	l->val = v;
	l->suiv = NULL;
	return l;
}

// ajoute l'élément v en tete de la liste l
Liste ajoutTete(Element v, Liste l) {
	Liste new = creer(v);
	new->suiv = l;
	return new;
}


void afficheElement(Element e) {
	printf("%i ",e);
}

// affiche tous les éléments de la liste l
// Attention, cette fonction doit être indépendante du type des éléments de la liste
// utiliser une fonction annexe affiche_element
// Attention la liste peut être vide !
// version itérative
void afficheListe_i(Liste l) {
	while(l != NULL){
		afficheElement(l->val);
		l = l->suiv;
	}
}

// version recursive
void afficheListe_r(Liste l) {
	if(estVide(l)){
		printf("Liste vide\n");
	}
	else{
		afficheElement(l->val);
		afficheListe_r(l->suiv);
	}
}

void detruireElement(Element e) {
}

// Détruit tous les éléments de la liste l
// version itérative
void detruire_i(Liste l) {
	while(l != NULL){
		detruireElement(l->val);
		l = l->suiv;
	}
}

// version récursive
void detruire_r(Liste l) {
	if(l != NULL){
		detruireElement(l->val);
		detruire_r(l->suiv);
		free(l);
		
	}
}

// retourne la liste dans laquelle l'élément v a été ajouté en fin
// version itérative
Liste ajoutFin_i(Element v, Liste l) {
	Liste new = creer(v);
	while(l->suiv != NULL){
		l = l->suiv;
	}
	l->suiv = new;
	return l;
}

// version recursive
Liste ajoutFin_r(Element v, Liste l) {
	if(l->suiv == NULL){
		Liste new = creer(v);
		l->suiv = new;
		return l;
	}
	else {
		ajoutFin_r(v, l->suiv);
	}
}

// compare deux elements
bool equalsElement(Element e1, Element e2){
	return e1 == e2;
}

// Retourne un pointeur sur l'élément de la liste l contenant la valeur v ou NULL
// version itérative
Liste cherche_i(Element v,Liste l) {
	while(l!= NULL){
		if(equalsElement(v, l->val)){
			return l;
		}
		l = l->suiv;
	}
	return NULL;
}

// version récursive
Liste cherche_r(Element v,Liste l) {
	if(l != NULL){
		if(equalsElement(l->val, v)){
			return l;
		}
		return cherche_r(v, l->suiv);
		
	}
	return NULL;
}

// Retourne la liste modifiée dans la laquelle le premier élément ayant la valeur v a été supprimé
// ne fait rien si aucun élément possède cette valeur
// version itérative
Liste retirePremier_i(Element v, Liste l) {
	Liste tmp = l;
	Liste prev = NULL;
	while(tmp != NULL){
		if(equalsElement(v, tmp->val)){
			if(prev == NULL){
				l = l->suiv;
			}
			else{
				prev->suiv = tmp->suiv;
			}
			free(tmp);
			return l;
		}
		prev = tmp;
		tmp = tmp->suiv;
	}
	return l;
}


// version recursive
Liste retirePremier_r(Element v, Liste l) {
	if(l != NULL){
		if(equalsElement(v, l->val)){
			Liste tmp = l;
			l = l->suiv;
			free(tmp);
			return l;
		}
		l->suiv = retirePremier_r(v, l->suiv);
	}
	return l;
}


void afficheEnvers_r(Liste l) {
	if(l != NULL){
		afficheEnvers_r(l->suiv);
		afficheElement(l->val);
	}
}



