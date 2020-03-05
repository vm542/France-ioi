#include <iostream>

using namespace std;

int     nbErosions, hauteur, largeur;
int     dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
char    image[250][250];

void    modifier(){
    for (int i = 0 ; i < hauteur ; i++)
        for (int j = 0 ; j < largeur ; j++)
            if (image[i][j] == 'x')
                image[i][j] = '.';
}

int     verifierCase(int x, int y){
    if (x < 0 || x >= hauteur || y < 0 || y >= largeur || (image[x][y] == '.'))
        return (0);
    return (1);
}

void    erosion(){
    int     nbNoirs;
    for (int x = 0 ; x < hauteur ; x++){
        for (int y = 0 ; y < largeur ; y++){
            nbNoirs = 0;
            if (image[x][y] == '#'){
                for (int i = 0 ; i < 4 ; i++){
                    nbNoirs += verifierCase(x + dirs[i][0], y + dirs[i][1]);
                }
                if (nbNoirs < 4)
                    image[x][y] = 'x';
            }
        }
    }
    modifier();
}

void    afficher(){
    for (int i = 0 ; i < hauteur ; i++){
        for (int j = 0 ; j < largeur ; j++)
            cout << image[i][j];
        cout << endl;
    }
}

int     main(void){
    cin >> nbErosions >> hauteur >> largeur;
    for (int i = 0 ; i < hauteur ; i++)
        cin >> image[i];
    for (int i = 0 ; i < nbErosions ; i++)
        erosion();
    afficher();
    return (0);
}