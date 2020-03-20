#include <stdio.h>
#include <vector>
#include <list>

#define MAX_NB_ZOINXIENS 200001

using namespace std;

struct  Zoinxien{
    int x, y, nbTentacules, age, visite = 0;
    vector<int> amis;
    Zoinxien(int x, int y, int nbTentacules, int age){
        this->x = x;
        this->y = y;
        this->nbTentacules = nbTentacules;
        this->age = age;
    }
    Zoinxien(){}
};

struct  Racine{
    list<int>   enfants;
};

Zoinxien    zoinxiens[MAX_NB_ZOINXIENS + 1];
Racine  racinesX[MAX_NB_ZOINXIENS + 1], racinesY[MAX_NB_ZOINXIENS + 1], racinesA[MAX_NB_ZOINXIENS + 1], racinesT[MAX_NB_ZOINXIENS + 1];

int nbZoinxiens, nbAmis = 0;

void parcourir(int indice){
    zoinxiens[indice].visite = 1;
    for (unsigned int i = 0 ; i < zoinxiens[indice].amis.size() ; i++){
        if (zoinxiens[zoinxiens[indice].amis[i]].visite == 0){
            nbAmis++;
            parcourir(zoinxiens[indice].amis[i]);
        }
    }
}

int main(void){
    scanf("%d", &nbZoinxiens);
    for (int i = 1 ; i <= nbZoinxiens ; i++){
        int x, y, nbTentacules, age;
        scanf("%d%d%d%d", &x, &y, &nbTentacules, &age);
        zoinxiens[i] = Zoinxien(x, y, nbTentacules, age);
        for (auto it = racinesX[x].enfants.begin(); it != racinesX[x].enfants.end(); ++it){
            zoinxiens[i].amis.push_back(*it);
            zoinxiens[*it].amis.push_back(i);
        }
        for (auto it = racinesY[y].enfants.begin(); it != racinesY[y].enfants.end(); ++it){
            zoinxiens[i].amis.push_back(*it);
            zoinxiens[*it].amis.push_back(i);
        }
        for (auto it = racinesT[nbTentacules].enfants.begin(); it != racinesT[nbTentacules].enfants.end(); ++it){
            zoinxiens[i].amis.push_back(*it);
            zoinxiens[*it].amis.push_back(i);
        }
        racinesX[x].enfants.push_back(i);
        racinesY[y].enfants.push_back(i);
        racinesT[nbTentacules].enfants.push_back(i);
        for (int j = age - 5 ; j <= age + 5 ; j++){
            if (j >= 0 && j <= 200000){
                for (auto it = racinesA[j].enfants.begin(); it != racinesA[j].enfants.end(); ++it){
                    zoinxiens[i].amis.push_back(*it);
                    zoinxiens[*it].amis.push_back(i);
                }
            }
        }
        racinesA[age].enfants.push_back(i);
    }
    parcourir(1);
    printf("%d", nbAmis);
    return (0);
}