#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>

#define INDEFINI -1
#define MAX_VALEURS 1000

using namespace std;

int nbValeurs = 0;
int valeurs[MAX_VALEURS];
set<vector<int>> dejaFait;


vector<int> initialisation(){
    int nbPlaques;
    vector<int> plaques;
    scanf("%d", &nbPlaques);
    for (int i = 0 ; i < MAX_VALEURS ; i++)
        valeurs[i] = INDEFINI;
    for (int i = 0 ; i < nbPlaques ; i++){
        int plaque;
        scanf("%d", &plaque);
        plaques.push_back(plaque);
    }
    return (plaques);
}

int valide(int  plaque){
    if (plaque >= 0 && plaque < MAX_VALEURS)
        return (1);
    return (0);
}

int dejaUtilise(vector<int> plaques){
    for (int i = 0 ; i < (int)plaques.size() ; i++)
        if (valide(plaques[i]) && valeurs[plaques[i]] == INDEFINI){
            valeurs[plaques[i]] = 1;
            nbValeurs++;
        }
    if (dejaFait.count(plaques) > 0)
        return (1);
    return (0);
}

void    parcourir(vector<int>   plaques){
    sort(plaques.begin(), plaques.end());
    if (dejaUtilise(plaques) == 1){
        return;
    }
    dejaFait.insert(plaques);
    for (int i = 0 ; i < (int)plaques.size() ; i++){
        int plaque = plaques[i];
        for (int j = 0 ; j < (int)plaques.size() ; j++){
            vector<int> nouvPlaques = plaques;
            nouvPlaques.erase(nouvPlaques.begin() + i);
            int valeur = nouvPlaques[j];
            nouvPlaques[j] = plaque + valeur;
            parcourir(nouvPlaques);
            nouvPlaques[j] = plaque * valeur;
            parcourir(nouvPlaques);
            if (plaque - valeur >= 0){
                nouvPlaques[j] = plaque - valeur;
                parcourir(nouvPlaques);
            }
            if (valeur != 0 && plaque % valeur == 0){
                nouvPlaques[j] = plaque / valeur;
                parcourir(nouvPlaques);
            }
        }
    }
}

int main(void){
    vector<int> plaques = initialisation();
    parcourir(plaques);
    printf("%d\n", nbValeurs);
    return (0);
}