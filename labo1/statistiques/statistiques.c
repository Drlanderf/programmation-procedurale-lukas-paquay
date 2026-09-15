#include <stdio.h>
#include <string.h>
#include "statistiques.h"

int compterCompetences(const Competence competences[], int nbCompetences)
{
    (void)competences;
    return nbCompetences;
}

int trouverNiveauMaximum(const Competence competences[], int nbCompetences)
{
    if (nbCompetences <= 0)
        return 0;

    int maximum = competences[0].niveau;

    for (int i = 1; i < nbCompetences; i++)
    {
        if (competences[i].niveau > maximum)
            maximum = competences[i].niveau;
    }

    return maximum;
}

int compterProjetsTermines(const Projet projets[], int nbProjets)
{
    int compteur = 0;

    for (int i = 0; i < nbProjets; i++)
    {
        if (strcmp(projets[i].statut, "TERMINE") == 0)
            compteur++;
    }

    return compteur;
}

int compterProjetsEnCours(const Projet projets[], int nbProjets)
{
    int compteur = 0;

    for (int i = 0; i < nbProjets; i++)
    {
        if (strcmp(projets[i].statut, "EN COURS") == 0)
            compteur++;
    }

    return compteur;
}

int compterProjetsProduction(const Projet projets[], int nbProjets)
{
    int compteur = 0;

    for (int i = 0; i < nbProjets; i++)
    {
        if (strcmp(projets[i].statut, "EN PRODUCTION") == 0)
            compteur++;
    }

    return compteur;
}

double calculerTauxProjetsActifs(const Projet projets[], int nbProjets)
{
    if (nbProjets == 0)
        return 0.0;

    int actifs = nbProjets - compterProjetsTermines(projets, nbProjets);

    return ((double)actifs / nbProjets) * 100.0;
}

static int trouverTechnologieLaPlusUtilisee(
    const Projet projets[],
    int nbProjets,
    char *resultat,
    int tailleResultat)
{
    /*
     * Pour garder le fichier TXT simple, cette fonction compte les
     * technologies séparées par '/'.
     *
     * Elle utilise un petit tableau local de technologies rencontrées.
     */
    char technologies[100][80];
    int compteurs[100];
    int nbTechnologies = 0;

    for (int i = 0; i < nbProjets; i++)
    {
        char copie[250];
        snprintf(copie, sizeof(copie), "%s", projets[i].technologies);

        char *token = strtok(copie, "/");

        while (token != NULL)
        {
            while (*token == ' ' || *token == '\t')
                token++;

            int longueur = (int)strlen(token);

            while (longueur > 0 &&
                   (token[longueur - 1] == ' ' || token[longueur - 1] == '\t'))
            {
                token[longueur - 1] = '\0';
                longueur--;
            }

            int index = -1;

            for (int j = 0; j < nbTechnologies; j++)
            {
                if (strcmp(technologies[j], token) == 0)
                {
                    index = j;
                    break;
                }
            }

            if (index == -1 && nbTechnologies < 100)
            {
                snprintf(technologies[nbTechnologies],sizeof(technologies[nbTechnologies]),"%s", token);

                compteurs[nbTechnologies] = 1;
                nbTechnologies++;
            }
            else if (index != -1)
            {
                compteurs[index]++;
            }

            token = strtok(NULL, "/");
        }
    }

    if (nbTechnologies == 0)
        return 0;

    int meilleur = 0;

    for (int i = 1; i < nbTechnologies; i++)
    {
        if (compteurs[i] > compteurs[meilleur])
            meilleur = i;
    }

    snprintf(resultat, tailleResultat, "%s", technologies[meilleur]);
    return compteurs[meilleur];
}

void afficherStatistiques(const Competence competences[], int nbCompetences,
                          const Projet projets[], int nbProjets)
{
    char technologie[80];
    int occurrences = trouverTechnologieLaPlusUtilisee(
        projets, nbProjets, technologie, sizeof(technologie));

    printf("\n");
    printf("==============================================\n");
    printf("                STATISTIQUES                 \n");
    printf("==============================================\n\n");

    printf("Technologies maitrisees     : %d\n",compterCompetences(competences, nbCompetences));

    printf("Niveau moyen                : %.1f / 5\n",calculerNiveauMoyen(competences, nbCompetences));

    printf("Niveau le plus eleve        : %d / 5\n\n",trouverNiveauMaximum(competences, nbCompetences));

    printf("Projets references          : %d\n", nbProjets);
    printf("Projets termines            : %d\n",compterProjetsTermines(projets, nbProjets));
    printf("Projets en cours            : %d\n",compterProjetsEnCours(projets, nbProjets));
    printf("Projets en production       : %d\n",compterProjetsProduction(projets, nbProjets));

    printf("\nTaux de projets actifs       : %.0f %%\n\n",calculerTauxProjetsActifs(projets, nbProjets));

    printf("Technologie la plus utilisee : ");

    if (occurrences > 0)
        printf("%s (%d projet(s))\n", technologie, occurrences);
    else
        printf("Aucune\n");

    printf("\n----------------------------------------------\n");
    printf("[0] Retour\n");
}
