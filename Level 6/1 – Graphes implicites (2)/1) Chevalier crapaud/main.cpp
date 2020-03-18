#include <stdio.h>
#include <queue>

#define MAX_COTE 1000
#define NB_COUPS_CAVALIER 8
#define NB_COUPS_CRAPAUD 4
#define INDEFINI -1
#define CAVALIER 0
#define CRAPAUD 1

using namespace std;

struct  Case{
    int     valide;
    int     nbCoupsCav = INDEFINI;
    int     nbCoupsCrap = INDEFINI;
};

struct  enAttente{
    int     x, y;
    int     tour;
    enAttente(int x, int y, int tour){
        this->x = x;
        this->y = y;
        this->tour = tour;
    }
    enAttente(){};
};

int     tailleEchiquier;
int     xDepart, yDepart, xArrivee, yArrivee;
Case    echiquier[MAX_COTE][MAX_COTE];
int     coupsCavalier[NB_COUPS_CAVALIER][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, 2}, {1, -2}, {2, -1}, {2, 1}};
int     coupsCrapaud[NB_COUPS_CRAPAUD][2] = {{0, 2}, {0, -2}, {2, 0}, {-2, 0}};

int     valide(int x, int y){
    if (x < 0 || x >= tailleEchiquier || y < 0 || y >= tailleEchiquier || !echiquier[x][y].valide)
        return (0);
    return (1);
}

int     main(void){
    scanf("%d%d%d%d%d", &tailleEchiquier, &xDepart, &yDepart, &xArrivee, &yArrivee);
    for (int i = 0 ; i < tailleEchiquier ; i++)
        for (int j = 0 ; j < tailleEchiquier ; j++)
            scanf("%1d", &echiquier[i][j].valide);
    queue<enAttente>  fileAttente;
    fileAttente.push(enAttente(xDepart, yDepart, CAVALIER));
    echiquier[xDepart][yDepart].nbCoupsCrap = 0;
    echiquier[xDepart][yDepart].nbCoupsCav = 0;
    while (!fileAttente.empty()){
        enAttente   courant = fileAttente.front();
        fileAttente.pop();
        if (courant.tour == CAVALIER){
            for (int i = 0 ; i < NB_COUPS_CAVALIER ; i++){
                int     nouvX = courant.x + coupsCavalier[i][0];
                int     nouvY = courant.y + coupsCavalier[i][1];
                if (valide(nouvX, nouvY) && (echiquier[nouvX][nouvY].nbCoupsCav == INDEFINI || 1 + echiquier[courant.x][courant.y].nbCoupsCrap < echiquier[nouvX][nouvY].nbCoupsCav)){
                    echiquier[nouvX][nouvY].nbCoupsCav = 1 + echiquier[courant.x][courant.y].nbCoupsCrap;
                    fileAttente.push(enAttente(nouvX, nouvY, (courant.tour + 1) % 2));
                }
            }
        }
        else{
            for (int i = 0 ; i < NB_COUPS_CRAPAUD ; i++){
                int     nouvX = courant.x + coupsCrapaud[i][0];
                int     nouvY = courant.y + coupsCrapaud[i][1];
                if (valide(nouvX, nouvY) && (echiquier[nouvX][nouvY].nbCoupsCrap == INDEFINI || 1 + echiquier[courant.x][courant.y].nbCoupsCav < echiquier[nouvX][nouvY].nbCoupsCrap)){
                    echiquier[nouvX][nouvY].nbCoupsCrap = 1 + echiquier[courant.x][courant.y].nbCoupsCav;
                    fileAttente.push(enAttente(nouvX, nouvY, (courant.tour + 1) % 2));
                }
            }
        }
    }
    if (echiquier[xArrivee][yArrivee].nbCoupsCrap == INDEFINI && echiquier[xArrivee][yArrivee].nbCoupsCav == INDEFINI)
        printf("%d", INDEFINI);
    else if (echiquier[xArrivee][yArrivee].nbCoupsCrap == INDEFINI || echiquier[xArrivee][yArrivee].nbCoupsCav == INDEFINI)
        printf("%d", max(echiquier[xArrivee][yArrivee].nbCoupsCrap, echiquier[xArrivee][yArrivee].nbCoupsCav));
    else
        printf("%d", min(echiquier[xArrivee][yArrivee].nbCoupsCrap, echiquier[xArrivee][yArrivee].nbCoupsCav));
    return (0);
}