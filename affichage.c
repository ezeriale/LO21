//
// Created by lucas on 14/12/2023.
//

#include "affichage.h"

void propositionAppartientAPremisse(char nom, bool valeur, Proposition* premisse) {
    // Cas de base : la prémisse est vide
    if (premisse == NULL) {
        printf("La prémisse est vide. La proposition n'appartient pas à la prémisse.\n");
        return;
    }

    // Cas de base : la proposition correspond à la proposition courante de la prémisse
    if (nom == premisse->nom && valeur == premisse->valeur) {
        printf("La proposition %c %s appartient a la premisse.\n", nom, valeur ? "Vrai" : "Faux");
        return;
    }

    // Appel récursif sur le reste de la prémisse
    propositionAppartientAPremisse(nom, valeur, premisse->suiv);
}

bool premisseEstVide(Regle* regle) {
    return regle->premisse == NULL;
}

// Fonction pour afficher une liste de propositions
void afficherListePropositions(Proposition* liste) {
    Proposition* courant = liste;
    while (courant != NULL) {
        printf("%c %s", courant->nom, courant->valeur ? "Vrai" : "Faux");
        courant = courant->suiv;
        if (courant != NULL) {
            printf(" ET ");
        }
    }
    printf("\n");
}

// Fonction pour afficher une règle
void afficherRegle(Regle* r) {
    if (r != NULL) {
        printf("Regle :\n");
        printf("  Premisse : ");
        afficherListePropositions(r->premisse);
        printf("  Conclusion : ");
        afficherListePropositions(r->conclusion);
        printf("\n");
    }
}