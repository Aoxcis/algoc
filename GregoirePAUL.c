// Grégoire PAUL

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int taille = 3;

int taillet1(int* pt1){
    int sommet1 = 0;
    for(int i = 0; i<taille; i++){
        sommet1 += pt1[i];
    }
    return sommet1;
}

int* repeat(int *pt1, int *pt2){
    int current = 0;
    int sommet1 = taillet1(pt1);
    int *nvtab = (int*)malloc(sommet1 * sizeof(int));

    for(int i = 0; i<taille; i++){
        for(int j = 0; j < pt1[i]; j++){
            nvtab[current] = pt2[i];
            current++;
        } 
    }
    printf("Nouveau tableau: ");
    for(int i = 0; i < sommet1; i++){
        printf("%d ", nvtab[i]);
    }
    return nvtab;
}


int main(void){
    int t1[3] = {1,2,3};
    int t2[3] = {1,2,3};
    int sommet1 = taillet1(t1);
    int *pnvt = repeat(t1,t2);
    
    free(pnvt);
    pnvt = NULL;
    return 0;
}