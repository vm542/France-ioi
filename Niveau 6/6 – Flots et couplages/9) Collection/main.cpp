#include <stdio.h>
#include <algorithm>

using namespace std;

struct  Info{
    int acheteur, vendeur, prix;
    Info(int acheteur, int vendeur, int prix){
        this->acheteur = acheteur;
        this->vendeur = vendeur;
        this->prix = prix;
    }
    Info(){}
};

int nbAcheteurs, nbObjets, nbInformations;
int interesse[100][100];
int achats[100], maxProfit = 0;
Info    informations[100000];

int     coupler(int iAcheteur, int *vu){
    for (int objet = 0 ; objet < 100 ; objet++){
        if (interesse[iAcheteur][objet] > 0){
            if (!vu[objet]){
                vu[objet] = 1;
                if (achats[objet] == -1 || coupler(achats[objet], vu)){
                    achats[objet] = iAcheteur;
                    return (1);
                }
            }
        }
    }
    return (0);
}

int main(void){
    scanf("%d%d%d", &nbAcheteurs, &nbObjets, &nbInformations);
    for (int i = 0 ; i < 100 ; i++)
        achats[i] = -1;
    for (int i = 0 ; i < nbInformations ; i++){
        int acheteur, objet, prix;
        scanf("%d%d%d", &acheteur, &objet, &prix);
        interesse[acheteur][objet] = prix;
        informations[i] = Info(acheteur, objet, prix);
    }
    int     aVendre;
    scanf("%d", &aVendre);
    for (int i = 0 ; i < aVendre ; i++){
        int    indice;
        scanf("%d", &indice);
        maxProfit += informations[indice].prix;
        for (int j = 0 ; j < 100 ; j++)
            interesse[informations[indice].acheteur][j] = 0;
    }
    int     m = -1;
    for (int i = 0 ; i < 100 ; i++)
        for (int j = 0 ; j < 100 ; j++)
            m = max(m, interesse[i][j]);
    printf("%d", maxProfit + m);
    return (0);
}