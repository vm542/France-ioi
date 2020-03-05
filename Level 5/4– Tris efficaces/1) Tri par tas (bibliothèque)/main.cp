#include <stdio.h>
#include <stdlib.h>

int   values[100000];

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int    main(void){
   int    nbVal;
   scanf("%d", &nbVal);
   for (int i = 0 ; i < nbVal ; i++)
      scanf("%d", &values[i]);
   qsort(values, nbVal, sizeof(int), cmpfunc);
   for (int i = 0 ; i < nbVal ; i++)
      printf("%d ", values[i]);
   return (0);
}
