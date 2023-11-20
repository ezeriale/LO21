#include <stdio.h>
#include <stdlib.h>

// Définition du type abstrait de données Regle
typedef struct NoeudProposition {
    char nom;
    int valeur;
    struct NoeudProposition* suivant;
} NoeudProposition;

typedef struct {
    NoeudProposition* prémisse;
    char conclusionNom;
    int conclusionValeur;
} Regle;

// Définition du type abstrait de données BC (Base de Connaissances)
typedef struct NoeudRegle {
    Regle regle;
    struct NoeudRegle* suivant;
} NoeudRegle;

typedef struct {
    NoeudRegle* tete;
} BC;

// Fonctions pour le type abstrait Regle
Regle creerRegle() {
    Regle nouvelleRegle;
    nouvelleRegle.prémisse = NULL;
    return nouvelleRegle;
}

void ajouterProposition(NoeudProposition** prémisse, char nom, int valeur) {
    NoeudProposition* nouveauNoeud = (NoeudProposition*)malloc(sizeof(NoeudProposition));
    nouveauNoeud->nom = nom;
    nouveauNoeud->valeur = valeur;
    nouveauNoeud->suivant = NULL;

    if (*prémisse == NULL) {
        *prémisse = nouveauNoeud;
    } else {
        NoeudProposition* actuel = *prémisse;
        while (actuel->suivant != NULL) {
            actuel = actuel->suivant;
        }
        actuel->suivant = nouveauNoeud;
    }
}

void creerConclusion(Regle* regle, char nom, int valeur) {
    regle->conclusionNom = nom;
    regle->conclusionValeur = valeur;
}

int propositionDansPremisse(NoeudProposition* prémisse, char nom) {
    if (prémisse == NULL) {
        return 0;
    }

    if (prémisse->nom == nom) {
        return 1;
    }

    return propositionDansPremisse(prémisse->suivant, nom);
}

void supprimerProposition(NoeudProposition** prémisse, char nom) {
    if (*prémisse == NULL) {
        return;
    }

    if ((*prémisse)->nom == nom) {
        NoeudProposition* temp = *prémisse;
        *prémisse = (*prémisse)->suivant;
        free(temp);
        return;
    }

    supprimerProposition(&((*prémisse)->suivant), nom);
}

int premissesVide(NoeudProposition* prémisse) {
    return prémisse == NULL;
}

char tetePremisse(NoeudProposition* prémisse) {
    if (prémisse != NULL) {
        return prémisse->nom;
    }
    return '\0';
}

char conclusionNom(Regle regle) {
    return regle.conclusionNom;
}

int conclusionValeur(Regle regle) {
    return regle.conclusionValeur;
}

// Fonctions pour le type abstrait BC
BC creerBC() {
    BC nouvelleBC;
    nouvelleBC.tete = NULL;
    return nouvelleBC;
}

void ajouterRegle(BC* baseConnaissances, Regle regle) {
    NoeudRegle* nouveauNoeud = (NoeudRegle*)malloc(sizeof(NoeudRegle));
    nouveauNoeud->regle = regle;
    nouveauNoeud->suivant = NULL;

    if (baseConnaissances->tete == NULL) {
        baseConnaissances->tete = nouveauNoeud;
    } else {
        NoeudRegle* actuel = baseConnaissances->tete;
        while (actuel->suivant != NULL) {
            actuel = actuel->suivant;
        }
        actuel->suivant = nouveauNoeud;
    }
}

Regle teteBC(BC baseConnaissances) {
    return baseConnaissances.tete->regle;
}

// Fonctions pour le moteur d'inférence
void appliquerRegle(BC baseConnaissances, NoeudProposition* faits, Regle regle, NoeudProposition** nouveauxFaits) {
    NoeudProposition* actuel = regle.prémisse;
    while (actuel != NULL) {
        if (!propositionDansPremisse(faits, actuel->nom)) {
            return; // La prémisse n'est pas satisfaite
        }
        actuel = actuel->suivant;
    }

    // Si on arrive ici, toutes les propositions de la prémisse sont dans les faits
    ajouterProposition(nouveauxFaits, regle.conclusionNom, regle.conclusionValeur);
}

void moteurInference(BC baseConnaissances, NoeudProposition* faits, NoeudProposition** nouveauxFaits) {
    NoeudRegle* actuel = baseConnaissances.tete;
    while (actuel != NULL) {
        appliquerRegle(baseConnaissances, faits, actuel->regle, nouveauxFaits);
        actuel = actuel->suivant;
    }
}

// Fonctions utilitaires pour afficher les propositions et les faits
void afficherPropositions(NoeudProposition* propositions) {
    while (propositions != NULL) {
        printf("%c%d ", propositions->nom, propositions->valeur);
        propositions = propositions->suivant;
    }
    printf("\n");
}

int main() {
    // Création de règles et de la base de connaissances
    Regle regle1 = creerRegle();
    ajouterProposition(&(regle1.prémisse), 'A', 1);
    ajouterProposition(&(regle1.prémisse), 'B', 0);
    creerConclusion(&regle1, 'D', 1);

    Regle regle2 = creerRegle();
    ajouterProposition(&(regle2.prémisse), 'D', 1);
    ajouterProposition(&(regle2.prémisse), 'B', 0);
    creerConclusion(&regle2, 'E', 0);

    Regle regleC1 = creerRegle();
    ajouterProposition(&(regleC1.prémisse), 'D', 1);
    creerConclusion(&regleC1, 'F', 1);

    BC baseConnaissances = creerBC();
    ajouterRegle(&baseConnaissances, regle1);
    ajouterRegle(&baseConnaissances, regle2);
    ajouterRegle(&baseConnaissances, regleC1);

    // Affichage de la base de connaissances
    printf("Base de connaissances :\n");
    NoeudRegle* actuelBC = baseConnaissances.tete;
    while (actuelBC != NULL) {
        printf("Si ");
        afficherPropositions(actuelBC->regle.prémisse);
        printf("Alors %c%d\n", actuelBC->regle.conclusionNom, actuelBC->regle.conclusionValeur);
        actuelBC = actuelBC->suivant;
    }

    // Ajout de faits initiaux
    NoeudProposition* faits = NULL;
    ajouterProposition(&faits, 'A', 1);
    ajouterProposition(&faits, 'B', 0);

    // Affichage des faits initiaux
    printf("\nFaits initiaux : ");
    afficherPropositions(faits);

    // Application du moteur d'inférence
    NoeudProposition* nouveauxFaits = NULL;
    moteurInference(baseConnaissances, faits, &nouveauxFaits);

    // Affichage des nouveaux faits déduits
    printf("\nNouveaux faits déduits : ");
    afficherPropositions(nouveauxFaits);

    // Libération de la mémoire
    free(faits);
    free(nouveauxFaits);

    return 0;
}