#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

const   int INDEFINI = -2147483647;

class   Sentier{
    public:
        int     debut, arrivee, points;
        Sentier(int d, int a, int l){
            debut = d;
            arrivee = a;
            points = l;
        }
        Sentier(){}
};

class   Intersection{
    public:
        int     indice;
        vector<Sentier> voisins;
        Intersection(){}
};

Intersection     intersections[1001];
int     tpsParcours[1001][500];

int     nbIntersections, nbSentiers, iDepart, tpsDonne;

int     calculerScore(int     iInter, int tpsRestant, int currScore){
    if (tpsRestant == 0)
        return (currScore);
    int     max = INDEFINI;
    for (int i = 0 ; i < intersections[iInter].voisins.size() ; i++){
        int     iVoisin = intersections[iInter].voisins.at(i).arrivee;
        int     nbPoints = intersections[iInter].voisins.at(i).points;
        int     calcul = currScore + nbPoints;
        if (tpsParcours[iVoisin][tpsRestant - 1] == INDEFINI)
            tpsParcours[iVoisin][tpsRestant - 1] = calculerScore(iVoisin, tpsRestant - 1, 0);
        if (tpsParcours[iVoisin][tpsRestant - 1] + calcul > max)
            max = tpsParcours[iVoisin][tpsRestant - 1] + calcul;
    }
    if (max == INDEFINI)
        return (currScore);
    return (max);
}

int     main(void){
    scanf("%d%d%d%d", &nbIntersections, &nbSentiers, &iDepart, &tpsDonne);
    for (int i = 1 ; i <= nbIntersections ; i++)
        for (int j = 0 ; j <= 500 ; j++)
            tpsParcours[i][j] = INDEFINI;
    for (int i = 0 ; i < nbSentiers ; i++){
        int     depart, arrivee, points;
        scanf("%d%d%d", &depart, &arrivee, &points);
        intersections[depart].voisins.push_back(Sentier(depart, arrivee, points));
    }
    for (int i = 1 ; i <= nbIntersections ; i++)
        intersections[i].voisins.push_back(Sentier(i, i, 0));
    printf("%d ", calculerScore(iDepart, tpsDonne, 0));
    return (0);
}