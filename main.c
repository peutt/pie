#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gd.h>
#include <math.h>
#include <time.h>

#define Taille 600
#define Taille_Label 12

int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (argc < 3) {
        printf("Usage: %s <nom_fichier.png> <pourcentage1> <label1> <pourcentage2> <label2> ... <pourcentageN> <labelN>\n", argv[0]);
        return 1;
    }
    const char *nomFichier = argv[1];

    // Calcul le pourcentage total
    double totalPourcentage = 0.0;
    for (int i = 2; i < argc; i += 2) {
        totalPourcentage += atof(argv[i]);
    }

    // Cree une image fond blanc
    gdImagePtr image = gdImageCreate(Taille, Taille);
    int blanc = gdImageColorAllocate(image, 255, 255, 255);
    int noir = gdImageColorAllocate(image, 0, 0, 0);
    gdImageFill(image, 0, 0, blanc);

    // Dessine le Camembert
    int x = Taille / 2;
    int y = Taille / 2;
    int diametre = Taille / 2;
    gdImageSetThickness(image, 5);
    gdImageArc(image, x, y, x, y, 0, 360, noir);
    gdImageSetThickness(image, 1);
    int angleDebut = 0;

    for (int i = 2; i < argc; i += 2) {

        //Dessine le cartier du camembert en couleur
        double pourcentage = atof(argv[i]);
        int couleur = gdImageColorAllocate(image, rand() % 256, rand() % 256, rand() % 256);
        int angleFin = angleDebut + (360 * pourcentage / totalPourcentage);
        gdImageFilledArc(image, x, y, diametre, diametre, angleDebut, angleFin, couleur, gdPie);

        //Dessine la bordure noir du camembert
        gdImageSetThickness(image, 4);
        gdImageArc(image, x, y, diametre, diametre, angleDebut, angleFin, noir);

        // Dessine les bord noir entre les segments
        int startX = x + diametre/2 * cos(angleDebut * M_PI / 180);
        int startY = y + diametre/2 * sin(angleDebut * M_PI / 180);
        gdImageLine(image, x, y, startX, startY, noir);
        int endX = x + diametre/2 * cos(angleFin * M_PI / 180);
        int endY = y + diametre/2 * sin(angleFin * M_PI / 180);
        gdImageLine(image, x, y, endX, endY, noir);

        gdImageSetThickness(image, 1);

        // Calcul la position du label
        double midAngle = (angleDebut + angleFin) / 2.0;
        double rayonLabel;
        if(cos(midAngle * M_PI / 180)<0){
            rayonLabel= diametre/1.6 + strlen(argv[i + 1])*(Taille_Label/1.6);
        } else {
            rayonLabel= diametre/1.6;
        }
        int labelX = x + rayonLabel * cos(midAngle * M_PI / 180);
        int labelY = y + diametre/1.6 * sin(midAngle * M_PI / 180);

        // Ecrit le label
        gdImageStringFT(image, NULL, gdImageColorAllocate(image, 0, 0, 0), "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", Taille_Label, 0, labelX, labelY, argv[i + 1]);

        // dessine le trait entre le label et le camembert
        int xStart = x + diametre/2 * cos(midAngle * M_PI / 180);
        int yStart = y + diametre/2 * sin(midAngle * M_PI / 180);
        if(cos(midAngle * M_PI / 180)<0){
            float increment=strlen(argv[i + 1])*(Taille_Label/1.3);
            printf("sin: %f, cos: %f\n", sin(midAngle * M_PI / 180), cos(midAngle * M_PI / 180));
            if(sin(midAngle * M_PI / 180)>0){
                gdImageLine(image, xStart, yStart, labelX+increment-sin(midAngle * M_PI / 180)*increment, labelY, noir);
            } else {
                gdImageLine(image, xStart, yStart, labelX+increment+sin(midAngle * M_PI / 180)*increment, labelY, noir);
            }

        } else {
            gdImageLine(image, xStart, yStart, labelX, labelY, noir);
        }

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
