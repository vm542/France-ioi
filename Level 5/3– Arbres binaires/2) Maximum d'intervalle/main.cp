#include <iostream>

using namespace std;

int     nbElements, nbIntervalles;

class   Noeud{
    public:
        int     left, right, max;
        Noeud(){}
        Noeud(int left, int right, int max){
            this->left = left;
            this->right = right;
            this->max = -1;
        }
};

Noeud   arbre[2000003];
int     racines[1000003];

void    arranger(int index){
    if (index < 1)
        return;
    if (arbre[index].max < arbre[index * 2].max)
        arbre[index].max = arbre[index * 2].max;
    if (arbre[index].max < arbre[index * 2 + 1].max)
        arbre[index].max = arbre[index * 2 + 1].max;
    arranger(index / 2);
}

void    creerArbre(int left, int right, int current){
    arbre[current * 2] = Noeud(left, right - (right - left) / 2 - 1, -1);
    arbre[current * 2 + 1] = Noeud(right - (right - left) / 2, right, -1);
    if (arbre[current * 2].left != arbre[current * 2].right)
        creerArbre(arbre[current * 2].left, arbre[current * 2].right, current * 2);
    else{
        arbre[current * 2].max = racines[arbre[current * 2].left];
        arranger(current);
    }
    if (arbre[current * 2 + 1].left != arbre[current * 2 + 1].right)
        creerArbre(arbre[current * 2 + 1].left, arbre[current * 2 + 1].right, current * 2 + 1);
    else{
        arbre[current * 2 + 1].max = racines[arbre[current * 2 + 1].left];
        arranger(current);
    }
}

int     parcourir(int left, int right, int currentId){
    int     RRChild, RLChild, LRChild, LLChild;

    LLChild = arbre[currentId * 2].left;
    LRChild = arbre[currentId * 2].right;
    RLChild = arbre[currentId * 2 + 1].left;
    RRChild = arbre[currentId * 2 + 1].right;
    if (left == arbre[currentId].left && right == arbre[currentId].right)
        return (arbre[currentId].max);
    if (LLChild == left && LRChild == right)
        return (arbre[currentId * 2].max);
    if (RLChild == left && RRChild == right)
        return (arbre[currentId * 2 + 1].max);
    if (left <= LRChild && right >= RLChild)
       return max(parcourir(left, LRChild, currentId * 2), parcourir(RLChild, right, currentId * 2 + 1));
    else if (left <= LRChild)
        return parcourir(left, right, currentId * 2);
    else if  (right >= RLChild)
        return parcourir(left, right, currentId * 2 + 1);
    else
        return (arbre[currentId].max);
}

int     main(void)
{
    cin >> nbElements;
    for (int i = 0 ; i < nbElements ; i++)
        cin >> racines[i];
    arbre[1] = Noeud(0, nbElements - 1, -1);
    creerArbre(0, nbElements - 1, 1);
    cin >> nbIntervalles;
    for (int i = 0 ; i < nbIntervalles ; i++){
        int     left, right;
        cin >> left >> right;
        cout << parcourir(left - 1, right - 1, 1) << endl;
    }
    return (0);
}
