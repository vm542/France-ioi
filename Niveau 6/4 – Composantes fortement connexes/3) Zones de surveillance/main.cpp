#include <stdio.h>
#include <vector>
#include <deque>

#define MAX_NB_INTERSECTIONS 1001
#define MAX_NB_SENTIERS 10001

using namespace std;

int nbIntersections, nbSentiers;
vector<int> intersections[MAX_NB_INTERSECTIONS], intersectionsInverse[MAX_NB_INTERSECTIONS];
deque<int>  derniersTermines;
int visite[MAX_NB_INTERSECTIONS];

void    initialiser(){
    for (int i = 1 ; i <= nbIntersections ; i++)
        visite[i] = 0;
}

void    parcourir(int iInter){
    visite[iInter] = 1;
    for (unsigned int i = 0 ; i < intersections[iInter].size() ; i++)
        if (visite[intersections[iInter][i]] == 0)
            parcourir(intersections[iInter][i]);
    derniersTermines.push_front(iInter);
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
        int depart, arrivee;
        scanf("%d%d", &depart, &arrivee);
        intersections[depart].push_back(arrivee);
        intersectionsInverse[arrivee].push_back(depart);
    }
    parcourir(1);
    initialiser();
    int     nbComposantes = 0;
    while (!derniersTermines.empty()){
        int current = derniersTermines.front();
        derniersTermines.pop_front();
        if (visite[current] == 0){
            parcourirInverse(current);
            nbComposantes++;
        }
    }
    printf("%d", nbComposantes);
    return (0);
}