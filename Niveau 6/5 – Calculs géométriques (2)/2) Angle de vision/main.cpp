#include <stdio.h>
#include <cmath>

using namespace std;

class   Coord{
    public:
        int x, y;
        Coord(int x, int y){
            this->x = x;
            this->y = y;
        }
        Coord(){}
};

class   Droite{
    public:
        Coord   point1, point2;
        int     x, y;
        Droite(Coord point1, Coord point2){
            this->point1 = point1;
            this->point2 = point2;
            this->x = point2.x - point1.x;
            this->y = point2.y - point1.y;
        }
        Droite(){}
        double  longeur(){
            return (sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2)));
        }
        double  scalaire(Droite droite2){
            return (x * droite2.x + y * droite2.y);
        }
};

int main(void){
    Coord   tour;
    scanf("%d%d", &tour.x, &tour.y);
    int nbPistes;
    double  min = 999;
    Droite  minDroite = Droite();
    scanf("%d", &nbPistes);
    for (int i = 0 ; i < nbPistes ; i++){
        Coord   extr1, extr2;
        scanf("%d%d%d%d", &extr1.x, &extr1.y, &extr2.x, &extr2.y);
        Droite  droite1 = Droite(tour, extr1);
        Droite  droite2 = Droite(tour, extr2);
        Droite  droite3 = Droite(extr1, extr2);
        //double  angle = abs(acos(droite1.scalaire(droite2) / (droite1.longeur() * droite2.longeur())) * (180 / M_PI));
        double  angle = acos((pow(droite1.longeur(), 2) + (pow(droite2.longeur(), 2)) - (pow(droite3.longeur(), 2))) / (2 * droite1.longeur() * droite2.longeur())) * (180 / M_PI);
        if (angle < min){
            min = angle;
            minDroite = Droite(extr1, extr2);
        }
    }
    printf("%d %d %d %d", minDroite.point1.x, minDroite.point1.y, minDroite.point2.x, minDroite.point2.y);
    return (0);
}