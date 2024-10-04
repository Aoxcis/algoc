/**
 Compilation
 gcc --std=c99 -W -Wall -o prixTuring prixTuring.c

 Exécution
 ./prixTuring

 Tests
 diff out.csv turingWinners.csv

**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MAIN
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct {
		int annee;
		char *nom;
		char *description;
	} Gagnant;

int numberOfWinners(FILE *fichier){
	int counter = 0;
	char buffer[2000];
	
	while(fgets(buffer, sizeof(buffer), fichier) != NULL){
		counter++;
	}
	return counter;
}

char* readLine(FILE *fichier, int line){
	rewind(fichier);
	char buffer[2000];
	for(int i = 0; i < line; i++){
		fgets(buffer, sizeof(buffer), fichier);
		if(i == line){
			break;
		}
	}
	return buffer;
}

void readWinners(FILE *fichier, Gagnant *gagnantTab){
	rewind(fichier);
	int nbligne = numberOfWinners(fichier);

	for(int i = 0; i < nbligne; i++){
		char *ligne = readLine(fichier, i+1);
		char *token = strtok(ligne, ";");
		if(token != NULL){
			gagnantTab[i].annee = atoi(token);
		}

		token = strtok(NULL, ";");
		if(token != NULL){
			gagnantTab[i].nom = malloc(strlen(token) + 1);
			strcpy(gagnantTab[i].nom, token);
		}

		token = strtok(NULL, ";");
		if(token != NULL){
			gagnantTab[i].description = malloc(strlen(token) + 1);
			strcpy(gagnantTab[i].description, token);
		}
	}
}

int compareByYear(const void *a, const void *b) {
    Gagnant *gagnantA = (Gagnant *)a;
    Gagnant *gagnantB = (Gagnant *)b;
    return gagnantA->annee - gagnantB->annee;
}

void sortTuringWinnersByYear(Gagnant *gagnantTab, int count) {
    qsort(gagnantTab, count, sizeof(Gagnant), compareByYear);
}

void printWinners(Gagnant *gagnantTab, FILE *Result, int nb){
	for(int i = 0; i < nb; i++){
		fprintf(Result, "%d;%s;%s", gagnantTab[i].annee, gagnantTab[i].nom, gagnantTab[i].description);
	}
}

void infosAnnee(FILE *fichier, Gagnant *gagnantTab ,int annee){
	rewind(fichier);
	printf("testinfos annee test test\n");
	int nb = numberOfWinners(fichier);
	for(int i = 0; i < nb; i++){
		char *ligne = readLine(fichier, i+1);
		char *token = strtok(ligne, ";");
		if(token != NULL){
			if(atoi(token) == annee){
				printf("Annee : %d\n", atoi(token));
				printf("Nom : %s\n", gagnantTab[i].nom);
				printf("Description : %s\n", gagnantTab[i].description);
			}
		}
	}
}


int main(int argc, char* argv[])
{
	char *inputFilename = NULL;
    char *outputFilename = "out.csv";  // Fichier de sortie par défaut
    FILE *fichierIn, *fichierOut;
	int afficheAnnee = 0;
	int annee = 0;
	int sort = 0;

    // Parcours des arguments de la ligne de commande
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 && (i + 1) < argc) {
            outputFilename = argv[++i];
			
        } 

		if(strcmp(argv[i], "--sort") == 0 && (i + 1) < argc){
			sort = 1;
		}

		if (strcmp(argv[i], "--info") == 0 && (i + 1) < argc) {
			afficheAnnee = 1;
			annee = atoi(argv[++i]);
			
		}

		else {
            inputFilename = argv[i];
			
        }
    }

    // Vérifier que le fichier d'entrée a été spécifié
    if (inputFilename == NULL) {
        fprintf(stderr, "Erreur: aucun fichier d'entrée spécifié.\n");
        return EXIT_FAILURE;
    }

    // Ouvrir le fichier d'entrée
    fichierIn = fopen(inputFilename, "r");
    if (fichierIn == NULL) {
        fprintf(stderr, "Erreur: impossible d'ouvrir le fichier %s\n", inputFilename);
        return EXIT_FAILURE;
    }

    // Ouvrir le fichier de sortie
    fichierOut = fopen(outputFilename, "w");
    if (fichierOut == NULL) {
        fprintf(stderr, "Erreur: impossible de créer le fichier %s\n", outputFilename);
        fclose(fichierIn);
        return EXIT_FAILURE;
    }

	int nb = numberOfWinners(fichierIn);
	Gagnant *gagnantTab = malloc(sizeof(Gagnant) * nb);

	
	readWinners(fichierIn, gagnantTab);
	
	if(afficheAnnee == 1){
		infosAnnee(fichierIn, gagnantTab, annee);
	}
	
	if(sort == 1){
		sortTuringWinnersByYear(gagnantTab, nb);
	}

	printWinners(gagnantTab, fichierOut, nb);
	
	for(int i = 0; i < nb; i++){
		free(gagnantTab[i].nom);
		free(gagnantTab[i].description);
	}

	fclose(fichierIn);
	fclose(fichierOut);
	
	return EXIT_SUCCESS;
}

