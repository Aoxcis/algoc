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

void readWinners(FILE *fichier){
	rewind(fichier);
	int nbligne = numberOfWinners(fichier);
	Gagnant gagnantTab[nbligne];

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

	for(int i = 0; i < nbligne; i++){
		printf("Annee : %d\n", gagnantTab[i].annee);
		printf("Nom : %s\n", gagnantTab[i].nom);
		printf("Description : %s\n", gagnantTab[i].description);
	}

	for(int i = 0; i < nbligne; i++){
		free(gagnantTab[i].nom);
		free(gagnantTab[i].description);
	}
}


int main(void)
{
	char filename[] = "turingWinners.csv";
	char outputFilename[] = "out.csv";

	FILE *fichier = fopen(filename, "r");
	if (fichier == NULL) {
		fprintf(stderr, "Erreur: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	else{
		printf("Fichier ouvert avec succes\n");
	}
	int nb;
	nb = numberOfWinners(fichier);
	printf("Number of winners : %d\n", nb);

	readWinners(fichier);
	fclose(fichier);
	return EXIT_SUCCESS;
}

