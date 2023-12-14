//
// Created by lucas on 14/12/2023.
//

#ifndef LO21_AFFICHAGE_H
#define LO21_AFFICHAGE_H

#include "struct.h"

void propositionAppartientAPremisse(char nom, bool valeur, Proposition* premisse);
bool premisseEstVide(Regle* regle);
void afficherListePropositions(Proposition* liste);
void afficherRegle(Regle* r);

#endif //LO21_AFFICHAGE_H
