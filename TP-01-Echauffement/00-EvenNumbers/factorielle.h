#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned long long TypeEntier;

TypeEntier factorielle(TypeEntier nb){
    TypeEntier temp = 1;
    for(TypeEntier i = nb; i >0; i--){
        temp = temp*i;
    }
    printf("%llu\n", temp);
    return temp;
}

