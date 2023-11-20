#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure pour une proposition
typedef struct proposition {
    char id;
    bool valeur;
    struct proposition* suiv;
} proposition;

// Structure pour une règle
typedef struct regle {
    proposition* premisse;
    proposition* conclusion;
    struct regle* suiv;
} regle;

// Structure pour la base de connaissances
typedef struct {
    regle* regles;
} BC;

// Fonction pour créer une nouvelle proposition
proposition* creerProposition(char id, bool valeur) {
    proposition* nouvelleProposition = (proposition*)malloc(sizeof(proposition));
    if (nouvelleProposition != NULL) {
        nouvelleProposition->id = id;
        nouvelleProposition->valeur = valeur;
        nouvelleProposition->suiv = NULL;
    }
    return nouvelleProposition;
}

// Fonction pour créer une nouvelle règle
regle* creerRegle(proposition* premisse, proposition* conclusion) {
    regle* nouvelleRegle = (regle*)malloc(sizeof(regle));
    if (nouvelleRegle != NULL) {
        nouvelleRegle->premisse = premisse;
        nouvelleRegle->conclusion = conclusion;
        nouvelleRegle->suiv = NULL;
    }
    return nouvelleRegle;
}

// Fonction pour créer une nouvelle base de connaissances
BC creerBC(regle* regles) {
    BC nouvelleBC;
    nouvelleBC.regles = regles;
    return nouvelleBC;
}

// Fonction pour ajouter une proposition à une liste de propositions
proposition* ajouterPropositionAListe(proposition* liste, char id, bool valeur) {
    proposition* nouvelleProposition = creerProposition(id, valeur);
    if (nouvelleProposition != NULL) {
        nouvelleProposition->suiv = liste;
        return nouvelleProposition;
    } else {
        return liste; // Retourner la liste inchangée en cas d'erreur
    }
}

// Fonction pour afficher une proposition
void afficherProposition(proposition* prop) {
    if (prop != NULL) {
        printf("%c %s", prop->id, prop->valeur ? "Vrai" : "Faux");
        if (prop->suiv != NULL) {
            printf(" ET ");
            afficherProposition(prop->suiv);
        } else {
            printf("\n");
        }
    }
}

// Fonction pour afficher une règle
void afficherRegle(regle* r) {
    if (r != NULL) {
        printf("Regle :\n");
        printf("  Premisse : ");
        afficherProposition(r->premisse);
        printf("  Conclusion : ");
        afficherProposition(r->conclusion);
        printf("\n");
    }
}

// Fonction pour libérer la mémoire d'une liste de propositions
void libererListePropositions(proposition* prop) {
    while (prop != NULL) {
        proposition* suivant = prop->suiv;
        free(prop);
        prop = suivant;
    }
}

// Fonction pour libérer la mémoire d'une règle
void libererRegle(regle* r) {
    if (r != NULL) {
        libererListePropositions(r->premisse);
        libererListePropositions(r->conclusion);
        free(r);
    }
}

// Fonction pour libérer la mémoire de la base de connaissances
void libererBC(BC baseConnaissances) {
    regle* current = baseConnaissances.regles;
    while (current != NULL) {
        regle* suivant = current->suiv;
        libererRegle(current);
        current = suivant;
    }
}

// Fonction pour ajouter une règle à la base de connaissances
BC ajouterRegleABase(BC baseConnaissances, regle* nouvelleRegle) {
    regle* current = baseConnaissances.regles;
    if (current == NULL) {
        baseConnaissances.regles = nouvelleRegle;
    } else {
        while (current->suiv != NULL) {
            current = current->suiv;
        }
        current->suiv = nouvelleRegle;
    }
    return baseConnaissances;
}

int main() {
    BC baseConnaissances = creerBC(NULL);
    int reglesValidees = 0;

    while (reglesValidees < 3) {
        char choix;
        printf("Que voulez-vous faire?\n");
        printf("1. Ajouter une prémisse\n");
        printf("2. Ajouter une conclusion\n");
        printf("3. Valider la règle\n");
        scanf(" %c", &choix);

        proposition* premisse = NULL;
        proposition* conclusion = NULL;

        switch (choix) {
            case '1':
                printf("Entrez une prémisse (ex: A true): ");
                char id1;
                bool valeur1;
                scanf(" %c %d", &id1, &valeur1);
                premisse = ajouterPropositionAListe(premisse, id1, valeur1);
                break;

            case '2':
                printf("Entrez une conclusion (ex: B false): ");
                char id2;
                bool valeur2;
                scanf(" %c %d", &id2, &valeur2);
                conclusion = ajouterPropositionAListe(conclusion, id2, valeur2);
                break;

            case '3':
                if (premisse != NULL && conclusion != NULL) {
                    regle* nouvelleRegle = creerRegle(premisse, conclusion);
                    baseConnaissances = ajouterRegleABase(baseConnaissances, nouvelleRegle);
                    reglesValidees++;
                    printf("Regle ajoutée avec succès!\n");
                } else {
                    printf("Erreur: La règle doit avoir une prémisse et une conclusion.\n");
                }
                break;

            default:
                printf("Choix invalide. Veuillez entrer 1, 2 ou 3.\n");
        }
    }

    // Affichage de toutes les règles de la base de connaissances
    printf("Base de connaissances après ajout de 3 règles :\n");
    afficherRegle(baseConnaissances.regles);

    // Libération de la mémoire
    libererBC(baseConnaissances);

    return 0;
}
