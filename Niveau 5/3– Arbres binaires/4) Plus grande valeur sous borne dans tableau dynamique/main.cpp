#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int     taille, nbRequetes;
int     tailleArbre = 1, profArbre = 1;
int     valeurs[1000001];
int     arbre[200001];

void     mettreAJour(int indice){
    if (indice < 1)
        return;
    arbre[indice] = max(arbre[indice * 2], arbre[indice * 2 + 1]);
    mettreAJour(indice / 2);
}

int     trouver(int indice, int aTrouver, int profondeur){
    int     min = indice;
    for (int i = 0 ; i < profArbre - profondeur ; i++)
        min *= 2;
    if (!arbre[indice] || min > aTrouver)
        return (-1);
    if (indice >= tailleArbre && indice <= aTrouver)
        return (indice - tailleArbre);
    if (arbre[indice * 2 + 1] == 1){
        int     val = trouver(indice * 2 + 1, aTrouver, profondeur + 1);
        if (val != -1)
            return (val);
    }
    return (trouver(indice * 2, aTrouver, profondeur + 1));
}

int     main(void){
    scanf("%d%d", &taille, &nbRequetes);
    for (int i = 0 ; i < taille ; i++)
        valeurs[i] = -1;
    while (tailleArbre < taille){
        tailleArbre *= 2;
        profArbre++;
    }
    for (int i = 0 ; i < nbRequetes ; i++){
        char requete;
        int     indice, valeur;
        scanf(" %c%d", &requete, &indice);
        if (requete == 'M'){
            scanf("%d", &valeur);arbre[tailleArbre + indice] = valeur;
            mettreAJour((tailleArbre + indice) / 2);
        }
        else{
            printf("%d\n", trouver(1, tailleArbre + indice, 1));
        }
    }
    return (0);
}