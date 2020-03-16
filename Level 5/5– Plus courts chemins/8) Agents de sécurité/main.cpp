#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

class   Sentier{
    public:
        int     debut, arrivee, longueur;
        Sentier(int d, int a, int l){
            debut = d;
            arrivee = a;
            longueur = l;
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
int     nbIntersections, nbSentiers;
int     distances[1001][1001];

void    calculer(int indice){
    queue<int>  fileAttente;
    fileAttente.push(indice);
    while (!fileAttente.empty()){
        int     current = fileAttente.front();
        fileAttente.pop();
        for (unsigned int i = 0 ; i < intersections[current].voisins.size() ; i++){
            int     iVoisin = intersections[current].voisins.at(i).arrivee;
            int     longueur = intersections[current].voisins.at(i).longueur;
            if (distances[indice][iVoisin] == -1 || longueur + distances[indice][current] < distances[indice][iVoisin]){
                fileAttente.push(iVoisin);
                distances[indice][iVoisin] = longueur + distances[indice][current];
                distances[iVoisin][indice] = longueur + distances[indice][current];
            }
        }
    }
}

int     main(void){
    scanf("%d%d", &nbIntersections, &nbSentiers);
    for (int i = 1 ; i <= nbIntersections ; i++)
        for (int j = 1 ; j <= nbIntersections ; j++)
            distances[i][j] = -1;
    for (int i = 0 ; i < nbSentiers ; i++){
        int     depart, arrivee, longueur;
        scanf("%d%d%d", &depart, &arrivee, &longueur);
        intersections[depart].voisins.push_back(Sentier(depart, arrivee, longueur));
        intersections[arrivee].voisins.push_back(Sentier(arrivee, depart, longueur));
    }
    for (int i = 1 ; i <= nbIntersections ; i++){
        calculer(i);
        for (int j = 1 ; j <= nbIntersections ; j++){
            if (i == j)
                printf("%d ", 0);
            else
                printf("%d ", distances[i][j] + 1);
        }
        printf("\n");
    }
    return (0);
}