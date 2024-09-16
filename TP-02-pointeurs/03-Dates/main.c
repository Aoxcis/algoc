#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dates.c"
#include "dates.h"



int main(void){
    Date d;
    initialiseDate(&d);
    afficheDate(&d);
    int nbDates;
    printf("Entrer le nombre de dates : ");
    //scanf("%i", &nbDates);
    Date *pd;
    pd = newDate();
    afficheDate(pd);
    free(pd);
    pd = NULL;
}