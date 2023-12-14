//
// Created by lucas on 14/12/2023.
//

#include "moteur-inference.h"

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

// Fonction du moteur d'inference
void moteurInference(Proposition* faits_connus, Regle* base_de_connaissances, Proposition** faits_deduits) {
    Regle* regle_courante = base_de_connaissances;
    bool nouveaux_faits_trouves = false; // Flag to track new facts

    while (regle_courante != NULL) {
        // Si la règle a déjà été vérifiée, passer à la suivante
        if (regle_courante->verif) {
            regle_courante = regle_courante->suiv;
            continue;
        }

        // Vérifier si la prémisse de la règle est respectée
        Proposition* premisse_courante = regle_courante->premisse;
        bool premisse_respectee = true;

        while (premisse_courante != NULL) {
            // Recherche de la proposition correspondante dans les faits connus
            Proposition* fait_courant = faits_connus;
            bool proposition_trouvee = false;

            while (fait_courant != NULL) {
                if (fait_courant->nom == premisse_courante->nom && fait_courant->valeur == premisse_courante->valeur) {
                    proposition_trouvee = true;
                    break;
                }
                fait_courant = fait_courant->suiv;
            }

            if (!proposition_trouvee) {
                // La prémisse n'est pas respectée
                premisse_respectee = false;
                break;
            }

            premisse_courante = premisse_courante->suiv;
        }

        // Si la prémisse est respectée, ajouter la conclusion à la liste de faits déduits
        if (premisse_respectee && !regle_courante->verif) {
            ajouterConclusionAuFait(regle_courante->conclusion, &faits_connus);
            ajouterConclusionAuFait(regle_courante->conclusion, faits_deduits);

            regle_courante->verif = true; // Marquer la règle comme vérifiée
            nouveaux_faits_trouves = true; // Set the flag to true
        }

        regle_courante = regle_courante->suiv;
    }

    // Si de nouveaux faits sont trouvés, rappeler récursivement la fonction avec la nouvelle liste de faits déduits
    if (nouveaux_faits_trouves) {
        moteurInference(faits_connus, base_de_connaissances, faits_deduits);
    }
}
