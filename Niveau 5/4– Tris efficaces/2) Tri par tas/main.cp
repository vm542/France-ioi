#include <iostream>
#include <algorithm>

using namespace std;

int   nbEntiers;
int   arbre[1000002], arbreTrie[1000002];
int   nbElements;

int      parent(int i){
   if (i % 2 == 0)
      return (i / 2);
   return ((i - 1) / 2);
}

int   voisin(int i){
   if (i % 2 == 0)
      return (i + 1);
   return (i - 1);
}

void  interchanger(int i1, int i2, int type){
   if (type == 1){
      int   temp = arbre[i1];
      arbre[i1] = arbre[i2];
      arbre[i2] = temp;
   }
   else if (type == 0){
      arbreTrie[nbElements] = arbre[i1];
      arbre[i1] = arbre[i2];
      arbre[i2] = -100000001;
      nbElements--;
   }
}

void  afficher(){
   for (int i = 1 ; i <= nbEntiers ; i++){
      cout << arbre[i] << " ";
   }
   cout << endl;
}

void  mettreAJour(int i){
   if (i >= nbElements)
      return;
   int   enfant1 = arbre[i * 2];
   int   enfant2 = arbre[i * 2 + 1];
   if (max(enfant1, enfant2) == enfant1){
      if (enfant1 > arbre[i]){
         interchanger(i * 2, i, 1);
         mettreAJour(i * 2);
         mettreAJour(i * 2 + 1);
      }
   }
   else if (max(enfant1, enfant2) == enfant2){
      if (enfant2 > arbre[i]){
         interchanger(i * 2 + 1, i, 1);
         mettreAJour(i * 2 + 1);
         mettreAJour(i * 2);
      }
   }
}

void  heap(int i){
   if (i <= 1)
      return;
   int   par = arbre[parent(i)];
   int   vois = arbre[voisin(i)];
   int   courant = arbre[i];
   if (max(courant, vois) == courant)
      if (courant > par)
         interchanger(i, parent(i), 1);
   else if (max(courant, vois) == vois)
      if (vois > par)
         interchanger(voisin(i), parent(i), 1);
   heap(parent(i));
}

int   main(void){
   for (int i = 0 ; i <= 1000001 ; i++){
      arbre[i] = -100000001;
   }
   cin >> nbEntiers;
   nbElements = nbEntiers;
   for (int i = 1 ; i <= nbEntiers ; i++){
      cin >> arbre[i];
      if (arbre[i] > arbre[parent(i)] && i != 1){
         heap(i);
      }
   }
   while(nbElements > 0){
      interchanger(1, nbElements, 0);
      mettreAJour(1);
   }
   for (int i = 1 ; i <= nbEntiers ; i++){
      cout << arbreTrie[i] << " ";
   }
   return (0);
}
