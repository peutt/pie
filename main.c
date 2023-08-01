#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gd.h>
#include <math.h>
#include <time.h>

#define Taille 1000
#define Taille_Label 15

int main(int argc, char *argv[]) {

    // Pour que les couleurs soit aléatoire à chaque execution :
    srand(time(NULL));

    // Verification du nombre d'arguments
    if (argc < 4 || argc % 2 != 0) {
        printf("Usage: %s <nom_fichier.png> <pourcentage1> <label1> <pourcentage2> <label2> ... <pourcentageN> <labelN> [<couleur_fond>]\n", argv[0]);
        return 1;
    }
    const char *nomFichier = argv[1];

    // Cree une image avec la couleur de fond
    gdImagePtr image = gdImageCreate(Taille, Taille);
    int couleurFond = gdImageColorAllocate(image, 0xFF, 0xFF, 0xFF);

    // Remplir l'image avec la couleur de fond
    gdImageFill(image, 0, 0, couleurFond);

    int noir = gdImageColorAllocate(image, 0, 0, 0);

    // Calcul le pourcentage total
    double totalPourcentage = 0.0;
    for (int i = 2; i < argc - 1; i += 2) {
        totalPourcentage += atof(argv[i]);
    }

    // Dessine le Camembert
    int x = Taille / 2;
    int y = Taille / 2;
    int diametre = Taille / 2;
    gdImageSetThickness(image, 5);
    gdImageArc(image, x, y, diametre, diametre, 0, 360, noir);
    gdImageSetThickness(image, 1);
    int angleDebut = 0;

    for (int i = 2; i < argc; i += 2) {
        // Dessine le secteur du camembert en couleur
        double pourcentage = atof(argv[i]);
        int couleur = gdImageColorAllocate(image, rand() % 256, rand() % 256, rand() % 256);
        int angleFin = angleDebut + (360 * pourcentage / 100.0);
        gdImageFilledArc(image, x, y, diametre, diametre, angleDebut, angleFin, couleur, gdPie);

        // Dessine la bordure noire du camembert
        gdImageSetThickness(image, 4);
        gdImageArc(image, x, y, diametre, diametre, angleDebut, angleFin, noir);

        // Dessine le trait noir entre les segments
        int startX = x + diametre/2 * cos(angleDebut * M_PI / 180);
        int startY = y + diametre/2 * sin(angleDebut * M_PI / 180);
        int endX = x + diametre/2 * cos(angleFin * M_PI / 180);
        int endY = y + diametre/2 * sin(angleFin * M_PI / 180);
        gdImageLine(image, x, y, startX, startY, noir);
        gdImageLine(image, x, y, endX, endY, noir);

        gdImageSetThickness(image, 1);

        // Calcul la position du label et du trait de liaison
        double midAngle = (angleDebut + angleFin) / 2.0;
        double rayonLabel = (cos(midAngle * M_PI / 180) < 0) ? diametre/1.6 + strlen(argv[i + 1])*(Taille_Label/1.2) : diametre/1.6;
        int xDebutTrait = x + diametre/2 * cos(midAngle * M_PI / 180);
        int yDebutTrait = y + diametre/2 * sin(midAngle * M_PI / 180);
        int labelX = x + rayonLabel * cos(midAngle * M_PI / 180);
        int labelY = y + diametre/1.6 * sin(midAngle * M_PI / 180);
        int xTrait = x + diametre/1.6 * cos(midAngle * M_PI / 180);

        // Ecrit le label
        gdImageStringFT(image, NULL, gdImageColorAllocate(image, 0, 0, 0), "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", Taille_Label, 0, labelX, labelY, argv[i + 1]);

        // dessine le trait entre le label et le camembert
        gdImageLine(image, xDebutTrait, yDebutTrait, xTrait, labelY, noir);

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
