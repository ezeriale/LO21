//
// Created by lucas on 14/12/2023.
//

#ifndef LO21_MOTEUR_INFERENCE_H
#define LO21_MOTEUR_INFERENCE_H

#include "struct.h"

void ajouterConclusionAuFait(Proposition* conclusion, Proposition** faits_connus);
void moteurInference(Proposition* faits_connus, Regle* base_de_connaissances, Proposition** faits_deduits);


#endif //LO21_MOTEUR_INFERENCE_H
