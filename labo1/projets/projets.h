#ifndef PROJETS_H
#define PROJETS_H

#define MAX_PROJETS 50
#define TAILLE_NOM_PROJET 100
#define TAILLE_DOMAINE 100
#define TAILLE_TECHNOLOGIES 250
#define TAILLE_STATUT 50

typedef struct
{
    char nom[TAILLE_NOM_PROJET];
    char domaine[TAILLE_DOMAINE];
    char technologies[TAILLE_TECHNOLOGIES];
    char statut[TAILLE_STATUT];
} Projet;

int chargerProjets(const char *nomFichier,Projet projets[],int *nbProjets);

void afficherTousProjets(const Projet projets[], int nbProjets);
void afficherProjetsTermines(const Projet projets[], int nbProjets);
void afficherProjetsEnCours(const Projet projets[], int nbProjets);
void rechercherProjetTechnologie(const Projet projets[], int nbProjets);
void menuProjets(const Projet projets[], int nbProjets);

#endif
