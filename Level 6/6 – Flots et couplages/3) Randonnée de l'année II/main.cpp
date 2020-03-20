#include <stdio.h>
#include <vector>

#define INDEFINI -1
#define MAX_NB 10000

using namespace std;

int     nbInformations, nbPersonnes, nbVelos;

vector<int> personnes[MAX_NB];
int     attributions[MAX_NB], maxAttributions = 0;

int     trouverTele(int iPersonne, int *vu){
    for (unsigned int i = 0 ; i < personnes[iPersonne].size() ; i++){
        int     iVelo = personnes[iPersonne][i];
        if (!vu[iVelo]){
            vu[iVelo] = 1;
            if (attributions[iVelo] == -1 || trouverTele(attributions[iVelo], vu)){
                attributions[iVelo] = iPersonne;
                return (1);
            }
        }
    }
    return (0);
}

int     main(void){
    for (int i = 0 ; i < MAX_NB ; i++)
        attributions[i] = -1;
    scanf("%d%d%d", &nbPersonnes, &nbVelos, &nbInformations);
    for (int i = 0 ; i < nbInformations ; i++){
        int     personne, velo;
        scanf("%d%d", &personne, &velo);
        personnes[personne].push_back(velo);
    }
    for (int i = 0 ; i < nbPersonnes ; i++){
        int     vu[MAX_NB];
        for (int j = 0 ; j < MAX_NB ; j++)
            vu[j] = 0;
        maxAttributions += trouverTele(i, vu);
    }
    printf("%d", maxAttributions);
    return (0);
}