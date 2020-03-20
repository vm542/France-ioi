#include <stdio.h>
#include <vector>
#include <algorithm>

#define MAX_NB_INTER 100000

using namespace std;

struct  Intersection{
    vector<int> voisins;
    int     atteint = 1, visite = 0;
};

int nbIntersections, nbChemins;
int nbPossible = 0, possible[MAX_NB_INTER + 1];
Intersection    intersections[MAX_NB_INTER + 1];

void    parcourir(int indice){
    intersections[indice].visite = 1;
    nbParcouru++;
    for (unsigned int i = 0 ; i < intersections[indice].voisins.size() ; i++){
        if (!intersections[intersections[indice].voisins[i]].visite){
            parcourir(intersections[indice].voisins[i]);
        }
    }
}

int main(void){
    scanf("%d%d", &nbIntersections, &nbChemins);
    for (int i = 0 ; i < nbChemins ; i++){
        int depart, arrivee;
        scanf("%d%d", &depart, &arrivee);
        intersections[depart].voisins.push_back(arrivee);
    }
    for (int i = 1 ; i <= nbIntersections ; i++){
        for (int j = 1 ; j <= nbIntersections ; j++)
            intersections[j].visite = 0;
        nbParcouru = 0;
        parcourir(i);
        if (nbParcouru == nbIntersections){
            intersections[i].possible = 1;
            possible[nbPossible] = i;
            nbPossible++;
        }
    }
    sort(possible, possible + nbPossible);
    printf("%d\n", nbPossible);
    for (int i = 0 ; i < nbPossible ; i++)
        printf("%d ", possible[i]);
    return (0);
}