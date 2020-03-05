#include <stdio.h>

int      num;
unsigned long long last1 = 0, last2 = 1;

  unsigned long long    fibo(int n){
   if (n == 1){
      return last1 + last2;
   }
   unsigned long long   temp = last1;
   last1 = last2 + last1;
   last2 = temp;
   fibo(n - 1);
}

int   main(void){
   int   ind;
   scanf("%d", &ind);
   if (ind == 0){
      printf("%llu\n", last1);
   }
   else if(ind == 1){
      printf("%llu\n", last2);
   }
   else{
      printf("%llu\n", fibo(ind));
   }
   return 0;
}
