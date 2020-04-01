#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int   MOINS_INFINI = -10000000;
const int   INCONNU = MOINS_INFINI + 1;
const int   MAX_LIN = 2000;
const int   MAX_COL = 50;

int     nbLin, nbCol, colDepart;
int     jeu[MAX_LIN][MAX_COL];
int     dynMeilleurScore[MAX_LIN][MAX_COL];
vector<int>     sequence;

int     meilleurScore(int lin, int col){
    if (lin < 0)
        return 0;
    if (col < 0 || col >= nbCol)
        return MOINS_INFINI;
    if (dynMeilleurScore[lin][col] == INCONNU){
        int     meilleur = MOINS_INFINI;
        int     meilleurDep;
        int     deps[3] = {1, -1, 0};
        for(int dep = 0 ; dep < 3 ; dep++){
            int     score = meilleurScore(lin - 1, col + deps[dep]);
            if (meilleur < score){
                meilleur = score;
                meilleurDep = deps[dep];
            }
        }
        dynMeilleurScore[lin][col] = jeu[lin][col] + meilleur;
    }
    return dynMeilleurScore[lin][col];
}

int     main(void){
    scanf("%d %d %d", &nbLin, &nbCol, &colDepart);
    for(int lin = 0; lin < nbLin; lin++){
        for(int col = 0; col < nbCol; col++){
            scanf("%d", &jeu[lin][col]);
            dynMeilleurScore[lin][col] = INCONNU;
        }
    }
    int     score = meilleurScore(nbLin-1, colDepart);
    for (int i = 0 ; i < nbCol ; i++){
        dynMeilleurScore[nbLin - 1][i] = score;
    }
    int     currColonne = colDepart;
    for (int i = nbLin - 1 ; i >= 0 ; i--){
        int     deps[3] = {1, -1, 0};
        int     meilleurDep;
        for (int dep = 0 ; dep < 3 ; dep++)
            if (currColonne + deps[dep] >= 0 && currColonne + deps[dep] < nbCol)
                if (dynMeilleurScore[i][currColonne] - jeu[i][currColonne] == dynMeilleurScore[i - 1][currColonne + deps[dep]])
                    meilleurDep = deps[dep];
        currColonne += meilleurDep;
        sequence.push_back(meilleurDep);
    }
    for (int i = 0 ; i < sequence.size() - 1 ; i++)
        printf("%d ", sequence.at(i));
    return 0;
}