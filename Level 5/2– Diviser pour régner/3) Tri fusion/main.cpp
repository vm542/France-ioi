#include <iostream>

using namespace std;

int     nbElements, elements[1000];

int     *triFusion(int taille, int *tab){
    if (taille == 1)
        return (tab);
    int     resultat[taille];
    int     tailleGauche = taille / 2, gauche[tailleGauche], iGauche = 0;
    int     tailleDroite = taille - tailleGauche, droite[tailleDroite], iDroite = 0;
    for (int i = 0 ; i < tailleGauche ; i++)
        gauche[i] = tab[i];
    for (int i = 0 ; i < tailleDroite ; i++)
        droite[i] = tab[tailleGauche + i];
    int     *trieGauche = triFusion(tailleGauche, gauche);
    int     *trieDroite = triFusion(tailleDroite, droite);
    for (int i = 0 ; i < taille ; i++){
        if (iGauche < tailleGauche && gauche[iGauche] <= droite[iDroite])
            resultat[i] = gauche[iGauche++];
        else if (iDroite < tailleDroite && droite[iDroite] <= gauche[iGauche])
            resultat[i] = droite[iDroite++];
    }
    int     *valeurRetour = resultat;
    return (valeurRetour);
}

int     main(void){
    cin >> nbElements;
    for (int i = 0 ; i < nbElements ; i++)
        cin >> elements[i];
    int     *elementsTries = triFusion(nbElements, elements);
    for (int i = 0 ; i < nbElements ; i++)
        cout << elementsTries[i] << " ";
    return (0);
}

/*

5
7 3 0 10 2

*/