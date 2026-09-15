#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include "../competences/competences.h"
#include "../projets/projets.h"

void afficherStatistiques(const Competence competences[], int nbCompetences,const Projet projets[], int nbProjets);

int compterCompetences(const Competence competences[], int nbCompetences);
int trouverNiveauMaximum(const Competence competences[], int nbCompetences);
int compterProjetsTermines(const Projet projets[], int nbProjets);
int compterProjetsEnCours(const Projet projets[], int nbProjets);
int compterProjetsProduction(const Projet projets[], int nbProjets);
double calculerTauxProjetsActifs(const Projet projets[], int nbProjets);

#endif
