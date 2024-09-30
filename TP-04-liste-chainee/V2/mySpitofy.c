#include "LinkedListOfMusic.h"
#include "LinkedListOfMusic.c"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(void){
    FILE *fichier = fopen("music.csv", "r");
    if(fichier == NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        return 0;
    }

    int nbMusic = numLine(fichier);
    Music *tabMusic = malloc(nbMusic * sizeof(Music));
    readMusic(fichier, tabMusic, nbMusic);

    Liste l = NULL;
    for(int i = 0; i < nbMusic; i++){
        l = ajoutFin_i(tabMusic, l);
    }

    afficheListe_i(l);

    detruire_i(l);
    free(tabMusic);
    fclose(fichier);
    return 0;
}