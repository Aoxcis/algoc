#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dates.c"
#include "dates.h"



int main(void){
    Date d;
    initialiseDate(&d);
    afficheDate(&d);
}