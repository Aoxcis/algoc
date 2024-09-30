#include "linkedListOfMusic.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define TODO NULL;
void ReadMusic(FILE* f, Element tabMusic, int numMusic) {
    char buffer[1000];
    int i = 0;
    rewind(f);

    while (fgets(buffer, sizeof(buffer), f) != NULL && i < numMusic) {
        char* token = strtok(buffer, ";");
        if (token != NULL) {
            tabMusic[i].name = malloc(strlen(token) + 1);  // +1 pour \0
            strcpy(tabMusic[i].name, token);
        }
        token = strtok(NULL, ";");
        if (token != NULL) {
            tabMusic[i].artist = malloc(strlen(token) + 1);  // +1 pour \0
            strcpy(tabMusic[i].artist, token);
        }
        token = strtok(NULL, ";");
        if (token != NULL) {
            tabMusic[i].album = malloc(strlen(token) + 1);  // +1 pour \0
            strcpy(tabMusic[i].album, token);
        }
        token = strtok(NULL, ";");
        if (token != NULL) {
            tabMusic[i].genre = malloc(strlen(token) + 1);  // +1 pour \0
            strcpy(tabMusic[i].genre, token);
        }
        token = strtok(NULL, ";");
        if (token != NULL) {
            tabMusic[i].discNumber = atoi(token);
        }
        token = strtok(NULL, ";");
        if (token != NULL) {
            tabMusic[i].trackNumber = atoi(token);
        }
        token = strtok(NULL, ";");
        if (token != NULL) {
            tabMusic[i].year = atoi(token);
        }
        i++;
    }
}
void PrintMusic(FILE* output, Element musique){
    fprintf(output,"%s;%s;%s;%s;%d;%d;%d",musique->name,musique->artist,musique->album,musique->genre,musique->discNumber,musique->trackNumber,musique->year);
}

void PrintMusics(FILE* output, Liste l){
    while(l != NULL){
        PrintMusic(output, l->val);
        l = l->suiv;
    }
}
// retourne vrai si l est vide et faux sinon
bool estVide(Liste l) {
	return l == NULL;
}

// créer une liste d'un seul élément contenant la valeur v
Liste creer(Element v){
	Liste liste = malloc(sizeof(Cellule));
    liste->val = v;
	liste->suiv=NULL;
	return liste;
}

// ajoute l'élément v en tete de la liste l
Liste ajoutTete(Element v, Liste l) {
    Liste nouvelleCellule = creer(v);
    nouvelleCellule->suiv = l;
    return nouvelleCellule;
}

void afficheElement(Element e) {      //affiche un element de type void*
    return 0;  // a faire
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

void detruireElement(Element e) {
    free(e->artist);
    free(e->name);
    free(e->album);
    free(e->genre);
    free(e);
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
bool equalsElement(Element e1, Element e2){
    return ((strcmp(e1->artist, e2->artist) == 0) &&
            (strcmp(e1->name, e2->name) == 0) &&
            (strcmp(e1->album, e2->album) == 0) &&
            (strcmp(e1->genre, e2->genre) == 0) &&
            (e1->discNumber == e2->discNumber) &&
            (e1->trackNumber == e2->trackNumber) &&
            (e1->year == e2->year));
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


