#include <stdio.h>

#define MAX_NB_ZOINXIENS 200000

using namespace std;


int nbZoinxiens, nbAmis = 0;
int racinesX[MAX_NB_ZOINXIENS + 1], racinesY[MAX_NB_ZOINXIENS + 1], racinesA[MAX_NB_ZOINXIENS + 1], racinesT[MAX_NB_ZOINXIENS + 1];
int amities[MAX_NB_ZOINXIENS + 1];
int tailles[MAX_NB_ZOINXIENS + 1];

int racine(int iZonxien){
    if (amities[iZonxien] != iZonxien)
        amities[iZonxien] = racine(amities[iZonxien]);
    return (amities[iZonxien]);
}

void    unir(int zA, int aB){
    int zoinxienA = racine(amities[zA]);
    int zoinxienB = racine(amities[aB]);
    if (zoinxienA == zoinxienB)
        return;
    if (tailles[zoinxienB] < tailles[zoinxienA]){
        amities[zoinxienB] = zoinxienA;
        tailles[zoinxienA] += tailles[zoinxienB];
    }
    else{
        amities[zoinxienA] = zoinxienB;
        tailles[zoinxienB] += tailles[zoinxienA];
    }
}

int main(void){
    scanf("%d", &nbZoinxiens);
    for (int i = 1 ; i <= nbZoinxiens ; i++){
        amities[i] = i;
        tailles[i] = 1;
    }
    for (int i = 1 ; i <= nbZoinxiens ; i++){
        int x, y, nbTentacules, age;
        scanf("%d%d%d%d", &x, &y, &nbTentacules, &age);
        if (racinesX[x] == 0)
            racinesX[x] = i;
        unir(racinesX[x], i);
        if (racinesY[y] == 0)
            racinesY[y] = amities[i];
        unir(racinesY[y], i);
        if (racinesT[nbTentacules] == 0)
            racinesT[nbTentacules] = amities[i];            
        unir(racinesT[nbTentacules], amities[i]);
        if (racinesA[age] == 0)
            racinesA[age] = i;
        for (int j = age - 5 ; j <= age + 5 ; j++)
            if (j >= 0 && j <= MAX_NB_ZOINXIENS)
                if (racinesA[j] != 0)
                    unir(racinesA[j], i);
    }
    for (int i = 2 ; i <= nbZoinxiens ; i++)
        if (racine(i) == racine(1))
            nbAmis++;
    printf("%d", nbAmis);
    return (0);
}