#include <stdio.h>
#include <vector>

#define INDEFINI -1
#define MAX_VALEURS 1000

using namespace std;

int nbValeurs = 0;
int valeurs[MAX_VALEURS];
int     it = 0;

void    parcourir(vector<int>   plaques){
    it++;
    for (unsigned int i = 0 ; i < plaques.size() ; i++){
        if (plaques[i] >= 0 && plaques[i] < 1000){
            if (valeurs[plaques[i]] == INDEFINI){
                valeurs[plaques[i]] = plaques[i];
                nbValeurs++;
            }
        }
        int temp = plaques[i];
        vector<int> plaques3 = plaques;
        plaques3.erase(plaques3.begin() + i);
        if (temp != 0){
            for (unsigned int j = 0 ; j < plaques.size() - 1 ; j++){
                vector<int> plaques2 = plaques3;
                plaques2[j] += temp;
                parcourir(plaques2);
                plaques2[j] -= temp;
                plaques2[j] *= temp;
                parcourir(plaques2);
                plaques2[j] /= temp;
                if (plaques2[j] - temp >= 0){
                    plaques2[j] -= temp;
                    parcourir(plaques2);
                }
                plaques2[j] += temp;
                if (temp != 0 && plaques2[j] % temp == 0){
                    plaques2[j] /= temp;
                    parcourir(plaques2);
                }
            }
        }
    }
}

int main(void){
    for (int i = 0 ; i < MAX_VALEURS ; i++)
        valeurs[i] = INDEFINI;
    int nbPlaques;
    scanf("%d", &nbPlaques);
    vector<int> plaques;
    for (int i = 0 ; i < nbPlaques ; i++){
        int plaque;
        scanf("%d", &plaque);
        plaques.push_back(plaque);
    }
    parcourir(plaques);
    //printf("%d ", it);
    printf("%d", nbValeurs);
    //for (int i = 0 ; i < 1000 ; i++)
        //if (valeurs[i] == INDEFINI)
            //printf("%d ", i);
    return (0);
}