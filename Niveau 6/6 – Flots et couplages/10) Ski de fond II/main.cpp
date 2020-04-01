#include <stdio.h>
#include <algorithm>
#include <vector>

#define MAX_NB_TUYAUX 500
#define MAX_NB_JONCTIONS 2500
#define MAX_CAPACITE 9999999

using namespace std;

struct  Jonction{
    int valeur, penibilite;
};

int nbJonctions, nbTuyaux, nbBallades;
Jonction    jonctions[MAX_NB_JONCTIONS + 1][MAX_NB_JONCTIONS + 1];
int visite[MAX_NB_JONCTIONS + 1], nbChemins = 0;
vector<pair<int,int>>   chemin;
int penibilites[MAX_NB_JONCTIONS + 1];
int penibilite = 0;

int existeChemin(int indice){
    visite[indice] = 1;
    if (indice == nbJonctions)
        return (1);
    for (int i = MAX_NB_JONCTIONS ; i >= 1 ; i--)
        if (jonctions[indice][i].valeur > 0 && visite[i] == 0 && existeChemin(i)){
            penibilite += jonctions[indice][i].penibilite;
            chemin.push_back(make_pair(indice, i));
            return (1);
        }
    return (0);
}

int main(void){
    scanf("%d%d%d", &nbJonctions, &nbTuyaux, &nbBallades);
    for (int i = 0 ; i < nbTuyaux ; i++){
        int jonctionA, jonctionB, indice;
        scanf("%d%d%d", &jonctionA, &jonctionB, &indice);
        jonctions[jonctionA][jonctionB].valeur = 1;
        jonctions[jonctionA][jonctionB].penibilite = indice;
    }
    while (existeChemin(1)){
        for (int i = 1 ; i <= MAX_NB_JONCTIONS ; i++)
            visite[i] = 0;
        penibilites[nbChemins] = penibilite;
        penibilite = 0;
        for (unsigned int i = 0 ; i < chemin.size() ; i++)
            jonctions[chemin[i].first][chemin[i].second].valeur--;
        nbChemins++;
        chemin.erase(chemin.begin(), chemin.end());
    }
    int total = 0;
    sort(penibilites, penibilites + nbChemins);
    for (int i = 0 ; i < nbBallades ; i++)
        total += penibilites[i];
    printf("%d", total);
    return (0);
}