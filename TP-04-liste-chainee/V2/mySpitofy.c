#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "linkedListOfMusic.h"

int main(int argc, char *argv[]) {
//=================================================
    // FILE *f = fopen(argv[1], "r");                        décommenter pour pouvoir entrer le nom du fichier input lors de l'exection du .out
//=================================================

    FILE *f = fopen("music.csv","r");
    
    if (f == NULL) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }
    
    int numMusic = 2703;

    Liste l = malloc(numMusic * sizeof(Music));
    if (l == NULL) {
        perror("Erreur d'allocation mémoire");
        fclose(f);
        return 1;
    }
    ReadMusic(f, l, numMusic);
    FILE *copie = fopen("copieMusic.csv","w");
    PrintMusics(copie, l);

    // fclose(copie);
    // while (l != NULL) {
    //     Liste tmp = l;
    //     l = l->suiv;
    //     detruireElement(tmp->val);
    //     free(tmp);
    // }

    return EXIT_SUCCESS;
}