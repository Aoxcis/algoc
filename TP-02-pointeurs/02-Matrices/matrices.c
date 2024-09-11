#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 5


void matrix_mult(int64_t matriceR[SIZE][SIZE], int64_t matriceA[SIZE][SIZE],int64_t matriceB[SIZE][SIZE]){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            matriceR[i][j]=0;
            for(int k=0; k<SIZE; k++){
                matriceR[i][j]+=matriceA[i][k]*matriceB[k][j];
            }
        }
    }
}

void matrix_print(int64_t matrice[SIZE][SIZE]){
    for(int i=0; i<SIZE; i++){
        printf("\n");
        for(int j=0; j<SIZE; j++){
            printf("%lld ",matrice[i][j]);
        }
        printf("\n");
    }
}