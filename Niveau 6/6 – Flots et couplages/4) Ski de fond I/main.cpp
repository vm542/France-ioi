#include <stdio.h>
#include <algorithm>
#include <vector>

#define MAX_NB_TUYAUX 500
#define MAX_NB_JONCTIONS 2500
#define MAX_CAPACITE 9999999

using namespace std;

int nbJonctions, nbTuyaux, nbBallades;
int jonctions[MAX_NB_JONCTIONS + 1][MAX_NB_JONCTIONS + 1];
int maxFlot = 0;
int visite[MAX_NB_JONCTIONS + 1];

vector<pair<int,int>>   chemin;

int existeChemin(int indice){
    visite[indice] = 1;
    if (indice == nbJonctions)
        return (1);
    for (int i = MAX_NB_JONCTIONS ; i >= 1 ; i--){
        if (jonctions[indice][i] > 0 && visite[i] == 0 && existeChemin(i)){
            chemin.push_back(make_pair(indice, i));
            return (1);
        }
    }
    return (0);
}

vector<int> chemins[MAX_NB_JONCTIONS + 1];
int     nbChemins = 0;

int main(void){
    scanf("%d%d%d", &nbJonctions, &nbTuyaux, &nbBallades);
    for (int i = 0 ; i < nbTuyaux ; i++){
        int jonctionA, jonctionB;
        scanf("%d%d", &jonctionA, &jonctionB);
        jonctions[jonctionA][jonctionB] = 1;
    }
    while (existeChemin(1)){
        for (int i = 1 ; i <= MAX_NB_JONCTIONS ; i++)
            visite[i] = 0;
        maxFlot++;
        chemins[nbChemins].push_back(chemin[0].second);
        for (unsigned int i = 0 ; i < chemin.size() ; i++){
            chemins[nbChemins].push_back(chemin[i].first);
            jonctions[chemin[i].first][chemin[i].second]--;
        }
        nbChemins++;
        chemin.erase(chemin.begin(), chemin.end());
    }
    for (int i = 0 ; i < nbBallades ; i++){
        printf("%d\n", (int)(chemins[i].size()));
        for (int j = chemins[i].size() - 1 ; j >= 0 ; j--)
            printf("%d\n", chemins[i][j]);
    }
    return (0);
}