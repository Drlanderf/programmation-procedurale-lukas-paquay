#ifndef COMPETENCES_H
#define COMPETENCES_H

#define MAX_COMPETENCES 50
#define TAILLE_TECHNOLOGIE 80

typedef struct
{
    char technologie[TAILLE_TECHNOLOGIE];
    int niveau;
} Competence;

int chargerCompetences(const char *nomFichier,Competence competences[],int *nbCompetences);

void afficherToutesCompetences(const Competence competences[], int nbCompetences);
void afficherCompetencesNiveau4(const Competence competences[], int nbCompetences);
void afficherMeilleureCompetence(const Competence competences[], int nbCompetences);
void menuCompetences(const Competence competences[], int nbCompetences);
double calculerNiveauMoyen(const Competence competences[], int nbCompetences);

#endif
