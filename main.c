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
    srand(time (NULL));

    Pixel rouge = {255,0,0};
    Pixel vert = {0,255,0};
    Pixel bleu = {0,0,255};

    Image *image1 = createImage(50,50);
    Image *imageAModifier = createImage(50,50);
    Image *imageChargee = NULL;

    //printf("Tab @ %p\n", &(**image1->image)); //Algebre des pointeurs *(*(arr+i)+j)
    //printf("Tab @ %p\n", &(image1->image[0][0])); // Notation avec []
    // Les deux sont egaux

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

            //printf("Val [%d][%d]", x,y);
        }
    }
    saveImage(image1,"test.ppm");

    for(int x = 0; x < imageAModifier->sizeX; x++)
    {
        for(int y = 0; y < imageAModifier->sizeY; y++)
        {
            imageAModifier->image[x][y] = rouge;
        }
    }
    saveImage(imageAModifier,"avant.ppm");

    imageChargee = loadImage("avant.ppm");
    for(int i = 0; i < imageChargee->sizeX; i++)
    {
        imageChargee->image[5][i] = vert;
        imageChargee->image[i][5] = bleu;
    }
    saveImage(imageChargee,"apres.ppm");




    Image* test = loadImage("base.ppm");
    saveImage(test,"test.ppm");
    redChannel("base.ppm");
    greenChannel("base.ppm");
    blueChannel("base.ppm");
    greyAverage("base.ppm");
    greyMax("base.ppm");
    sepia("base.ppm");

    destructImage(image1);
    destructImage(imageAModifier);
    destructImage(imageChargee);
    //destructImage(test);

    return 0;
}
