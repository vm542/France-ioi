#include <stdio.h>
#include <math.h>

struct  vecteur{
    int x, y;
    vecteur(int x = 0, int y = 0) : x(x), y(y) {}
    void    lire() { scanf("%d%d", &x, &y); }
    vecteur operator - (const vecteur other) const{
        return vecteur(x - other.x, y - other.y);
    }
    double  prodScalaire(vecteur other){
        return x * other.x + y * other.y;
    }
    double  prodCroix(vecteur other){
        return x * other.y - y * other.x;
    }
    double  longueur(vecteur other){
        return (sqrt(pow(other.x - x, 2) + pow(other.y - y, 2)));
    }
};

struct  segment{
    vecteur A, B;
    segment(vecteur A, vecteur B){
        this->A = A;
        this->B = B;
    }
    segment();
};

double  angleVision(vecteur P, segment S){
    vecteur PA = S.A - P;
    vecteur PB = S.B - P;
    return fabs(atan2(PA.prodCroix(PB), PA.prodScalaire(PB)));
}

int nbLieux;
vecteur lieux[100001];
vecteur gauche = vecteur(1000000001, -1), droite = vecteur(-1, -1), haut = vecteur(1000000001, -1), bas = vecteur(-1, 1000000001);

int main(void){
    scanf("%d", &nbLieux);
    for (int i = 0 ; i < nbLieux ; i++){
        lieux[i].lire();
        if (lieux[i].x < gauche.x)
            gauche = lieux[i];
        if (lieux[i].x > droite.x)
            droite = lieux[i];
        if (lieux[i].y >= haut.y && lieux[i].x < haut.x)
            haut = lieux[i];
        if (lieux[i].y < bas.y)
            bas = lieux[i];
    }
    vecteur curPoint = vecteur(0, 10);
    int pointX = 0;
    double  distance = 0;
    printf("%d %d\n", haut.x, haut.y);
    //while (true){
        if (curPoint.x == haut.x && curPoint.y == haut.y)
            pointX = droite.x + 10000000;
        double  minAngle = -1;
        vecteur suivPoint;
        vecteur pt = vecteur(pointX, curPoint.y);
        if (pointX == 0){
            for (int i = 0 ; i < nbLieux ; i++){
                if (lieux[i].x != curPoint.x && lieux[i].y != curPoint.y){
                    if (minAngle < angleVision(lieux[i], segment(pt, curPoint)) && lieux[i].y > curPoint.y){
                        minAngle = angleVision(lieux[i], segment(pt, curPoint));
                        suivPoint = lieux[i];
                    }
                }
            }
        }
        else{
            for (int i = 0 ; i < nbLieux ; i++){
                if (lieux[i].x != curPoint.x && lieux[i].y != curPoint.y){
                    if (minAngle < angleVision(lieux[i], segment(pt, curPoint)) && lieux[i].y <= curPoint.y){
                        minAngle = angleVision(lieux[i], segment(pt, curPoint));
                        suivPoint = lieux[i];
                    }
                }
            }
        }            
        distance += curPoint.longueur(suivPoint);
        curPoint = suivPoint;
        printf("%d %d\n", curPoint.x, curPoint.y);
        //if (suivPoint.x == bas.x && suivPoint.y == bas.y)
        //    break;
    //}
    //printf("%d", (int)(round(distance)));
    return (0);
}