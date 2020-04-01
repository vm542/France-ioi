#include <stdio.h>
#include <vector>

using namespace std;

class Case{
    public:
        int     x, y;
        bool    aColorier;
    Case(int xCase, int yCase, int aCol){
        x = xCase;
        y = yCase;
        aColorier = aCol;
    }
    Case(){}
};

char    triminos[8][8], lettre = 'a' - 1;

int     choisir(int xPiece, int yPiece, int xCoin, int yCoin, int taille){
    if (xPiece < xCoin + taille / 2){
        if (yPiece < yCoin + taille / 2)
            return (1);
        return (2);
    }
    else{
        if (yPiece < yCoin + taille / 2)
            return (4);
        return (3);
    }
}

void    parcourir(int xPiece, int yPiece, int xCoin, int yCoin, int taille){
    if (taille < 2)
        return;
    int choix = choisir(xPiece, yPiece, xCoin, yCoin, taille);
    vector<Case> aParcourir;
    aParcourir.push_back(Case(taille / 2 - 1, taille / 2 - 1, 1));
    aParcourir.push_back(Case(taille / 2 - 1, taille / 2, 1));
    aParcourir.push_back(Case(taille / 2, taille / 2, 1));
    aParcourir.push_back(Case(taille / 2, taille / 2 - 1, 1));
    aParcourir.at(choix - 1) = Case(xPiece - xCoin, yPiece - yCoin, 0);
    lettre++;
    int     coins[4][2] = {{xCoin, yCoin}, {xCoin, yCoin + taille / 2}, {xCoin + taille / 2, yCoin + taille / 2}, {xCoin + taille / 2, yCoin}};
    for (int i = 0 ; i < 4 ; i++){
        int     x = aParcourir.at(i).x;
        int     y = aParcourir.at(i).y;
        if (aParcourir.at(i).aColorier == 1)
            triminos[xCoin + x][yCoin + y] = lettre;
    }
    for (int i = 0 ; i < 4 ; i++){
        int     x = aParcourir.at(i).x;
        int     y = aParcourir.at(i).y;
        parcourir(xCoin + x, yCoin + y, coins[i][0], coins[i][1], taille / 2);
    }
}

int     main(void){
    int     xPiece, yPiece;
    scanf("%d%d", &xPiece, &yPiece);
    triminos[xPiece][yPiece] = '#';
    parcourir(xPiece, yPiece, 0, 0, 8);
    for (int i = 0 ; i < 8 ; i++){
        for (int j = 0 ; j < 8 ; j++)
            printf("%c", triminos[i][j]);
        printf("\n");
    }
    return (0);
}