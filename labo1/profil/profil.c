#include <stdio.h>
#include <string.h>
#include "profil.h"

#define SECTION_PROFIL "[PROFIL]"

static void supprimerFinLigne(char *chaine)
{
    chaine[strcspn(chaine, "\r\n")] = '\0';
}

static void copierValeur(char *destination, size_t taille,const char *ligne, const char *cle)
{
    const char *valeur = ligne + strlen(cle);
    while (*valeur == ' ' || *valeur == '\t')
        valeur++;

    snprintf(destination, taille, "%s", valeur);supprimerFinLigne(destination);
}

int chargerProfil(const char *nomFichier, Profil *profil)
{
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL)
        return 0;

    char ligne[700];
    int dansSection = 0;

    memset(profil, 0, sizeof(Profil));
    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        supprimerFinLigne(ligne);
        if (strcmp(ligne, SECTION_PROFIL) == 0)
        {
            dansSection = 1;
            continue;
        }
        if (ligne[0] == '[' && strcmp(ligne, SECTION_PROFIL) != 0)
        {
            dansSection = 0;
            continue;
        }
        if (!dansSection || ligne[0] == '\0')
            continue;
        if (strncmp(ligne, "nom=", 4) == 0)copierValeur(profil->nom, sizeof(profil->nom), ligne, "nom=");
        //profil->nom Va à l'adresse pointée par profil et accède au membre nom
        else if (strncmp(ligne, "prenom=", 7) == 0)copierValeur(profil->prenom, sizeof(profil->prenom), ligne, "prenom=");
        else if (strncmp(ligne, "formation=", 10) == 0)copierValeur(profil->formation, sizeof(profil->formation), ligne, "formation=");
        else if (strncmp(ligne, "orientation=", 12) == 0)copierValeur(profil->orientation, sizeof(profil->orientation), ligne, "orientation=");
        else if (strncmp(ligne, "presentation=", 13) == 0)copierValeur(profil->presentation, sizeof(profil->presentation), ligne, "presentation=");
        else if (strncmp(ligne, "github=", 7) == 0)copierValeur(profil->github, sizeof(profil->github), ligne, "github=");
    }

    fclose(fichier);
    return 1;
}

void afficherProfil(const Profil *profil)
{
    printf("\n");
    printf("==============================================\n");
    printf("                 MON PROFIL                   \n");
    printf("==============================================\n\n");

    printf("Nom / Prenom : %s %s\n\n", profil->prenom, profil->nom);
    printf("Formation    : %s\n", profil->formation);
    printf("Orientation  : %s\n\n", profil->orientation);
    printf("Presentation :\n");
    printf("%s\n\n", profil->presentation);
    printf("Git personnel : %s\n", profil->github);
    printf("\n----------------------------------------------\n");
    printf("[0] Retour\n");
}
