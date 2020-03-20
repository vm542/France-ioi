#include <stdio.h>

using namespace std;

struct  Coord{
    int x, y;
};

Coord   nouv1, nouv2;
int     nbSegments;

float   coefficientDir(Coord point1, Coord point2){
    return ((double)(point2.y - point1.y) / (double)(point2.x - point1.x));
}

int     main(void){
    scanf("%d%d%d%d", &nouv1.x, &nouv2.y, &nouv2.x, &nouv2.y);
    printf("%lf ", coefficientDir(nouv1, nouv2));
    scanf("%d", &nbSegments);
    for (int i = 0 ; i < nbSegments ; i++){
        Coord   point1, point2;
        scanf("%d%d%d%d", &point1.x, &point1.y, &point2.x, &point2.y);
        printf("%lf", coefficientDir(point1, point2));
        //printf("%lf %lf\n", coefficientDir(point1, point2), coefficientDir(nouv1, nouv2));
        /*if (coefficientDir(point1, point2) == coefficientDir(nouv1, nouv2)){
            
        }
        else
            printf("%d\n", 0);*/
    }
    return (0);
}

/*


25 28 0 40
1
10 3 3 18
10 3 18 8
18 8 13 21
13 21 9 30
9 30 15 38
15 38 25 36
13 21 25 36
25 36 27 45
27 45 32 38
32 38 45 36

*/