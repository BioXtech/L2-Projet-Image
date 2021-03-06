/*
* Projet de programmation en C
* Binome constitue de Doan Duc-Thong et Porro Guillaume
* L2 Informatique, Université de Poitiers, 2020-2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include <float.h>

Image* createImage(int x, int y)
{
    if(x <= 0 || y <= 0)
    {
        printf("Erreur dans les parametres pour creer l'image\n");
        return NULL;
    }

    Image *allocatedImage = (Image*)malloc(sizeof(Image));

    allocatedImage->sizeX = x; // Longueur de x = nombre de colonnes
    allocatedImage->sizeY = y; // Longueur de y = nombre de lignes

    allocatedImage->image = (Pixel **)malloc(sizeof(Pixel *) * allocatedImage->sizeX); //Alloue la place pour les colonnes de pixels (1 case = 1 colonne de pixel)
    for (int i=0; i<allocatedImage->sizeX; i++)
    {
        allocatedImage->image[i] = (Pixel *)malloc(sizeof(Pixel) * allocatedImage->sizeY); // Alloue les lignes de pixels
    }

    return allocatedImage;
}

void destructImage(Image* image)
{
    for (int i=0; i<image->sizeX; i++)
    {
        free(image->image[i]);
    }
    free(image->image);
    free(image);
}

void saveImage(Image *pxArray, char nomFichier[])
{
    FILE *image = fopen(nomFichier,"w");

    // File header
    fprintf(image,"P3\n");
    fprintf(image,"%d %d\n", pxArray->sizeX, pxArray->sizeY);
    fprintf(image,"255\n");

    //Actual image
    for(int y = 0; y < pxArray->sizeY; y++)
    {
        for(int x = 0; x < pxArray->sizeX; x++)
        {
            fprintf(image, "%d %d %d ", pxArray->image[x][y].r,pxArray->image[x][y].v,pxArray->image[x][y].b);
        }
        fprintf(image,"\n");
    }

    fclose(image);

}

Image* loadImage(char nomFichier[])
{
    printf("Execution loadImage()\n");

    FILE *image = fopen(nomFichier,"r");
    if(image == NULL)
    {
        perror("Erreur: l'image n'existe pas");
        exit(NULL);
    }

    char headerParam[5];
    int x,y,colorDepth;
    int r,v,b;
    Pixel pixel = {0,0,0};

    fscanf(image,"%s",headerParam);
    fscanf(image,"%d",&x);
    fscanf(image,"%d",&y);
    fscanf(image,"%d",&colorDepth);

    Image* imageReturn = createImage(x,y);

    printf("Name: %s, Type: %s, x: %d, y: %d, Color depth: %d\n",nomFichier,headerParam,imageReturn->sizeX,imageReturn->sizeY,colorDepth);

    for(int y = 0; y < imageReturn->sizeY; y++)
    {
        for(int x = 0; x < imageReturn->sizeX; x++)
        {
            fscanf(image, "%d %d %d ", &r,&v,&b);
            pixel.r = r;
            pixel.v = v;
            pixel.b = b;
            imageReturn->image[x][y] = pixel;
        }
    }

    fclose(image);
    return imageReturn;
}

void redChannel(char nomFichier[])
{
    Image* image = loadImage(nomFichier);

    for(int x = 0; x < image->sizeX; x++)
    {
        for(int y = 0; y < image->sizeY; y++)
        {
            image->image[x][y].v = 0;
            image->image[x][y].b = 0;
        }
    }

    saveImage(image, "red.ppm");
    destructImage(image);
}

void greenChannel(char nomFichier[])
{
    Image* image = loadImage(nomFichier);

    for(int x = 0; x < image->sizeX; x++)
    {
        for(int y = 0; y < image->sizeY; y++)
        {
            image->image[x][y].r = 0;
            image->image[x][y].b = 0;
        }
    }

    saveImage(image, "green.ppm");
    destructImage(image);
}

void blueChannel(char nomFichier[])
{
    Image* image = loadImage(nomFichier);

    for(int x = 0; x < image->sizeX; x++)
    {
        for(int y = 0; y < image->sizeY; y++)
        {
            image->image[x][y].r = 0;
            image->image[x][y].v = 0;
        }
    }

    saveImage(image, "blue.ppm");
    destructImage(image);
}

void greyAverage(char nomFichier[])
{
    Image* image = loadImage(nomFichier);
    Octet average = 0;

    for(int x = 0; x < image->sizeX; x++)
    {
        for(int y = 0; y < image->sizeY; y++)
        {
            average = (image->image[x][y].r + image->image[x][y].v + image->image[x][y].b)/3;

            image->image[x][y].r = average;
            image->image[x][y].v = average;
            image->image[x][y].b = average;
        }
    }

    saveImage(image, "greyAverage.ppm");
    destructImage(image);
}

void greyMax(char nomFichier[])
{
    Image* image = loadImage(nomFichier);
    Octet max = 0;
    Octet r,v,b;

    for(int x = 0; x < image->sizeX; x++)
    {
        for(int y = 0; y < image->sizeY; y++)
        {
            r = image->image[x][y].r;
            v = image->image[x][y].v;
            b = image->image[x][y].b;

            if(r >= v && r >= b)
            {
                max = r;
            }
            else if(v >= r && v >= b)
            {
                max = v;
            }
            else
            {
                max = b;
            }

            image->image[x][y].r = max;
            image->image[x][y].v = max;
            image->image[x][y].b = max;
        }
    }

    saveImage(image, "greyMax.ppm");
    destructImage(image);
}

void sepia(char nomFichier[])
{
    Image* image = loadImage(nomFichier);
    int newR,newV,newB;

    for(int x = 0; x < image->sizeX; x++)
    {
        for(int y = 0; y < image->sizeY; y++)
        {
            newR = 0.393*(image->image[x][y].r) + 0.769*(image->image[x][y].v) + 0.189*(image->image[x][y].b);
            newV = 0.349*(image->image[x][y].r) + 0.686*(image->image[x][y].v) + 0.168*(image->image[x][y].b);
            newB = 0.272*(image->image[x][y].r) + 0.534*(image->image[x][y].v) + 0.131*(image->image[x][y].b);

            if(newR > 255)
            {
                newR = 255;
            }

            if(newV > 255)
            {
                newV = 255;
            }

            if(newB > 255)
            {
                newB = 255;
            }

            image->image[x][y].r = newR;
            image->image[x][y].v = newV;
            image->image[x][y].b = newB;
        }
    }

    saveImage(image, "sepia.ppm");
    destructImage(image);
}

void negative(char nomFichier[])
{
    Image* image = loadImage(nomFichier);
    Octet newR,newV,newB;

    for(int x = 0; x < image->sizeX; x++)
    {
        for(int y = 0; y < image->sizeY; y++)
        {
            newR = 255 - image->image[x][y].r;
            newV = 255 - image->image[x][y].v;
            newB = 255 - image->image[x][y].b;

            image->image[x][y].r = newR;
            image->image[x][y].v = newV;
            image->image[x][y].b = newB;
        }
    }

    saveImage(image, "negative.ppm");
    destructImage(image);
}

void threshold(char nomFichier[])
{
    Image* image = loadImage(nomFichier);
    Octet average = 0;

    Pixel noir = {0,0,0}, blanc = {255,255,255};

    for(int x = 0; x < image->sizeX; x++)
    {
        for(int y = 0; y < image->sizeY; y++)
        {
            average = (image->image[x][y].r + image->image[x][y].v + image->image[x][y].b)/3;

            if(average > 100) //Seuil choisi de facon empirique
            {
                image->image[x][y] = blanc;
            }
            else
            {
                image->image[x][y] = noir;
            }
        }
    }

    saveImage(image, "threshold.ppm");
    destructImage(image);
}

void thresholdOtsu(char nomFichier[])
{
    Image* image = loadImage(nomFichier);
    int average = 0, i;
    int histogramme[256];
    double probaPixel[256];
    double sum = 0.0;

    Pixel noir = {0,0,0}, blanc = {255,255,255};

    for(i = 0; i <= 255; i++)
    {
        histogramme[i] = 0;
    }

    for(int x = 0; x < image->sizeX; x++)
    {
        for(int y = 0; y < image->sizeY; y++)
        {
            average = (image->image[x][y].r + image->image[x][y].v + image->image[x][y].b)/3;
            histogramme[average]++;
        }
    }

    int nbPixel = image->sizeX * image->sizeY;
    //printf("%d\n",nbPixel);
    for(i = 0; i <= 255; i++)
    {
        probaPixel[i] = (double)histogramme[i]/nbPixel;
        //sum = sum + probaPixel[i];
        //Drawing graphics
        /*for(int j = 0; j < probaPixel[i]*10000; j++){
            printf("*");
        }
        printf("*\n");*/
        //printf("%3d : %8d | %8f\n", i, histogramme[i],probaPixel[i]*100);
    }
    //printf("Somme des probas: %f\n", sum*100); //Checking the sum value is near 100

    double omega1, omega2,
           moyenne1, moyenne2,
           variance1, variance2;
    double variances[256];
    int t,wall;
    for(t = 0; t <= 255; t++)
    {
        omega1 = 0.0;
        omega2 = 0.0;
        moyenne1 = 0.0;
        moyenne2 = 0.0;
        variance1 = 0.0;
        variance2 = 0.0;

        //printf("Classe %d\n",t);
        for(wall = 0; wall <= t; wall++)
        {
            omega1 += probaPixel[wall];
        }
        for(wall = t+1; wall <= 255; wall++)
        {
            omega2 += probaPixel[wall];
        }
        //printf("Omega1: %f, Omega2: %f\n", omega1, omega2);

        for(wall = 0; wall < t; wall++)
        {
            moyenne1 += (wall+1)*probaPixel[wall];
        }
        for(wall = t; wall <= 255; wall++)
        {
            moyenne2 += (wall+1)*probaPixel[wall];
        }

        //printf("%f\n",moyenne1);
        if(omega1 != 0.0)
        {
            moyenne1 = moyenne1/omega1;
        }
        if(omega2 != 0)
        {
            moyenne2 = moyenne2/omega2;
        }
        //printf("Moyenne1: %f, Moyenne2: %f\n",moyenne1,moyenne2);

        for(wall = 0; wall <= t; wall++)
        {
            variance1 += ((wall - moyenne1)*(wall - moyenne1))* probaPixel[wall];
        }
        for(wall = t+1; wall <= 255; wall++)
        {
            variance1 += ((wall - moyenne2)*(wall - moyenne2))* probaPixel[wall];
        }

        if(omega1 != 0.0)
        {
            variance1 = variance1/omega1;
        }
        if(omega2 != 0)
        {
            variance2 = variance2/omega2;
        }

        variances[t] = variance1 + variance2;
        //printf("Variance1: %f, Variance2: %f\n\n",variance1,variance2);
    }

    float minVariance = FLT_MAX;
    int seuil = -1;
    for(i = 0; i <= 255; i++)
    {
        //printf("%f\n",variances[i]);
        if(variances[i]<minVariance)
        {
            minVariance = variances[i];
            seuil = i;
        }
    }
    //printf("Seuil: %f pour indice %d\n",minVariance,seuil);

    for(int x = 0; x < image->sizeX; x++)
    {
        for(int y = 0; y < image->sizeY; y++)
        {
            average = (image->image[x][y].r + image->image[x][y].v + image->image[x][y].b)/3;

            if(average > seuil) //Seuil choisi selon la technique d'Otsu
            {
                image->image[x][y] = blanc;
            }
            else
            {
                image->image[x][y] = noir;
            }
        }
    }

    saveImage(image, "thresholdOtsu.ppm");
    destructImage(image);
}

void pixelate(char nomFichier[])
{

    Image *originalImage = loadImage(nomFichier);
    Image *newImage = createImage(originalImage->sizeX,originalImage->sizeY);

    Pixel currentPixel = {0,0,0};
    int xIndex=0,yIndex=0;

    for(int x = 1; x < originalImage->sizeX; x+=3)
    {
        for(int y = 1; y < originalImage->sizeY; y+=3)
        {

            currentPixel = originalImage->image[x][y];

            for(int i = -1; i <= 1; i++)
            {
                for(int j = -1; j <= 1; j++)
                {
                    xIndex = (x+i);
                    yIndex = (y+j);
                    if(xIndex < 0 || xIndex >= originalImage->sizeX)
                    {
                        xIndex = x;
                    }
                    if(yIndex < 0 || yIndex >= originalImage->sizeY)
                    {
                        yIndex = y;
                    }
                    newImage->image[xIndex][yIndex] = currentPixel;
                }
            }
        }
    }

    saveImage(newImage, "pixelated.ppm");
    destructImage(originalImage);
    destructImage(newImage);
}

void lowPass(char nomFichier[])
{
    Image *originalImage = loadImage(nomFichier);
    Image *newImage = createImage(originalImage->sizeX,originalImage->sizeY);

    int averageRed, averageGreen, averageBlue;

    Pixel newPixel = {0,0,0};
    int xIndex,yIndex;

    for(int x = 0; x < originalImage->sizeX; x++)
    {
        for(int y = 0; y < originalImage->sizeY; y++)
        {
            averageRed = 0;
            averageGreen = 0;
            averageBlue = 0;

            for(int i = -1; i <= 1; i++)
            {
                for(int j = -1; j <= 1; j++)
                {
                    xIndex = (x+i);
                    yIndex = (y+j);
                    if(xIndex < 0 || xIndex >= originalImage->sizeX)
                    {
                        xIndex = x;
                    }
                    if(yIndex < 0 || yIndex >= originalImage->sizeY)
                    {
                        yIndex = y;
                    }
                    averageRed += originalImage->image[xIndex][yIndex].r;
                    averageGreen += originalImage->image[xIndex][yIndex].v;
                    averageBlue += originalImage->image[xIndex][yIndex].b;
                }
            }

            newPixel.r = averageRed/9;
            newPixel.v = averageGreen/9;
            newPixel.b = averageBlue/9;

            newImage->image[x][y] = newPixel;
        }
    }

    saveImage(newImage, "lowPass.ppm");
    destructImage(originalImage);
    destructImage(newImage);
}

void gaussianBlur(char nomFichier[])
{
    Image *originalImage = loadImage(nomFichier);
    Image *newImage = createImage(originalImage->sizeX,originalImage->sizeY);

    int averageRed, averageGreen, averageBlue;

    Pixel newPixel = {0,0,0};
    float kernel[3][3] = {
        {1,4,1},
        {4,8,4},
        {1,4,1}
    };
    int xIndex,yIndex;

    for(int x = 0; x < originalImage->sizeX; x++)
    {
        for(int y = 0; y < originalImage->sizeY; y++)
        {
            averageRed = 0;
            averageGreen = 0;
            averageBlue = 0;

            for(int i = -1; i <= 1; i++)
            {
                for(int j = -1; j <= 1; j++)
                {
                    xIndex = (x+i);
                    yIndex = (y+j);
                    if(xIndex < 0 || xIndex >= originalImage->sizeX)
                    {
                        xIndex = x;
                    }
                    if(yIndex < 0 || yIndex >= originalImage->sizeY)
                    {
                        yIndex = y;
                    }
                    averageRed += originalImage->image[xIndex][yIndex].r*kernel[1+i][1+j];
                    averageGreen += originalImage->image[xIndex][yIndex].v*kernel[1+i][1+j];
                    averageBlue += originalImage->image[xIndex][yIndex].b*kernel[1+i][1+j];
                }
            }

            newPixel.r = averageRed/28;
            newPixel.v = averageGreen/28;
            newPixel.b = averageBlue/28;

            newImage->image[x][y] = newPixel;
        }
    }

    saveImage(newImage, "gaussianBlur.ppm");
    destructImage(originalImage);
    destructImage(newImage);
}

void highPass(char nomFichier[])
{
    Image *originalImage = loadImage(nomFichier);
    Image *newImage = createImage(originalImage->sizeX,originalImage->sizeY);

    int averageRed, averageGreen, averageBlue;
    int xIndex, yIndex;

    Pixel newPixel = {0,0,0};
    /*float kernel[3][3] = {
        {-1,-2,-1},
        {-2,12,-2},
        {-1,-2,-1}
    };*/

    float kernel[3][3] = {
        {0,-1,0},
        {-1,5,-1},
        {0,-1,0}
    };

    for(int x = 0; x < originalImage->sizeX; x++)
    {
        for(int y = 0; y < originalImage->sizeY; y++)
        {
            averageRed = 0;
            averageGreen = 0;
            averageBlue = 0;

            for(int i = -1; i <= 1; i++)
            {
                for(int j = -1; j <= 1; j++)
                {
                    xIndex = (x+i);
                    yIndex = (y+j);
                    if(xIndex < 0 || xIndex >= originalImage->sizeX)
                    {
                        xIndex = x;
                    }
                    if(yIndex < 0 || yIndex >= originalImage->sizeY)
                    {
                        yIndex = y;
                    }
                    averageRed += originalImage->image[xIndex][yIndex].r*kernel[1+i][1+j];
                    averageGreen += originalImage->image[xIndex][yIndex].v*kernel[1+i][1+j];
                    averageBlue += originalImage->image[xIndex][yIndex].b*kernel[1+i][1+j];
                }
            }

            if(averageRed > 255) averageRed = 255;
            if(averageGreen > 255) averageGreen = 255;
            if(averageBlue > 255) averageBlue = 255;
            newPixel.r = averageRed;
            newPixel.v = averageGreen;
            newPixel.b = averageBlue;

            newImage->image[x][y] = newPixel;
        }
    }

    saveImage(newImage, "highPass.ppm");
    destructImage(originalImage);
    destructImage(newImage);
}
