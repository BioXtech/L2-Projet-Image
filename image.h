#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

typedef unsigned char Octet;

typedef struct
{
    Octet r;
    Octet v;
    Octet b;
} Pixel;

typedef struct
{
    Pixel **image;
    int sizeX;
    int sizeY;
} Image;

Image* createImage(int x, int y);
void destructImage(Image* image);

void saveImage(Image *pxArray, char nomFichier[]);
Image* loadImage(char nomFichier[]);

void redChannel(char nomFichier[]);
void greenChannel(char nomFichier[]);
void blueChannel(char nomFichier[]);

void greyAverage(char nomFichier[]);
void greyMax(char nomFichier[]);

void sepia(char nomFichier[]);

void negative(char nomFichier[]);
void threshold(char nomFichier[]); //Methode artisanale
void thresholdOtsu(char nomFichier[]); //Methode d'Otsu

void pixelate(char nomFichier[]);
void quintuplage(char nomFichier[]);
#endif // IMAGE_H_INCLUDED
