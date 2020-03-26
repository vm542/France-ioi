#include <stdio.h>
#include <vector>

#define MAX_NB_SENTIERS 100001
#define MAX_NB_INTERSECTIONS 10001

using namespace std;

int nbIntersections, nbSentiers;
vector<int> intersections[MAX_NB_SENTIERS];
vector<int> intersectionsInverse[MAX_NB_SENTIERS];
int visite[MAX_NB_SENTIERS];
int mere, nbMeres = 0;

void    initialiser(){
    for (int i = 0 ; i < MAX_NB_SENTIERS ; i++)
        visite[i] = 0;
}

void    parcourir(int iInter){
    visite[iInter] = 1;
    for (unsigned int i = 0 ; i < intersections[iInter].size() ; i++)
        if (!visite[intersections[iInter][i]])
            parcourir(intersections[iInter][i]);
}

int trouverMere(){
    int     dernierTrouve = 0;
    for (int i = 1 ; i <= nbIntersections ; i++)
        if (!visite[i]){
            parcourir(i);
            dernierTrouve = i;
        }
    initialiser();
    parcourir(dernierTrouve);
    for (int i = 1 ; i <= nbIntersections ; i++)
        if (!visite[i])
            return (0);
    return (dernierTrouve);
}

void    parcourirInverse(int iInter){
    visite[iInter] = 1;
    for (unsigned int i = 0 ; i < intersectionsInverse[iInter].size() ; i++)
        if (visite[intersectionsInverse[iInter][i]] == 0)
            parcourirInverse(intersectionsInverse[iInter][i]);
}

int main(void){
    scanf("%d%d", &nbIntersections, &nbSentiers);
    for (int i = 0 ; i < nbSentiers ; i++){
        int debut, arrivee;
        scanf("%d%d", &debut, &arrivee);
        intersections[debut].push_back(arrivee);
        intersectionsInverse[arrivee].push_back(debut);
    }
    mere = trouverMere();
    initialiser();
    if (mere != 0){
        parcourirInverse(mere);
        for (int i = 1 ; i <= nbIntersections ; i++)
            if (visite[i] == 1)
                nbMeres++;
    }
    printf("%d\n", nbMeres);
    for (int i = 1 ; i <= nbIntersections ; i++)
        if (visite[i] == 1)
            printf("%d ", i);
    return (0);
}