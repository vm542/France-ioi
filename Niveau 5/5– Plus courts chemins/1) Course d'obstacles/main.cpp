#include <stdio.h>
#include <queue>

#define MAX_COTE 1000
#define NB_DIRS 4

const   int PAS_DEFINI = -1;

using namespace std;

class   Case{
    public:
        int     ligne, colonne, aAjouter, valeurMin;
        Case(int lig, int col, int val){
            ligne = lig;
            colonne = col;
            aAjouter = val;
            valeurMin = PAS_DEFINI;
        }
        Case(){

        }
};

Case    labyrinthe[MAX_COTE][MAX_COTE];
int     nbLignes, nbColonnes;
int     dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void    lireLabyrinthe(){
    for (int i = 0 ; i < nbLignes ; i++){
        char    ligne[MAX_COTE];
        scanf("%s", ligne);
        for (int j = 0 ; j < nbColonnes ; j++){
            if (ligne[j] == '#')
                labyrinthe[i][j] = Case(i, j, -1);
            else if(ligne[j] == '.')
                labyrinthe[i][j] = Case(i, j, 0);
            else
                labyrinthe[i][j] = Case(i, j, ligne[j] - '0');
        }
    }
}

int     valide(int x, int y){
    if (x < 0 || x >= nbLignes || y < 0 || y > nbColonnes || labyrinthe[x][y].aAjouter == -1)
        return (0);
    return (1);
}

int     main(void){
    scanf("%d%d", &nbLignes, &nbColonnes);
    lireLabyrinthe();
    queue<Case> fileAttente;
    labyrinthe[nbLignes - 1][nbColonnes - 2].valeurMin = labyrinthe[nbLignes - 1][nbColonnes - 2].aAjouter;
    fileAttente.push(labyrinthe[nbLignes - 1][nbColonnes - 2]);
    while (!fileAttente.empty()){
        Case    current = fileAttente.front();
        fileAttente.pop();
        int     currX = current.ligne;
        int     currY = current.colonne;
        for (int i = 0 ; i < NB_DIRS ; i++){
            int     newX = current.ligne + dirs[i][0];
            int     newY = current.colonne + dirs[i][1];
            if (valide(newX, newY) && (labyrinthe[newX][newY].valeurMin == PAS_DEFINI || labyrinthe[currX][currY].valeurMin + labyrinthe[newX][newY].aAjouter < labyrinthe[newX][newY].valeurMin)){
                labyrinthe[newX][newY].valeurMin = labyrinthe[currX][currY].valeurMin + labyrinthe[newX][newY].aAjouter;
                fileAttente.push(labyrinthe[newX][newY]);
            }
        }
    }
    printf("%d", labyrinthe[1][0].valeurMin);
    return (0);
}