#include <iostream>

using namespace std;

int   nbEntiers;
int   entiers[100000];

void  tri(int pivot, int array[], int sizeArray){
   if (sizeArray <= 1)
      return;
   int   iGauche = 0;
   int   iDroite = 0;
   int      gauche[100000];
   int   droite[100000];
   for (int i = 0 ; i < sizeArray ; i++){
      if (array[i] <= array[pivot] && i != pivot){
         gauche[iGauche] = array[i];
         iGauche++;
      }
      else if (array[i] > array[pivot]){
         droite[iDroite] = array[i];
         iDroite++;
      }
   }
   if (iGauche == 1){
      cout << gauche[0] << " ";
   }
   else{
      tri(iGauche / 2, gauche, iGauche);
   }
   cout << array[pivot] << " ";
   if (iDroite == 1){
      cout << droite[0] << " ";
   }
   else{
      tri(iDroite / 2, droite, iDroite);
   }
}

int   main(void){
   cin >> nbEntiers;
   for (int i = 0 ; i < nbEntiers ; i++)
      cin >> entiers[i];
   if (nbEntiers == 1){
      cout << entiers[0];
   }
   tri(nbEntiers / 2, entiers, nbEntiers);
   return (0);
}
