# Camembert Generator

Camembert Generator est un programme en C qui génère un graphique camembert (ou diagramme circulaire) en utilisant la bibliothèque GD pour créer une image au format PNG. Le programme prend en entrée les pourcentages et les libellés des différents secteurs du camembert, ainsi qu'une couleur de fond optionnelle.

## Prérequis

Avant de compiler et exécuter le programme, assurez-vous d'avoir les éléments suivants installés sur votre système :

- Bibliothèque GD : Assurez-vous d'installer la bibliothèque GD sur votre système. Vous pouvez l'installer en utilisant la commande suivante sur Ubuntu/Debian :

  ```
  sudo apt-get install libgd-dev
  ```

- Compilation : Pour compiler le programme, assurez-vous d'avoir un compilateur C installé, comme gcc.

## Compilation

Pour compiler le programme, utilisez la commande suivante dans le dossier src:

```
gcc -o pie main.c -lgd -lm
```

## Utilisation

Pour utiliser le programme, exécutez la commande suivante dans le dossier src :

```
./pie <nom_fichier.png> <pourcentage1> <label1> <pourcentage2> <label2> ... <pourcentageN> <labelN> [<couleur_fond>]
```

- `<nom_fichier.png>` : Le nom du fichier PNG dans lequel le camembert sera sauvegardé.

- `<pourcentageX>` : Le pourcentage pour le secteur X du camembert (doit être un nombre réel positif).

- `<labelX>` : Le libellé associé au secteur X du camembert.

- `<couleur_fond>` (optionnel) : La couleur de fond du camembert, spécifiée en hexadécimal (par exemple, 0xFF0000 pour le rouge). Si aucune couleur de fond n'est spécifiée, le fond sera blanc par défaut.

Exemple d'utilisation :

```
./pie camembert.png 30 "Label 1" 50 "Label 2" 20 "Label 3" 0xFF0000
```

Cet exemple générera un camembert avec trois secteurs ayant respectivement 30%, 50% et 20% du cercle total, avec les étiquettes "Label 1", "Label 2" et "Label 3". Le camembert aura un fond rouge.

## Résultat

Une fois le programme exécuté, le camembert sera généré et sauvegardé dans le fichier PNG spécifié. Vous pouvez ouvrir le fichier PNG avec un logiciel d'affichage d'images pour visualiser le camembert.