#include <iostream>
#include <math.h>

using namespace std;

int tailleTableau, nbRequetes, tailleArbre, tableau[1000000];

int   frere(int indice){
   if (indice % 2 == 0){
      return indice + 1;
   }
   return indice - 1;
}

int   parent(int indice){
   if (indice % 2 != 0){
      return (indice - 1) / 2;
   }
   return indice / 2;
}

int max(int i1, int i2){
   if (i1 >= i2){
      return i1;
   }
   return i2;
}

void  mettreAJour(int iCourant){
    int iFrere = frere(iCourant);
    int iParent = parent(iCourant);
    int aMettreAJour = 0;
    if (tableau[iCourant] >= tableau[iFrere]){
       aMettreAJour = 1;
       tableau[iParent] = tableau[iCourant];
    }
    else if (tableau[iFrere] >= tableau[iCourant]){
        aMettreAJour = 1;
        tableau[iParent] = tableau[iFrere];
    }
    if (iParent > 1 && aMettreAJour){
        mettreAJour(iParent);
    }
}

int main() {
    cin >> tailleTableau >> nbRequetes;
    tailleArbre = pow(2, tailleTableau);
    for (int i = 0 ; i < 1000000; i++){
        tableau[i] = -1;
    }
    for (int i = 0 ; i < nbRequetes ; i++){
        int ind, valeur;
        cin >> ind >> valeur;
        tableau[tailleArbre + ind] = valeur;
        mettreAJour(tailleArbre + ind);
        cout << tableau[1] << endl;
    }
}
