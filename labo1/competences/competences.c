#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "competences.h"

static void supprimerFinLigne(char *chaine)
{
    chaine[strcspn(chaine, "\r\n")] = '\0';
}

int chargerCompetences(const char *nomFichier,
                       Competence competences[],
                       int *nbCompetences)
{
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL)
        return 0;

    char ligne[300];
    int dansSection = 0;
    *nbCompetences = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        supprimerFinLigne(ligne);

        if (strcmp(ligne, "[COMPETENCES]") == 0)
        {
            dansSection = 1;
            continue;
        }

        if (ligne[0] == '[' && strcmp(ligne, "[COMPETENCES]") != 0)
        {
            dansSection = 0;
            continue;
        }

        if (!dansSection || ligne[0] == '\0')
            continue;

        if (*nbCompetences >= MAX_COMPETENCES)
            break;

        char *separateur = strchr(ligne, ';');

        if (separateur == NULL)
            continue;

        *separateur = '\0';

        char *technologie = ligne;
        char *niveauTexte = separateur + 1;

        while (*technologie == ' ' || *technologie == '\t')
            technologie++;

        while (*niveauTexte == ' ' || *niveauTexte == '\t')
            niveauTexte++;

        snprintf(competences[*nbCompetences].technologie,
                 sizeof(competences[*nbCompetences].technologie),
                 "%s", technologie);

        competences[*nbCompetences].niveau = atoi(niveauTexte);

        if (competences[*nbCompetences].niveau < 0)
            competences[*nbCompetences].niveau = 0;

        if (competences[*nbCompetences].niveau > 5)
            competences[*nbCompetences].niveau = 5;

        (*nbCompetences)++;
    }

    fclose(fichier);
    return 1;
}

static void afficherEtoiles(int niveau)
{
    for (int i = 0; i < niveau; i++)
        printf("*");
}

void afficherToutesCompetences(const Competence competences[], int nbCompetences)
{
    printf("\n");
    printf("==============================================\n");
    printf("                COMPETENCES                  \n");
    printf("==============================================\n\n");

    printf("%-4s %-28s %-8s %s\n", "#", "Technologie", "Niveau", "Evaluation");
    printf("------------------------------------------------\n");

    for (int i = 0; i < nbCompetences; i++)
    {
        printf("%-4d %-28s %d/5      ",
               i + 1,
               competences[i].technologie,
               competences[i].niveau);

        afficherEtoiles(competences[i].niveau);
        printf("\n");
    }

    printf("\nNiveau moyen : %.1f / 5\n",
           calculerNiveauMoyen(competences, nbCompetences));

    printf("\n----------------------------------------------\n");
    printf("[0] Retour\n");
}

void afficherCompetencesNiveau4(const Competence competences[], int nbCompetences)
{
    printf("\n");
    printf("==============================================\n");
    printf("          COMPETENCES >= NIVEAU 4            \n");
    printf("==============================================\n\n");

    int trouve = 0;

    for (int i = 0; i < nbCompetences; i++)
    {
        if (competences[i].niveau >= 4)
        {
            printf("- %-28s %d/5\n",
                   competences[i].technologie,
                   competences[i].niveau);
            trouve = 1;
        }
    }

    if (!trouve)
        printf("Aucune competence de niveau 4 ou 5.\n");

    printf("\n----------------------------------------------\n");
    printf("[0] Retour\n");
}

void afficherMeilleureCompetence(const Competence competences[], int nbCompetences)
{
    printf("\n");
    printf("==============================================\n");
    printf("          COMPETENCE LA MIEUX MAITRISEE      \n");
    printf("==============================================\n\n");

    if (nbCompetences <= 0)
    {
        printf("Aucune competence disponible.\n");
        printf("\n[0] Retour\n");
        return;
    }

    int meilleurNiveau = 0;

    for (int i = 0; i < nbCompetences; i++)
    {
        if (competences[i].niveau > meilleurNiveau)
            meilleurNiveau = competences[i].niveau;
    }

    for (int i = 0; i < nbCompetences; i++)
    {
        if (competences[i].niveau == meilleurNiveau)
        {
            printf("%s : %d/5  ",
                   competences[i].technologie,
                   competences[i].niveau);
            afficherEtoiles(competences[i].niveau);
            printf("\n");
        }
    }

    printf("\n[0] Retour\n");
}

void menuCompetences(const Competence competences[], int nbCompetences)
{
    int choix;

    do
    {
        printf("\n");
        printf("==============================================\n");
        printf("                COMPETENCES                  \n");
        printf("==============================================\n\n");

        printf("[1] Toutes les competences\n");
        printf("[2] Competences >= niveau 4\n");
        printf("[3] Competence(s) la mieux maitrisee(s)\n");
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
                afficherToutesCompetences(competences, nbCompetences);
                getchar();
                break;

            case 2:
                afficherCompetencesNiveau4(competences, nbCompetences);
                getchar();
                break;

            case 3:
                afficherMeilleureCompetence(competences, nbCompetences);
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

double calculerNiveauMoyen(const Competence competences[], int nbCompetences)
{
    if (nbCompetences == 0)
        return 0.0;

    int total = 0;

    for (int i = 0; i < nbCompetences; i++)
        total += competences[i].niveau;

    return (double)total / nbCompetences;
}
