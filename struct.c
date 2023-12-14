//
// Created by lucas on 14/12/2023.
//
#include "struct.h"

void creerProposition(Proposition** nouvelleProposition, char nom, bool valeur) {
    *nouvelleProposition = (Proposition*)malloc(sizeof(Proposition));
    if (*nouvelleProposition != NULL) {
        (*nouvelleProposition)->nom = nom;
        (*nouvelleProposition)->valeur = valeur;
        (*nouvelleProposition)->suiv = NULL;
    }
}

// Fonction pour créer une nouvelle règle
Regle* creerRegleVide() {
    Regle* nouvelleRegle = (Regle*)malloc(sizeof(Regle));
    if (nouvelleRegle != NULL) {
        nouvelleRegle->premisse = NULL;
        nouvelleRegle->conclusion = NULL;
        nouvelleRegle->suiv = NULL;
        nouvelleRegle->verif = false;
    }
    return nouvelleRegle;
}

Regle* creerBCVide() {
    return NULL; // Une base de connaissances vide est représentée par un pointeur NULL
}

void ajouterPropositionAListe(Proposition** liste, char nom, bool valeur) {
    Proposition* nouvelleProposition;
    creerProposition(&nouvelleProposition, nom, valeur);

    if (nouvelleProposition != NULL) {
        nouvelleProposition->suiv = *liste;
        *liste = nouvelleProposition;
    }
}

// Fonction pour ajouter une règle à la base de connaissances
void ajouterRegleABase(Regle** base, Regle** nouvelleRegle) {
    (*nouvelleRegle)->suiv = *base;
    *base = *nouvelleRegle;
}

Proposition* teteDePremisse(Regle* regle) {
    return regle->premisse;
}

Proposition* conclusionDeRegle(Regle* regle) {
    return regle->conclusion;
}

Regle* premiereRegleDeBase(Regle* base) {
    return base;
}

void enleverRegleDeBase(Regle** base, Regle* regleAEnlever) {
    if (*base == NULL || regleAEnlever == NULL) {
        return;  // La base est déjà vide ou la règle à enlever est nulle, rien à faire
    }

    // Si la règle à enlever est en tête de la base
    if (*base == regleAEnlever) {
        *base = regleAEnlever->suiv;
        regleAEnlever->suiv = NULL;  // Détache la règle de la base
        return;
    }

    // Recherche de la règle précédant celle à enlever
    Regle* regleCourante = *base;
    while (regleCourante != NULL && regleCourante->suiv != regleAEnlever) {
        regleCourante = regleCourante->suiv;
    }

    // Si la règle à enlever n'a pas été trouvée dans la base
    if (regleCourante == NULL) {
        return;  // Rien à faire
    }

    // Met à jour les liens pour sauter la règle à enlever
    regleCourante->suiv = regleAEnlever->suiv;
    regleAEnlever->suiv = NULL;  // Détache la règle de la base
}

// Fonction pour ajouter les propositions de la conclusion à la liste de faits connus
void ajouterConclusionAuFait(Proposition* conclusion, Proposition** faits_connus) {
    // Trouver la fin de la liste des faits connus
    Proposition* fin_liste = *faits_connus;
    while (fin_liste != NULL && fin_liste->suiv != NULL) {
        fin_liste = fin_liste->suiv;
    }

    Proposition* conclusion_courante = conclusion;

    while (conclusion_courante != NULL) {
        Proposition* nouvelleProposition;
        creerProposition(&nouvelleProposition, conclusion_courante->nom, conclusion_courante->valeur);

        if (nouvelleProposition != NULL) {
            if (fin_liste != NULL) {
                fin_liste->suiv = nouvelleProposition;
            } else {
                *faits_connus = nouvelleProposition;
            }

            fin_liste = nouvelleProposition;
        }

        conclusion_courante = conclusion_courante->suiv;
    }
}

// Fonction pour libérer la mémoire d'une liste de propositions
void libererListePropositions(Proposition** liste) {
    Proposition* courant = *liste;
    while (courant != NULL) {
        Proposition* suivant = courant->suiv;
        free(courant);
        courant = suivant;
    }
    *liste = NULL; // La liste est vide après libération
}

// Fonction pour libérer la mémoire d'une règle
void libererRegle(Regle** r) {
    if (*r != NULL) {
        libererListePropositions(&((*r)->premisse));
        libererListePropositions(&((*r)->conclusion));
        free(*r);
        *r = NULL;
    }
}

// Fonction pour libérer la mémoire de la base de connaissances
void libererBC(Regle** base) {
    Regle* courant = *base;
    while (courant != NULL) {
        Regle* suivant = courant->suiv;
        libererRegle(&courant);
        courant = suivant;
    }
    *base = NULL; // La base de connaissances est vide après libération
}