#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gd.h>

#define Longueur 600
#define Largeur 400

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <nom_fichier.png> <percentage1> <label1> <percentage2> <label2> ... <percentageN> <labelN>\n", argv[0]);
        return 1;
    }
    const char *nomFichier = argv[1];

    // Calcul le pourcentage total
    double totalPourcentage = 0.0;
    for (int i = 2; i < argc; i += 2) {
        totalPourcentage += atof(argv[i]);
    }

    // Cree une image fond blanc
    gdImagePtr image = gdImageCreate(Longueur, Largeur);
    int blanc = gdImageColorAllocate(image, 255, 255, 255);
    gdImageFill(image, 0, 0, blanc);

    // Dessine le Camembert
    int x = Longueur / 2;
    int y = Largeur / 2;
    int angleDebut = 0;

    for (int i = 2; i < argc; i += 2) {
        double pourcentage = atof(argv[i]);
        int couleur = gdImageColorAllocate(image, rand() % 256, rand() % 256, rand() % 256);
        int angleFin = angleDebut + (360 * pourcentage / totalPourcentage);
        gdImageFilledArc(image, x, y, Longueur / 2, Largeur / 2, angleDebut, angleFin, couleur, gdPie);
        angleDebut = angleFin;
    }

    // Sauvegarde l'image dans le nomFichier
    FILE *fichierSortie = fopen(nomFichier, "wb");
    gdImagePng(image, fichierSortie);
    fclose(fichierSortie);

    // Libère la mémoire
    gdImageDestroy(image);

    printf("Le Camembert s'est généré et sauvegardé dans %s\n", nomFichier);

    return 0;
}
