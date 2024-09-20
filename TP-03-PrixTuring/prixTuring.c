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

void printWinners(Gagnant *gagnantTab, FILE *Result, int nb){
	for(int i = 0; i < nb; i++){
		fprintf(Result, "%d;%s;%s", gagnantTab[i].annee, gagnantTab[i].nom, gagnantTab[i].description);
	}
}


int main(int argc, char** argv)
{
	char filename[] = "turingWinners.csv";
	char outputFilename[] = "out.csv";

	FILE *fichier = fopen(filename, "r");
	FILE *output = fopen(outputFilename, "w");

	int nb = numberOfWinners(fichier);
	Gagnant *gagnantTab = malloc(sizeof(Gagnant) * nb);

	readWinners(fichier, gagnantTab);
	printWinners(gagnantTab, output, nb);
	
	for(int i = 0; i < nb; i++){
		free(gagnantTab[i].nom);
		free(gagnantTab[i].description);
	}
	free(gagnantTab);
	fclose(fichier);
	fclose(output);
	
	return EXIT_SUCCESS;
}

