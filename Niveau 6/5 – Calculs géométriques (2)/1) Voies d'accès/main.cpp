#include <stdio.h>
#include <cmath>

using namespace std;

struct  Coord{
    int x, y;
};

Coord   nouv1, nouv2;
int     nbSegments;

int orientation(Coord point1, Coord point2, Coord point3){
    float   val = (float)((point2.y - point1.y) * (point3.x - point2.x) - (point3.y - point2.y) * (point2.x - point1.x));
    if (val == 0)
        return (0);
    if (val > 0)
        return (1);
    return (2);
}

int     colinear(Coord point1, Coord point2, Coord point3, Coord point4){
    if ((point1.x >= point3.x && point1.x <= point4.x) || (point2.x >= point3.x && point2.x <= point4.x))
        return (1);
    if ((point1.y >= point3.y && point1.y <= point4.y) || (point2.y >= point3.y && point2.y <= point4.y))
        return (1);
    return (0);
}

int     main(void){
    scanf("%d%d%d%d", &nouv1.x, &nouv1.y, &nouv2.x, &nouv2.y);
    scanf("%d", &nbSegments);
    for (int i = 0 ; i < nbSegments ; i++){
        Coord   point1, point2;
        scanf("%d%d%d%d", &point1.x, &point1.y, &point2.x, &point2.y);
        int o1 = orientation(nouv1, nouv2, point1);
        int o2 = orientation(nouv1, nouv2, point2);
        int o3 = orientation(point1, point2, nouv1);
        int o4 = orientation(point1, point2, nouv2);
        if ((o1 != o2 && o3 != o4) || (o1 == 0 && o2 == 0 && o3 == 0 && o4 == 0 && colinear(nouv1, nouv2, point1, point2)))
            printf("1\n");
        else
            printf("0\n");
    }
    return (0);
}