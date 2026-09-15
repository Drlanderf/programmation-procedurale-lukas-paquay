#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "profil/profil.h"
#include "competences/competences.h"
#include "projets/projets.h"
#include "statistiques/statistiques.h"

#define DATA_FILE "data.txt"

static void viderBuffer(void)// Vide le buffer clavier jusqu'à la fin de la ligne
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static int lireChoix(void)
{ //Pourquoi faire un simple scanf quand on peut faire une fonction qui l'utilise + vérifie la valeur entrée
    int choix;
    if (scanf("%d", &choix) != 1)
    {
        viderBuffer();
        return -1;
    }
    viderBuffer();
    return choix;
}

static void pauseConsole(void)
{
    printf("\nAppuyez sur ENTER pour continuer...");
    getchar();
}

static void afficherMenuPrincipal(void)
{
    printf("\n");
    printf("==============================================\n");
    printf("                 DEV PROFILE                 \n");
    printf("==============================================\n\n");

    printf("Bienvenue sur le profil de Lukas\n\n");

    printf("[1] Mon profil\n");
    printf("[2] Mes competences\n");
    printf("[3] Mes projets\n");
    printf("[4] Mes statistiques\n\n");
    printf("[0] Quitter\n\n");

    printf("----------------------------------------------\n");
    printf("Votre choix : ");
}

int main(void)
{
    setlocale(LC_ALL, "");

    Profil profil;
    Competence competences[MAX_COMPETENCES];
    Projet projets[MAX_PROJETS];

    int nbCompetences = 0;
    int nbProjets = 0;

    //On test si les différentes ouverture fonctionne correctement, si aucun problème on peut continuer,
    //En C++/C# on utilisera les try/catch mais ici on fait avec les moyen du bord
    if (!chargerProfil(DATA_FILE, &profil))
    {
        printf("Erreur lors du chargement du profil.\n");
        return EXIT_FAILURE;
    }

    if (!chargerCompetences(DATA_FILE, competences, &nbCompetences))
    {
        printf("Erreur lors du chargement des competences.\n");
        return EXIT_FAILURE;
    }

    if (!chargerProjets(DATA_FILE, projets, &nbProjets))
    {
        printf("Erreur lors du chargement des projets.\n");
        return EXIT_FAILURE;
    }

    int choix;
    //petit switch case pour choisir vers où on veut aller
    do
    {
        afficherMenuPrincipal();
        choix = lireChoix();

        switch (choix)
        {
            case 1:
                afficherProfil(&profil);
                pauseConsole();
                break;

            case 2:
                menuCompetences(competences, nbCompetences);
                break;

            case 3:
                menuProjets(projets, nbProjets);
                break;

            case 4:
                afficherStatistiques(competences, nbCompetences,
                                      projets, nbProjets);
                pauseConsole();
                break;

            case 0:
                printf("\nFermeture du programme...\n");
                break;

            default:
                printf("\nChoix invalide.\n");
                pauseConsole();
                break;
        }

    } while (choix != 0);

    return EXIT_SUCCESS;
}
