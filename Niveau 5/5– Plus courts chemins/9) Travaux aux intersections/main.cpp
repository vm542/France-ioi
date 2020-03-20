#include <stdio.h>
#include <algorithm>

using namespace std;

const int MAX_NB_NOEUDS = 1000;
const int INFINI = 1000*1000*1000;

int     distances[MAX_NB_NOEUDS + 1][MAX_NB_NOEUDS + 1];
int     nbIntersections, nbSentiers;
int     fait[MAX_NB_NOEUDS + 1];

void    afficher(){
    for (int i = 1 ; i <= nbIntersections ; i++){
        for (int j = 1 ; j <= nbIntersections ; j++){
            if (distances[i][j] == INFINI)
                printf(". ");
            else
                printf("%d ", distances[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int     main(void){
    scanf("%d%d", &nbIntersections, &nbSentiers);
    for (int i = 1 ; i <= nbIntersections ; i++){
        for (int j = 1 ; j <= nbIntersections ; j++)
            distances[i][j] = INFINI;
        distances[i][i] = 0;
        printf("\n");
    }
    for (int i = 0 ; i < nbSentiers ; i++){
        int     depart, arrivee, longueur;
        scanf("%d%d%d", &depart, &arrivee, &longueur);
        distances[depart][arrivee] = longueur;
    }
    for (int i = 1 ; i <= nbIntersections ; i++){
        fait[i] = 1;
        for (int inter = 1 ; inter <= nbIntersections ; inter++)
            for (int depart = 1 ; depart <= nbIntersections ; depart++)
                for (int arrivee = 1 ; arrivee <= nbIntersections ; arrivee++){
                    if (distances[depart][arrivee] > distances[depart][inter] + distances[inter][arrivee] && fait[inter] == 1)
                        distances[depart][arrivee] =  distances[depart][inter] + distances[inter][arrivee];
                }
        afficher();
    }
    return (0);
}