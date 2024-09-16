#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dates.h"

enum Mois {
    Janvier,
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
    int Annee;
    enum Mois Mois;
    int Jour;
};

void initialiseDate(struct Date* adresse){
    struct Date* date = (struct Date*) adresse;
    scanf("entrer le jour%d", &date->Jour);
    scanf("entrer le mois%d", &date->Mois);
    scanf("entrer l'annee%d", &date->Annee);
}

void afficheDate(struct Date* adresse){
    printf("Date enregistrée %d/%d/%d\n", Date->jour, Date->Mois, Date->Mois);
}
