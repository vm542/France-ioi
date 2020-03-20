#include <stdio.h>

int    main(void){
    int     n;
    int     tab[10001][2];
    scanf("%d", &n);
    tab[0][0] = n / 2;
    tab[0][1] = (n - 1) / 2;
    tab[1][0] = 1;
    tab[1][1] = 2;
    int     j = 2;
    for (int i = n - 1 ; i > 1 ; i--){
        tab[j][0] = n;
        tab[j][1] = i;
        j++;
    }
    for (int i = 0 ; i < j ; i++){
        if (i % 2 == 0)
            printf("%d %d\n", tab[i][0], tab[i][1]);
    }
    for (int i = 0 ; i < j ; i++)
        if (i % 2 != 0)
            printf("%d %d\n", tab[i][0], tab[i][1]);
    return (0);
}