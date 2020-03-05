#include <iostream>

using namespace std;

int     sizeArray, array[10000];

void    afficher(int    size, int   tab[]){
    for (int i = 0 ; i <= size ; i++)
        cout << tab[i] << " ";
    cout << endl;
}

int   *triFusion(int begin, int end){
    if (end - begin == 0)
        return (array);
    int     middle = begin + (end - begin) / 2;
    int     *left = triFusion(begin, middle);
    int     *right = triFusion(middle + 1, end);
    int     sizeLeft = middle - begin + 1, sizeRight = end - middle + 1, iLeft = 0, iRight = 0;
    int     sortedTab[100000];
    for (int i = 0 ; i <= end - begin ; i++){
        if (left[iLeft] <= right[iRight])
            sortedTab[i] = left[iLeft++];
        else
            sortedTab[i] = right[iRight++];
    }
    return (sortedTab);
} 

int     main(void){
    cin >> sizeArray;
    for (int i = 0 ; i < sizeArray ; i++)
        cin >> array[i];
    int     *sorted = triFusion(0, sizeArray - 1);
    afficher(sizeArray, sorted);
    return (0); 
}

/*

5
1 20 3 7 5

*/