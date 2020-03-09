#include <stdio.h>
#include <vector>

using namespace std;

int     nbCartes, cartes[10001], visite[10001], nbCycles = 0;
vector<int> cycles[10001];

void    parcourir(int i, int i2){
    cycles[nbCycles].push_back(i);
    visite[i] = 1;
    if (!visite[cartes[i]])
        parcourir(cartes[i], i2 + 1);
}

int     main() {
    scanf("%d", &nbCartes);
    for (int i = 1 ; i <= nbCartes ; i++)
        scanf("%d", &cartes[i]);
    for (int i = 1 ; i <= nbCartes ; i++)
        if (!visite[i]){
            parcourir(cartes[i], 0);
            nbCycles++;
        }
    printf("%d\n", nbCycles);
    for (int i = 0 ; i < nbCycles ; i++){
        for (int j = 0 ; j < cycles[i].size() ; j++)
            printf("%d ", cycles[i].at(j));
        printf("\n");
    }
}