#include <stdio.h>

void    merge(int array[], int l, int middle, int r){
    int     leftSize = middle - l + 1, rightSize = r - middle;
    int     iLeft = 0, iRight = 0, index = l;
    int     left[leftSize], right[rightSize];
    
    for (int i = 0 ; i < leftSize ; i++)
        left[i] = array[l + i];
    for (int i = 0 ; i < rightSize ; i++)
        right[i] = array[middle + i + 1];
    while (iLeft < leftSize && iRight < rightSize){
        if (left[iLeft] <= right[iRight])
            array[index++] = left[iLeft++];
        else
            array[index++] = right[iRight++];
    }
    while (iLeft < leftSize)
        array[index++] = left[iLeft++];
    while (iRight < rightSize)
        array[index++] = right[iRight++];
}

void    mergeSort(int array[], int left, int right){
    if (left < right){
        int     middle = left + (right - left) / 2;
        mergeSort(array, left, middle);
        mergeSort(array, middle + 1, right);
        merge(array, left, middle, right);
    }
}

int     main(void){
    int     nbElements, elements[100001];
    scanf("%d", &nbElements);
    for (int i = 0 ; i < nbElements ; i++)
        scanf("%d", &elements[i]);
    mergeSort(elements, 0, nbElements - 1);
    for (int i = 0 ; i < nbElements; i++)
        printf("%d ", elements[i]);
    return (0);
}