#include <stdio.h>
#include <algorithm>

#define MAX_LIG 20001

using namespace std;

struct  Case{
    int bonus, colonne;
    Case(int bonus, int colonne){
        this->bonus = bonus;
        this->colonne = colonne;
    }
    Case(){}
};

int nbLignes, nbColonnes, colDepart;
int deps[3] = {0, -1, 1};

Case    jeu[MAX_LIG];

#define GAUCHE -1
#define CENTRE 0
#define DROITE 1

int parcourir(int ligne, int iCol, int score, int cote = CENTRE){
    if (ligne == 0)
        return (score);
    int maxi = -1;
    if (cote == CENTRE){
        int aAjouter = 0;
        if (jeu[ligne - 1].colonne == iCol )
            aAjouter = jeu[ligne - 1].bonus;
        maxi = parcourir(ligne - 1, iCol, score + aAjouter, 0);
    }
    else if (cote == GAUCHE){
        for (int i = 0 ; i < 3 ; i++){
            if (deps[i] != 1 && iCol + deps[i] >= 0 && iCol + deps[i] < nbColonnes){
                int aAjouter = 0;
                if (jeu[ligne - 1].colonne == iCol + deps[i])
                    aAjouter = jeu[ligne - 1].bonus;
                if (maxi < parcourir(ligne - 1, iCol + deps[i], score + aAjouter, deps[i]))
                    maxi = parcourir(ligne - 1, iCol + deps[i], score + aAjouter, deps[i]);
            }
        }
    }
    else if (cote == DROITE){
        for (int i = 0 ; i < 3 ; i++){
            if (deps[i] != -1 && iCol + deps[i] >= 0 && iCol + deps[i] < nbColonnes){
                int aAjouter = 0;
                if (jeu[ligne - 1].colonne == iCol + deps[i])
                    aAjouter = jeu[ligne - 1].bonus;
                if (maxi < parcourir(ligne - 1, iCol + deps[i], score + aAjouter, deps[i]))
                    maxi = parcourir(ligne - 1, iCol + deps[i], score + aAjouter, deps[i]);
            }
        }
    }
    /*else{
        for (int i = 0 ; i < 3 ; i++){
            if (iCol + deps[i] >= 0 && iCol + deps[i] < nbColonnes){
                int aAjouter = 0;
                if (jeu[ligne - 1].colonne == iCol + deps[i]){
                    aAjouter = jeu[ligne - 1].bonus;
                }
                if (maxi < parcourir(ligne - 1, iCol + deps[i], score + aAjouter, deps[i]))
                    maxi = parcourir(ligne - 1, iCol + deps[i], score + aAjouter, deps[i]);
            }
        }
    }*/
    return (maxi);
}

int main(void){
    scanf("%d%d%d", &nbLignes, &nbColonnes, &colDepart);
    for (int i = 0 ; i < nbLignes - 1 ; i++)
        scanf("%d%d", &jeu[i].colonne, &jeu[i].bonus);
    jeu[nbLignes - 1] = Case(0, colDepart);
    printf("%d", parcourir(nbLignes - 1, colDepart, 0, 4));
    int maxi = -1;
    for (int i = 0 ; i < 3 ; i++){
        printf("%d", parcourir(nbLignes - 1, colDepart, 0, deps[i]));
    }
    return (0);
}