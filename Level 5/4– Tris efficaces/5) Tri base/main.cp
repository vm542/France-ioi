#include <iostream>

using namespace std;

int     nbInts, ints[100000];

void    sortIt(int bit, int begin, int end){
    if (bit < 1 || end <= begin)
        return;
    int     left[100000], right[100000], nbLeft = 0, nbRight = 0;
    for (int i = begin ; i <= end ; i++){
        if ((ints[i] & bit) == 0){
            left[nbLeft] = ints[i];
            nbLeft++;
        }
        else{
            right[nbRight] = ints[i];
            nbRight++;
        }
    }
    for (int i = 0 ; i < nbLeft ; i++)
        ints[begin + i] = left[i];
    for (int i = 0 ; i < nbRight ; i++)
        ints[begin + nbLeft + i] = right[i];
    sortIt(bit / 2, begin, begin + nbLeft - 1);
    sortIt(bit / 2, begin + nbLeft, begin + nbLeft + nbRight - 1);
}

int     nbLetters(int n){
    int     nb = 0;
    while (n > 1)
    {
        nb++;
        n /= 10;
    }
    return (nb);
}

void    radixSort(int tab[], int sizeTab){
    int     maxNbLetters = 0, biggest = 0, nb = 1;
    for (int i = 0 ; i < sizeTab ; i++){
        if (maxNbLetters <= nbLetters(tab[i]) && biggest <= tab[i]){
            maxNbLetters = nbLetters(tab[i]);
            biggest = tab[i];
        }
    }
    while (nb < biggest)
        nb *= 2;
    sortIt(nb / 2, 0, sizeTab - 1);
}

int     main(void){
    cin >> nbInts;
    for (int i = 0 ; i < nbInts ; i++)
        cin >> ints[i];
    radixSort(ints, nbInts);
    for (int i = 0 ; i < nbInts ; i++)
        cout << ints[i] << " ";
    return (0);
}
