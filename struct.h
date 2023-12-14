//
// Created by lucas on 14/12/2023.
//

#ifndef LO21_STRUCT_H
#define LO21_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Structure pour une proposition
typedef struct Proposition {
    char nom;
    bool valeur;
    struct Proposition* suiv;
} Proposition;

// Structure pour une règle
typedef struct Regle {
    Proposition* premisse;
    Proposition* conclusion;
    struct Regle* suiv;
    bool verif;
} Regle;

void creerProposition(Proposition** nouvelleProposition, char nom, bool valeur);
Regle* creerRegleVide();
Regle* creerBCVide();
void ajouterPropositionAListe(Proposition** liste, char nom, bool valeur);
void ajouterRegleABase(Regle** base, Regle** nouvelleRegle);
Proposition* teteDePremisse(Regle* regle);
Proposition* conclusionDeRegle(Regle* regle);
Regle* premiereRegleDeBase(Regle* base);
void enleverRegleDeBase(Regle** base, Regle* regleAEnlever);
void libererListePropositions(Proposition** liste);
void libererRegle(Regle** r);void libererBC(Regle** base);






#endif //LO21_STRUCT_H
