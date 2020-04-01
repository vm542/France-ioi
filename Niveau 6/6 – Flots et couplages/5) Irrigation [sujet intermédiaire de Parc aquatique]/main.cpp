#include <stdio.h>
#include <algorithm>
#include <vector>

#define MAX_NB_TUYAUX 501
#define MAX_NB_JONCTIONS 2501
#define MAX_CAPACITE 999999999

using namespace std;

int nbJonctions, nbTuyaux;
int jonctions[MAX_NB_TUYAUX + 1][MAX_NB_TUYAUX + 1];
int maxFlot = 0, minFlot = MAX_CAPACITE;
int visite[MAX_NB_TUYAUX + 1], prevu = 0;
vector<pair<int,int>>   chemin;

int existeChemin(int indice){
    visite[indice] = 1;
    if (indice == nbJonctions)
        return (1);
    for (int i = MAX_NB_TUYAUX ; i >= 1 ; i--){
        if (jonctions[indice][i] > 0 && visite[i] == 0 && existeChemin(i)){
            chemin.push_back(make_pair(indice, i));
            minFlot = min(minFlot, jonctions[indice][i]);
            return (1);
        }
    }
    return (0);
}

int main(void){
    scanf("%d%d", &nbJonctions, &nbTuyaux);
    for (int i = 0 ; i < nbTuyaux ; i++){
        int jonctionA, jonctionB, capacite, prevision;
        scanf("%d%d%d%d", &jonctionA, &jonctionB, &capacite, &prevision);
        if (jonctionB == nbJonctions)
            prevu += prevision;
        jonctions[jonctionA][jonctionB] = capacite;
    }
    while (existeChemin(1)){
        maxFlot += minFlot;
        for (unsigned int i = 0 ; i < chemin.size() ; i++){
            jonctions[chemin[i].first][chemin[i].second] -= minFlot;
            jonctions[chemin[i].second][chemin[i].first] += minFlot;
        }
        minFlot = MAX_CAPACITE;
        for (int i = 1 ; i <= MAX_NB_TUYAUX ; i++)
            visite[i] = 0;
        chemin.erase(chemin.begin(), chemin.end());
    }
    if (maxFlot == prevu)
        printf("OUI");
    else
        printf("NON");
    return (0);
}