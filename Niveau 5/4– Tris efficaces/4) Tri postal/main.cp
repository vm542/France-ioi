#include <iostream>

using namespace std;

int   nbElements;
int   elements[200001];

int   main(void){
   cin >> nbElements;
   for (int i = 0 ; i < nbElements ; i++){
      int   n;
      cin >> n;
      elements[n + 100000]++;
   }
   for (int i = 0 ; i < 200001 ; i++){
      if (elements[i] > 0){
         for (int j = 0 ; j < elements[i] ; j++)
            cout << i - 100000 << " ";
      }
   }
   return (0);
}
