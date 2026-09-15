#include <stdio.h>
#include <string.h>
#include "projets.h"

static void supprimerFinLigne(char *chaine)
{
    chaine[strcspn(chaine, "\r\n")] = '\0';
}

static void supprimerEspacesDebut(char *chaine)
{
    while (*chaine == ' ' || *chaine == '\t')
        memmove(chaine, chaine + 1, strlen(chaine));
}

int chargerProjets(const char *nomFichier,Projet projets[],int *nbProjets)
{
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL)
        return 0;

    char ligne[600];
    int dansSection = 0;
    *nbProjets = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        supprimerFinLigne(ligne);

        if (strcmp(ligne, "[PROJETS]") == 0)
        {
            dansSection = 1;
            continue;
        }

        if (ligne[0] == '[' && strcmp(ligne, "[PROJETS]") != 0)
        {
            dansSection = 0;
            continue;
        }

        if (!dansSection || ligne[0] == '\0')
            continue;

        if (*nbProjets >= MAX_PROJETS)
            break;

        char *champ1 = strtok(ligne, ";");
        char *champ2 = strtok(NULL, ";");
        char *champ3 = strtok(NULL, ";");
        char *champ4 = strtok(NULL, ";");

        if (champ1 == NULL || champ2 == NULL ||
            champ3 == NULL || champ4 == NULL)
            continue;

        supprimerEspacesDebut(champ1);
        supprimerEspacesDebut(champ2);
        supprimerEspacesDebut(champ3);
        supprimerEspacesDebut(champ4);

        snprintf(projets[*nbProjets].nom,
                 sizeof(projets[*nbProjets].nom), "%s", champ1);

        snprintf(projets[*nbProjets].domaine,sizeof(projets[*nbProjets].domaine), "%s", champ2);

        snprintf(projets[*nbProjets].technologies,sizeof(projets[*nbProjets].technologies), "%s", champ3);

        snprintf(projets[*nbProjets].statut,sizeof(projets[*nbProjets].statut), "%s", champ4);

        (*nbProjets)++;
    }

    fclose(fichier);
    return 1;
}

static void afficherProjet(const Projet *projet, int numero)
{
    printf("%d. %s\n", numero, projet->nom);
    printf("   Domaine       : %s\n", projet->domaine);
    printf("   Technologies  : %s\n", projet->technologies);
    printf("   Statut        : %s\n\n", projet->statut);
}

void afficherTousProjets(const Projet projets[], int nbProjets)
{
    printf("\n");
    printf("==============================================\n");
    printf("                  PROJETS                    \n");
    printf("==============================================\n\n");

    if (nbProjets == 0)
    {
        printf("Aucun projet disponible.\n");
        return;
    }

    for (int i = 0; i < nbProjets; i++)
        afficherProjet(&projets[i], i + 1);

    printf("----------------------------------------------\n");
    printf("[0] Retour\n");
}

void afficherProjetsTermines(const Projet projets[], int nbProjets)
{
    printf("\n");
    printf("==============================================\n");
    printf("              PROJETS TERMINES               \n");
    printf("==============================================\n\n");

    int trouve = 0;
    int numero = 1;

    for (int i = 0; i < nbProjets; i++)
    {
        if (strcmp(projets[i].statut, "TERMINE") == 0)
        {
            afficherProjet(&projets[i], numero++);
            trouve = 1;
        }
    }

    if (!trouve)
        printf("Aucun projet termine.\n");

    printf("----------------------------------------------\n");
    printf("[0] Retour\n");
}

void afficherProjetsEnCours(const Projet projets[], int nbProjets)
{
    printf("\n");
    printf("==============================================\n");
    printf("               PROJETS EN COURS              \n");
    printf("==============================================\n\n");

    int trouve = 0;
    int numero = 1;

    for (int i = 0; i < nbProjets; i++)
    {
        if (strcmp(projets[i].statut, "EN COURS") == 0)
        {
            afficherProjet(&projets[i], numero++);
            trouve = 1;
        }
    }

    if (!trouve)
        printf("Aucun projet en cours.\n");

    printf("----------------------------------------------\n");
    printf("[0] Retour\n");
}

void rechercherProjetTechnologie(const Projet projets[], int nbProjets)
{
    char recherche[100];

    printf("\n");
    printf("Technologie a rechercher : ");

    if (fgets(recherche, sizeof(recherche), stdin) == NULL)
        return;

    supprimerFinLigne(recherche);

    if (recherche[0] == '\0')
        return;

    printf("\nProjets utilisant \"%s\" :\n\n", recherche);

    int trouve = 0;
    int numero = 1;

    for (int i = 0; i < nbProjets; i++)
    {
        if (strstr(projets[i].technologies, recherche) != NULL)
        {
            afficherProjet(&projets[i], numero++);
            trouve = 1;
        }
    }

    if (!trouve)
        printf("Aucun projet ne correspond a cette technologie.\n");

    printf("\n----------------------------------------------\n");
    printf("[0] Retour\n");
}

void menuProjets(const Projet projets[], int nbProjets)
{
    int choix;

    do
    {
        printf("\n");
        printf("==============================================\n");
        printf("                  PROJETS                    \n");
        printf("==============================================\n\n");

        printf("[1] Afficher tous les projets\n");
        printf("[2] Afficher les projets termines\n");
        printf("[3] Afficher les projets en cours\n");
        printf("[4] Rechercher par technologie\n");
        printf("[0] Retour\n\n");

        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            choix = -1;
        }
        else
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
        }

        switch (choix)
        {
            case 1:
                afficherTousProjets(projets, nbProjets);
                getchar();
                break;

            case 2:
                afficherProjetsTermines(projets, nbProjets);
                getchar();
                break;

            case 3:
                afficherProjetsEnCours(projets, nbProjets);
                getchar();
                break;

            case 4:
                rechercherProjetTechnologie(projets, nbProjets);
                getchar();
                break;

            case 0:
                break;

            default:
                printf("Choix invalide.\n");
                getchar();
                break;
        }

    } while (choix != 0);
}
