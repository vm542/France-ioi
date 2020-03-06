#include <iostream>

using namespace std;

int     nbElements, elements[1000];

void    afficher(int taille, int *tab){
    for (int i = 0 ; i < taille ; i++)
        cout << tab[i] << " ";
    cout << endl;
}

int     *triFusion(int taille, int *tab){
    if (taille <= 1)
        return (tab);
    int     *resultat = new int[taille];
    int     tailleGauche = taille / 2, gauche[tailleGauche], iGauche = 0;
    int     tailleDroite = taille - tailleGauche, droite[tailleDroite], iDroite = 0;
    for (int i = 0 ; i < tailleGauche ; i++)
        gauche[i] = tab[i];
    for (int i = 0 ; i < tailleDroite ; i++)
        droite[i] = tab[tailleGauche + i];
    int     *trieGauche = triFusion(tailleGauche, gauche);
    int     *trieDroite = triFusion(tailleDroite, droite);
    for (int i = 0 ; i < taille ; i++){
        if (iGauche < tailleGauche && iDroite < tailleDroite){
            if (trieGauche[iGauche] < trieDroite[iDroite])
                resultat[i] = trieGauche[iGauche++];
            else
                resultat[i] = trieDroite[iDroite++];
        }
        else if (iGauche < tailleGauche)
            resultat[i] = trieGauche[iGauche++];
        else if (iDroite < tailleDroite)
            resultat[i] = trieDroite[iDroite++];
    }
    return (resultat);
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