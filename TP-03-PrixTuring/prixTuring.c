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

char* readLine(FILE *fichier){
	rewind(fichier);
	char buffer[2000];
	fgets(buffer, sizeof(buffer), fichier);
	return buffer;
}

char* readPartLine(FILE *fichier){
	char *line = readLine(fichier);
	printf("ligne entiere : %s\n", line);
	int buffer1[50];
	char buffer2[50];
	char buffer3[50];
	int current = 0;
	int partie = 0;
	for(int i = 0; fgetc(fichier) == '\0'; i++){
		if(fgetc(fichier) == ';' || fgetc(fichier) == '\0'){
			current = 0;
			partie++;
		}
		else {
			if(partie == 0 && current < 49) {
				buffer1[current] = fgetc(fichier);
				buffer1[current + 1] = '\0';
			}
			if(partie == 1 && current < 49) {
				buffer2[current] = fgetc(fichier);
				buffer2[current + 1] = '\0';
			}
			if(partie == 2 && current < 49) {
				buffer3[current] = fgetc(fichier);
				buffer3[current + 1] = '\0';
			}
			current++;
		}
		if(partie >2){
			break;
		} 
	}
	return buffer1;
}


int main(int argc, char** argv)
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

	char *prem;
	prem = readLine(fichier);
	printf("ligne entiere : %s", prem);
	prem = NULL;
	fclose(fichier);
	return EXIT_SUCCESS;
}

