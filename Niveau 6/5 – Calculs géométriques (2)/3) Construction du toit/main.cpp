#include <stdio.h>
#include <algorithm>

using namespace std;

int nbPiliers, piliers[1000001];
int maxPilier = 0;

int findNext(int indice){
   for (int i = indice + 1 ; i < nbPiliers ; i++)
      if (piliers[i] > piliers[indice])
         return (i);
   return (indice);
}

int main(void){
    scanf("%d", &nbPiliers);
    for (int i = 0 ; i < nbPiliers ; i++){
        scanf("%d", &piliers[i]);
        if (piliers[maxPilier] <= piliers[i])
            maxPilier = i;
    }
    int curPilier = 0;
    printf("1 ");
    for (int i = 1 ; i <= maxPilier ; i++){
        if (piliers[i] >= piliers[curPilier] && piliers[i] >= (piliers[curPilier] + piliers[findNext(curPilier)]) / 2){
            if (curPilier != 0)
               printf("%d ", curPilier + 1);
            curPilier = i;
        }
    }
    if (maxPilier != 0)
       printf("%d ", maxPilier + 1);
    int maximums[1000001], curMax = nbPiliers - 1;
    for (int i = nbPiliers - 1 ; i >= 0 ; i--){
        if (piliers[i] >= piliers[curMax])
            curMax = i;
        maximums[i] = curMax;
    }
    for (int i = maxPilier + 1 ; i < nbPiliers ; i++){
        if (maximums[i] == i && i != 0)
            printf("%d ", i + 1);
    }
    return (0);
}