// Compilation
// gcc -g --std=c99 -W -Wall memoryManager.c

// Exécution
// ./a.out

// Détection de fuites mémoires
// valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --show-reachable=no ./a.out

#include "linkedList.h"
#include "linkedList.c"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// définir le type Bloc
// (facultatif) définir le type BlocList

typedef struct Bloc {
	int address;
	int size;
} Bloc;

typedef struct BlocList {
	Bloc *bloc;
	struct BlocList *next;
} BlocList;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 2
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// définir le type MemoryManager

typedef struct MemoryManager {
	BlocList *allocatedList;
	BlocList *freeList;
} MemoryManager;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 3
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// createMemoryManager(startAddress,maxSize)

MemoryManager createMemoryManager(int startAddress, int maxSize) {
	MemoryManager memoryManager;
	memoryManager.allocatedList = NULL;
	Bloc *bloc = malloc(sizeof(Bloc));
	bloc->address = startAddress;
	bloc->size = maxSize;
	memoryManager.freeList = creer(bloc);
	return memoryManager;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 4
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// myalloc(MemoryManager, size)
Bloc* myalloc(MemoryManager memoryManager, int size){
	Bloc *bloc = malloc(sizeof(Bloc));
	bloc->size = size;
	BlocList *current = memoryManager.freeList;
	while(current != NULL){
		if(current->bloc->size >= size){
			bloc->address = current->bloc->address;
			current->bloc->address += size;
			current->bloc->size -= size;
			memoryManager.allocatedList = ajoutTete(bloc, memoryManager.allocatedList);
			return bloc;
		}
		current = current->next;
	}
	return NULL;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 5
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// myfree(MemoryManager, address)

Bloc* myfree(MemoryManager memoryManager, int address){
	BlocList *current = memoryManager.allocatedList;
	Bloc *bloc = NULL;
	while(current != NULL){
		if(current->bloc->address == address){
			bloc = current->bloc;
			memoryManager.allocatedList = retirePremier_r(bloc, memoryManager.allocatedList);
			memoryManager.freeList = ajoutTete(bloc, memoryManager.freeList); // ne renvoie pas bien le nouveau freeList
			return bloc;
		}
		current = current->next;
	}
	return NULL;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 6
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void simpleMain() {
	MemoryManager memoryManager = createMemoryManager(0,100);
	printf("size freelist pre tout: %d\n", memoryManager.freeList->bloc->size);
	printf("adresse free list : %d\n", memoryManager.freeList->bloc->address);
	myalloc(memoryManager, 8);
	myalloc(memoryManager, 15);
	myalloc(memoryManager, 5);
	printf("size freelist : %d\n", memoryManager.freeList->bloc->size);
	printf("adresse free list : %d\n", memoryManager.freeList->bloc->address);
	myfree(memoryManager, 8);
	printf("size freelist post free : %d\n", memoryManager.freeList->bloc->size);
	printf("adresse free list : %d\n", memoryManager.freeList->bloc->address);

	free(memoryManager.allocatedList);
	free(memoryManager.freeList);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 7
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

int numberOfLines(FILE *fichier){
	int counter = 0;
	char buffer[2000];
	while(fgets(buffer, sizeof(buffer), fichier) != NULL){
		counter++;
	}
	return counter;
}

void readFromFile(FILE *file) {
	int startAddress, sizeFree, size, line= numberOfLines(file);
	printf("<fichier memorySimulation-small.txt>              <Resultat>\n");	
	char *ligne = readLine(file, 1);

	char *token = strtok(ligne, " ");
		if(token != NULL){
			startAddress = atoi(token);
		}

	token = strtok(NULL, " ");
		if(token != NULL){
			sizeFree = atoi(token);
		}
	printf("%d %d						0\n", startAddress, sizeFree);
	MemoryManager memoryManager = createMemoryManager(startAddress, sizeFree);

	for(int i = 2; i < line+1; i++){
		char *ligne = readLine(file, i);
		char *token = strtok(ligne, " ");
		if(token != NULL){
			if(strcmp(token, "MYALLOC") == 0){
				token = strtok(NULL, " ");
				if(token != NULL){
					size = atoi(token);
				}
				myalloc(memoryManager, size);
				printf("MYALLOC %d					%d\n", size, memoryManager.freeList->bloc->address); // ne fonctionne pas avec allocatedList
			}
			if(strcmp(token, "MYFREE") == 0){
				token = strtok(NULL, " ");
				if(token != NULL){
					size = atoi(token);
				}
				myfree(memoryManager, size);
				printf("MYFREE %d					%d\n", size, memoryManager.freeList->bloc->address);
			}
		}
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 8
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// defragmentation(memoryManager)

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MAIN
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char *argv[]) {

	// 6
	//simpleMain();

	// 7

	FILE *file = fopen("memorySimulation-small.txt", "r");
	readFromFile(file);

	return 0;
}
