#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

Image* createImage(int x, int y)
{
    Image *image = (Image*)malloc(sizeof(Image));

    image->sizeX = x;
    image->sizeY = y;

    image->image = (Pixel **)malloc(sizeof(Pixel *) * image->sizeX);
    for (int i=0; i<image->sizeX; i++)
    {
        image->image[i] = (Pixel *)malloc(sizeof(Pixel) * image->sizeY);
    }

    return image;

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
    //fprintf(stdout,"P3\n");
    //fprintf(stdout,"%d %d\n", pxArray->sizeX, pxArray->sizeY);
    //fprintf(stdout,"255\n");

    //Actual image
    for(int x = 0; x < pxArray->sizeX; x++)
    {
        for(int y = 0; y < pxArray->sizeY; y++)
        {
            fprintf(image, "%d %d %d ", pxArray->image[x][y].r,pxArray->image[x][y].v,pxArray->image[x][y].b);
            //fprintf(stdout, "%d %d %d ", pxArray->image[x][y].r,pxArray->image[x][y].v,pxArray->image[x][y].b);
        }
        fprintf(image,"\n");
        //fprintf(stdout,"\n");
    }

    fclose(image);

}

Image* loadImage(char nomFichier[])
{
    printf("Execution loadImage()\n");

    FILE *image = fopen(nomFichier,"r");
    char headerParam[3];
    int x,y,colorDepth;
    Octet r,v,b;
    Pixel pixel = {0,0,0};

    fscanf(image,"%s",headerParam);
    fscanf(image,"%d",&x);
    fscanf(image,"%d",&y);
    fscanf(image,"%d",&colorDepth);

    Image* imageReturn = createImage(x,y);

    printf("Name: %s, Type: %s, x: %d, y: %d, Color depth: %d\n",nomFichier,headerParam,imageReturn->sizeX,imageReturn->sizeY,colorDepth);

    for(int x = 0; x < imageReturn->sizeX; x++)
    {
        for(int y = 0; y < imageReturn->sizeY; y++)
        {
            fscanf(image, "%d %d %d ", &r,&v,&b);
            pixel.r = r;
            pixel.v = v;
            pixel.b = b;
            imageReturn->image[x][y] = pixel;
            fprintf(stdout, "%d %d %d ", imageReturn->image[x][y].r,imageReturn->image[x][y].v,imageReturn->image[x][y].b);
        }
        fprintf(stdout,"\n");
    }

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

void greyAverage(char nomFichier[]){
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

void greyMax(char nomFichier[]){
    Image* image = loadImage(nomFichier);
    int max = 0;
    Octet r,v,b;

    for(int x = 0; x < image->sizeX; x++)
    {
        for(int y = 0; y < image->sizeY; y++)
        {
            r = image->image[x][y].r;
            v = image->image[x][y].v;
            b = image->image[x][y].b;

            if(r >= v && r >= b){
                max = r;
            }
            else if(v >= r && v >= b){
                max = v;
            }
            else{
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

void sepia(char nomFichier[]){
    Image* image = loadImage(nomFichier);
    Octet newR,newV,newB;

    for(int x = 0; x < image->sizeX; x++)
    {
        for(int y = 0; y < image->sizeY; y++)
        {
            newR = 0.393*(image->image[x][y].r) + 0.769*(image->image[x][y].v) + 0.189*(image->image[x][y].b);
            newV = 0.349*(image->image[x][y].r) + 0.686*(image->image[x][y].v) + 0.168*(image->image[x][y].b);
            newB = 0.272*(image->image[x][y].r) + 0.534*(image->image[x][y].v) + 0.131*(image->image[x][y].b);

            if(newR > 255){
                newR = 255;
            }

            if(newV > 255){
                newV = 255;
            }

            if(newB > 255){
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

