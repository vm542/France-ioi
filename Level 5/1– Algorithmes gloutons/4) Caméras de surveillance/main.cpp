#include <stdio.h>
#include <algorithm>

using namespace std;

class   Arc{
    public:
        int     iInter1, iInter2, longueur;
        Arc(int i1, int i2, int l){
            iInter1 = i1;
            iInter2 = i2;
            longueur = l;
        }
        Arc(){}
};

Arc arcs[10000];
int     chemins[10001];

int     longueurTotale = 0;
int     nbIntersections, nbChemins;

bool    cmp(Arc const & a, Arc const & b){
    return (a.longueur < b.longueur);
}

void    unir(int iInter1, int iInter2){
    for (int i = 1 ; i <= nbIntersections ; i++){
        if (i != iInter2 && chemins[i] == chemins[iInter2])
            chemins[i] = chemins[iInter1];
    }
    chemins[iInter2] = chemins[iInter1];
}

int     find(int iInter1, int iInter2){
    if (chemins[iInter1] == chemins[iInter2])
        return (1);
    return (0);
}

int     main(void){
    scanf("%d%d", &nbIntersections, &nbChemins);
    for (int i = 1 ; i <= nbIntersections ; i++)
        chemins[i] = i;
    for (int i = 0 ; i < nbChemins ; i++){
        int     iInter1, iInter2, longueur;
        scanf("%d%d%d", &iInter1, &iInter2, &longueur);
        arcs[i] = Arc(iInter1, iInter2, longueur);
    }
    sort(arcs, arcs + nbChemins, cmp);
    for (int i = 0 ; i < nbChemins ; i++){
        if (!find(arcs[i].iInter1, arcs[i].iInter2)){
            unir(arcs[i].iInter1, arcs[i].iInter2);
            longueurTotale += arcs[i].longueur;   
        }
    }
    printf("%d", longueurTotale);
    return (0);
}