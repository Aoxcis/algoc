#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

enum Mois {
    Janvier = 1,
    Fevrier,
    Mars,
    Avril,
    Mai,
    Juin,
    Juillet,
    Aout,
    Septembre,
    Octobre,
    Novembre,
    Decembre
};

struct Date{
    int annee;
    enum Mois mois;
    int jour;
};

typedef struct Date Date;

void initialiseDate(Date *date);
void afficheDate(Date *date);

