/*
* Projet de programmation en C
* Binome constitue de Doan Duc-Thong et Porro Guillaume
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "image.h"
#include "interface.h"

int random(int min, int max)
{
    return (rand()% (max-min+1))+min;
}

int main()
{
    // Initialisation du random
    srand(time (NULL));

    // Initialisation de constante de pixel
    Pixel rouge = {255,0,0};
    Pixel vert = {0,255,0};
    Pixel bleu = {0,0,255};

    /*
    Image *image1 = createImage(50,50);
    Image *imageAModifier = createImage(50,50);
    Image *imageChargee = NULL;

    // Creation d'une image avec des pixels bleus, rouges ou verts
    for(int x = 0; x < image1->sizeX; x++)
    {
        for(int y = 0; y < image1->sizeY; y++)
        {
            switch (random(0,2))
            {
                case 0:
                    image1->image[x][y] = rouge;
                    break;
                case 1:
                    image1->image[x][y] = vert;
                    break;
                case 2:
                    image1->image[x][y] = bleu;
                    break;

                default:
                    image1->image[x][y] = bleu;
                    break;
            }
        }
    }
    saveImage(image1,"images/test.ppm");


    // Creation d'une image rouge puis modification en lui rajoutant deux lignes
    for(int x = 0; x < imageAModifier->sizeX; x++)
    {
        for(int y = 0; y < imageAModifier->sizeY; y++)
        {
            imageAModifier->image[x][y] = rouge;
        }
    }
    saveImage(imageAModifier,"images/avant.ppm");
    imageChargee = loadImage("images/avant.ppm");
    for(int i = 0; i < imageChargee->sizeX; i++)
    {
        imageChargee->image[5][i] = vert;
        imageChargee->image[i][5] = bleu;
    }
    saveImage(imageChargee,"images/apres.ppm");

    */
    // Test d'effets sur images
    char fichier[20] = "cell.ppm";
    // /*
    redChannel(fichier);
    greenChannel(fichier);
    blueChannel(fichier);
    greyAverage(fichier);
    greyMax(fichier);
    sepia(fichier);
    negative(fichier);
    threshold(fichier);
    thresholdOtsu(fichier);
    pixelate(fichier);
    lowPass(fichier);
    // */
    gaussianBlur(fichier);
    highPass(fichier);

    // Liberation de la memoire
    /*
    destructImage(image1);
    destructImage(imageAModifier);
    destructImage(imageChargee);
    */

    return 0;
}
