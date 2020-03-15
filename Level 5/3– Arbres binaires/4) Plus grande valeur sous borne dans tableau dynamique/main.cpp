#include <stdio.h>
#include <algorithm>

using namespace std;

int     sizeArray, nbRequests, noeuds[2000000], sizeTree = 1;

void    update(int index){
    if (index < 1)
        return;
    noeuds[index] = max(noeuds[index * 2], noeuds[index * 2 + 1]);
    update(index / 2);
}

int     find(int index, int toFind){
    if (noeuds[index] == 1){
        
    }
}

int     main(void){
    scanf("%d%d", &sizeArray, &nbRequests);
    while (sizeTree < sizeArray)
        sizeTree *= 2;
    for (int i = 0 ; i < nbRequests ; i++){
        char    request;
        int     index;
        scanf(" %c%d", &request, &index);
        if (request == 'M'){
            scanf("%d", &noeuds[sizeTree + index]);
            update((sizeTree + index) / 2);
        }
        else{
            printf("%d\n", find(sizeTree + index, index));
        }
    }
    return (0);
}

/*

5
7
M 2 1
R 3
M 1 1
R 2
M 2 0
R 0
R 4

*/