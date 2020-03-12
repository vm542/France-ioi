#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>

using namespace std;

class   Chemin{
    public:
        int     voisin, longueur;
        Chemin(int v, int l){
            voisin = v;
            longueur = l;
        }
        Chemin(){}
};

class   Noeud{
    public:
        vector<Chemin>  voisins;
        int     valeurMin = -1;
        Noeud(){}
};

Noeud   intersections[100001];

int     nbIntersections, nbChemins, numSortie;
int     distances[100001][2];

int     cmp(const void *a, const void *b) {
    return ((const int *)a)[0] - ((const int *)b)[0];
}

int     main(void){
    scanf("%d%d%d", &nbIntersections, &nbChemins, &numSortie);
    for (int i = 0 ; i < nbChemins ; i++){
        int     num1, num2, longueur;
        scanf("%d%d%d", &num1, &num2, &longueur);
        intersections[num1].voisins.push_back(Chemin(num2, longueur));
        intersections[num2].voisins.push_back(Chemin(num1, longueur));
    }
    queue<Noeud>  fileAttente;
    fileAttente.push(intersections[numSortie]);
    while (!fileAttente.empty()){
        Noeud   current = fileAttente.front();
        fileAttente.pop();
        int     currValeur = current.valeurMin;
        for (unsigned int i = 0 ; i < current.voisins.size() ; i++){
            int     aAjouter = current.voisins.at(i).longueur;
            int     iVoisin = current.voisins.at(i).voisin;
            if (intersections[iVoisin].valeurMin == -1 || currValeur + aAjouter < intersections[iVoisin].valeurMin){
                intersections[iVoisin].valeurMin = currValeur + aAjouter;
                distances[iVoisin][0] = intersections[iVoisin].valeurMin + 1;
                distances[iVoisin][1] = iVoisin;
                fileAttente.push(intersections[iVoisin]);
            }
        }
    }
    qsort(distances, nbIntersections + 1, 2 * sizeof(int), cmp);
    printf("%d %d\n", 0, numSortie);
    for (int i = 1 ; i <= nbIntersections ; i++)
        if (distances[i][1] != numSortie)
            printf("%d %d\n", distances[i][0], distances[i][1]);
    return (0);
}