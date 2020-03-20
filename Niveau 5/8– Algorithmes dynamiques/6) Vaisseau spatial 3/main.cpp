#include <stdio.h>
#include <algorithm>

using namespace std;

const int   MOINS_INFINI = -10000000;
const int   MAX_LIN = 20000;
const int   MAX_COL = 500;

int     nbLin, nbCol, colDepart;
int     jeu[MAX_COL];

int     main(void){
    scanf("%d%d%d", &nbLin, &nbCol, &colDepart);
    int     colBonus, bonus;
    scanf("%d%d", &colBonus, &bonus);
    jeu[colBonus] = bonus;
    int     lu[MAX_COL];
    for (int i = 0 ; i < nbCol ; i++)
        lu[i] = 0;
    for(int lin = 1 ; lin < nbLin; lin++){
        for (int i = 0 ; i < nbCol ; i++)
            lu[i] = 0;
        if (lin != nbLin - 1){
            scanf("%d%d", &colBonus, &bonus);
            lu[colBonus] = bonus;
        }
        for (int j = 0 ; j < nbCol ; j++){
            int meilleur = MOINS_INFINI;
            int meilleurDep;
            for(int dep = -1; dep <= 1; dep++){
                int curCol = j + dep;
                if (curCol >= 0 && curCol < nbCol && jeu[curCol] > meilleur){
                    meilleur = jeu[curCol];
                    meilleurDep = dep;
                }
            }
            lu[j] += meilleur;
        }
        for (int i = 0 ; i < nbCol ; i++)
            jeu[i] = lu[i];
    }
    printf("%d", jeu[colDepart]);
    return 0;
}