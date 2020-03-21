#include <stdio.h>
#include <algorithm>
#include <vector>

#define MAX_NB_TUYAUX 500
#define MAX_NB_JONCTIONS 2500
#define MAX_CAPACITE 999999

using namespace std;

int nbJonctions, nbTuyaux;
int jonctions[MAX_NB_JONCTIONS + 1][MAX_NB_JONCTIONS + 1];
int maxFlot = 0, minFlot = MAX_CAPACITE;
int visite[MAX_NB_JONCTIONS + 1];

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
        int jonctionA, jonctionB, capacite;
        scanf("%d%d%d", &jonctionA, &jonctionB, &capacite);
        jonctions[jonctionA][jonctionB] = capacite;
    }
    while (existeChemin(1)){
        maxFlot += minFlot;
        for (unsigned int i = 0 ; i < chemin.size() ; i++)
            jonctions[chemin[i].first][chemin[i].second] -= minFlot;
        minFlot = MAX_CAPACITE;
        for (int i = 1 ; i <= MAX_NB_TUYAUX ; i++)
            visite[i] = 0;
        chemin.erase(chemin.begin(), chemin.end());
    }
    printf("%d", maxFlot);
    return (0);
}