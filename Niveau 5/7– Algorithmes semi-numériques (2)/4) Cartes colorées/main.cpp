#include "colors.h"
#include <stdio.h>

using namespace std;

int    quantites[13];

void   parcourir(int couleur, int cartes[], int taille){
   for (int i = couleur ; i <= nbColors() ; i++){
      cartes[taille - 1] = i;
      quantites[taille] += question(cartes, taille);
      parcourir(i + 1, cartes, taille + 1);
   }
}

int     main(void){
    int   cartes[13] = {1};
    parcourir(1, cartes, 1);
    for (int i = 12 ; i >= 1 ; i--)
       quantites[i] -= quantites[i + 1];
    printf("%d", quantites[1]);
    return (0);
}