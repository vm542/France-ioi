#include <stdio.h>
#include <vector>

using namespace std;

int     sizeTree = 0;
int     arbre[2000001];

void    permuter(int i1, int i2){
    int     temps = arbre[i1];
    arbre[i1] = arbre[i2];
    arbre[i2] = temps;
}

void    update(int index){
    if (index == 1)
        return;
    if (arbre[index] < arbre[index / 2]){
        permuter(index, index / 2);
        update(index / 2);
    }
}

void    insertion(int valeur){
    sizeTree++;
    arbre[sizeTree] = valeur;
    update(sizeTree);
}

void    update2(int index){
    if (index > sizeTree)
        return;
    if (arbre[index * 2] < arbre[index] && arbre[index * 2 + 1] < arbre[index]){
        int     min;
        if (arbre[index * 2] < arbre[index * 2 + 1])
            min = index * 2;
        else
            min = index * 2 + 1;
        if (min <= sizeTree){
            permuter(index, min);    
            update2(min);
        }
    }
    else if (arbre[index * 2] < arbre[index] && index * 2 <= sizeTree){
        permuter(index * 2, index);   
        update2(index * 2);
    }
    else if (arbre[index * 2 + 1] < arbre[index] && index * 2 + 1 <= sizeTree){
        permuter(index * 2 + 1, index);    
        update2(index * 2 + 1);
    }
}

void    extraire(){
    printf("%d\n", arbre[1]);
    arbre[1] = arbre[sizeTree];
    sizeTree--;
    update2(1);
}

int     main(void){
    int     nbRequetes;
    scanf("%d", &nbRequetes);
    for (int i = 0 ; i < nbRequetes ; i++){
        char    requete;
        int     valeur;
        scanf(" %c", &requete);
        if (requete == 'I'){
            scanf("%d", &valeur);
            insertion(valeur);
        }
        else{
            if (sizeTree == 1)
                printf("-\n");
            else
                extraire();
        }
    }
    return (0);
}