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

struct gagnants {
		int annee;
		char nom[40];
		char description[200];
	};

int numberOfWinners(FILE *fichier){
	int counter = 0;
	char *buffer[1024];
	while(fgets(buffer, sizeof(buffer), fichier) != NULL){
		counter++;
	}
	return counter;
}

char* readLine(FILE *fichier){
	char *buffer[100];
	fgets(buffer, sizeof(buffer), fichier);
	return buffer;
}

char* readPartLine(FILE *fichier){
	char *line = readLine(fichier);
	char *buffer[50];
	int current = 0;
	while(fgetc(line) != ';' || fgetc(line) != EOF){
		buffer[current] = fgetc(line);
	}
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
	fclose(fichier);
	return EXIT_SUCCESS;
}

