#include <stdio.h>
#include <vector>

#define INDEFINI -1

using namespace std;

int     nbPlaques, plaques[6];
int     utilise[6];
int     nbValeurs = 0, valeurs[1000000];

int parcourir(int valeur, int profondeur){
    printf("%d ", valeur);
    if (valeur < 1000 && valeur >= 0)
        return (0);
    if (valeurs[valeur] == INDEFINI && profondeur == nbPlaques){
        valeurs[valeur] = valeur;
        nbValeurs++;
    }
    for (int i = 0 ; i < nbPlaques ; i++){
        if (utilise[i] == 0){
            utilise[i] = 1;
            parcourir(valeur + plaques[i], profondeur + 1);
            parcourir(valeur - plaques[i], profondeur + 1);
            parcourir(valeur * parcourir(plaques[i], profondeur + 1), profondeur + 1);
            if (valeur % plaques[i] == 0)
                parcourir(valeur / plaques[i], profondeur + 1);
            utilise[i] = 0;
        }
    }
    return (valeur);
}

int     main(void){
    for (int i = 0 ; i < 100000 ; i++)
        valeurs[i] = INDEFINI;
    scanf("%d", &nbPlaques);
    for (int i = 0 ; i < nbPlaques ; i++)
        scanf("%d", &plaques[i]);
    for (int i = 0 ; i < nbPlaques ; i++){
        utilise[i] = 1;
        parcourir(plaques[i], 0);
        utilise[i] = 0;
    }
    printf("%d", nbValeurs);
    return (0);
}