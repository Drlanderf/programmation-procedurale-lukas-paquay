#ifndef PROFIL_H
#define PROFIL_H

#define TAILLE_NOM 50
#define TAILLE_FORMATION 150
#define TAILLE_PRESENTATION 500
#define TAILLE_GITHUB 200

typedef struct
{
    char nom[TAILLE_NOM];
    char prenom[TAILLE_NOM];
    char formation[TAILLE_FORMATION];
    char orientation[TAILLE_FORMATION];
    char presentation[TAILLE_PRESENTATION];
    char github[TAILLE_GITHUB];
} Profil;

int chargerProfil(const char *nomFichier, Profil *profil);
void afficherProfil(const Profil *profil);

#endif

