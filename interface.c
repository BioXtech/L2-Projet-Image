/*
* Projet de programmation en C
* Binome constitue de Doan Duc-Thong et Porro Guillaume
* L2 Informatique, Université de Poitiers, 2020-2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "image.h"

#define NOMBRE_FILTRES 13
#define TAILLE_NOM_FICHIER_MAX 51

void argParse(int argc, char *argv[])
{
    int numFiltre;
    char nomFichier[TAILLE_NOM_FICHIER_MAX];
    void (*nomFonctions[NOMBRE_FILTRES])(char nomFichier[]) =
    {
        redChannel,
        greenChannel,
        blueChannel,
        greyAverage,
        greyMax,
        sepia,
        negative,
        threshold,
        thresholdOtsu,
        pixelate,
        lowPass,
        gaussianBlur,
        highPass
    };
    char *nomFiltres[NOMBRE_FILTRES] =
    {
        "Cannal de couleur rouge",
        "Cannal de couleur verte",
        "Cannal de couleur bleue",
        "Gris avec la methode des moyennes",
        "Gris avec la methode des maximums",
        "Sepia",
        "Negatif",
        "Seuillage",
        "Seuillage avec la methode d'Otsu",
        "Pixelisation",
        "Filtre passe-bas ou floutage",
        "Flou gaussien",
        "Filtre passe-haut"
    };

    // Cas sans arguments
    if(argc == 1)
    {
        numFiltre = getUserInput(nomFichier, nomFiltres);
        (*nomFonctions[numFiltre])(nomFichier);
    }
    else if(argc == 3 && strtol(argv[1],NULL,10) >= 0 && strtol(argv[1],NULL,10) < NOMBRE_FILTRES) //Cas avec 2 arguments passes
    {
        numFiltre = strtol(argv[1], NULL, 10);
        (*nomFonctions[numFiltre])(argv[2]);
    }
    else if(argc == 2 && (!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help"))) //Cas de l'aide
    {
        printf("Aide du programme\n-----------------\n");
        printf("Parametres d'appel: numero de filtre, nom du fichier\n");
        printf("Liste des filtres\n");
        for(int i = 0; i < NOMBRE_FILTRES; i++)
        {
            printf("%d - %s\n",i, nomFiltres[i]);
        }
    }
    else //Cas avec nombre d'arguments invalide ou arguments invalides
    {
        printf("Erreur: arguments specifies !\n");
        printf("2 arguments requis: numeroFiltre, nomFichier\n");
        printf("Option -h ou --help pour avoir de l'aide et la liste des numeros des filtres\n");
        exit(NULL);
    }
}

int getUserInput(char nomFichier[], char *nomFiltres[])
{
    int numFiltre;

    //Selection filtre
    do
    {
        printf("Veuillez specifier quel filtre voulez-vous utiliser: ");
        fflush(stdin);
        scanf("%d",&numFiltre);
        if( numFiltre >= 0 && numFiltre < NOMBRE_FILTRES)
        {
            printf("Vous avez selectionne : %s\n", nomFiltres[numFiltre]);
        }
        else
        {
            printf("Le nombre entre n'est pas valide\n");
            printf("Liste des filtres\n");
            for(int i = 0; i < NOMBRE_FILTRES; i++)
            {
                printf("%d - %s\n",i, nomFiltres[i]);
            }
            numFiltre = -1;
        }
    }
    while(numFiltre < 0 || numFiltre >= NOMBRE_FILTRES);

    //Nom de fichier
    printf("Nom du fichier de l'image : ");
    fflush(stdin);
    scanf("%s", nomFichier);

    return numFiltre;
}
