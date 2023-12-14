#include "struct.h"
#include "moteur-inference.h"
#include "affichage.h"

int main() {
    // Création de faits connus
    Proposition* faits_connus = NULL;
    ajouterPropositionAListe(&faits_connus, 'B', false);
    ajouterPropositionAListe(&faits_connus, 'Q', false);
    ajouterPropositionAListe(&faits_connus, 'V', true);

    // Création de la base de connaissances
    Regle *base_de_connaissances = creerBCVide();

    // Ajout des règles à la base de connaissances
    Regle* regle1 = creerRegleVide();

    Regle* regle2 = creerRegleVide();

    Regle* regle3 = creerRegleVide();

    ajouterPropositionAListe(&(regle1->premisse), 'S', false);
    ajouterPropositionAListe(&(regle1->premisse), 'B', false);
    ajouterPropositionAListe(&(regle1->conclusion), 'C', true);

    ajouterPropositionAListe(&(regle2->premisse), 'V', true);
    ajouterPropositionAListe(&(regle2->premisse), 'Q', false);
    ajouterPropositionAListe(&(regle2->conclusion), 'S', false);

    ajouterPropositionAListe(&(regle3->premisse), 'C', true);
    ajouterPropositionAListe(&(regle3->premisse), 'S', false);
    ajouterPropositionAListe(&(regle3->conclusion), 'K', true);

    ajouterRegleABase(&base_de_connaissances, &regle1);
    ajouterRegleABase(&base_de_connaissances, &regle2);
    ajouterRegleABase(&base_de_connaissances, &regle3);

    propositionAppartientAPremisse('C', true, regle1->conclusion);
    // Utilisation du résultat

    // Affichage de la base de connaissances
    printf("Base de connaissances :\n");
    Regle* regle_courante = base_de_connaissances;
    while (regle_courante != NULL) {
        afficherRegle(regle_courante);
        regle_courante = regle_courante->suiv;
    }

    // Affichage des faits connus
    printf("Faits connus :\n");
    afficherListePropositions(faits_connus);

    // Utilisation du moteur d'inference
    Proposition* faits_deduits = NULL;
    moteurInference(faits_connus, base_de_connaissances, &faits_deduits);

    // Affichage des faits déduits
    printf("Faits deduits :\n");
    afficherListePropositions(faits_deduits);

    printf("Faits connus a la fin :\n");
    afficherListePropositions(faits_connus);

    // Libération de la mémoire
    libererListePropositions(&faits_connus);
    libererListePropositions(&faits_deduits);
    libererBC(&base_de_connaissances);

    return 0;
}
