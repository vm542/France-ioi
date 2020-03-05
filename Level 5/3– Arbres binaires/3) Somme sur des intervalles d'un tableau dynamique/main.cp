#include <iostream>

using namespace std;

class   Node{
    public:
        int     left, right, sum;
        Node(){}
        Node(int left, int right, int sum){
            this->left = left;
            this->right = right;
            this->sum = sum;
        }
};

int     sizeArray, nbRequests, array[1000003], indices[1000003];
Node    arbre[2000003];

void    update(int index){
    if (index < 1)
        return;
    arbre[index].sum = arbre[index * 2].sum + arbre[index * 2 + 1].sum;
    update(index / 2);
}

void    createTree(int left, int right, int index){
    if (left == right){
        arbre[index] = Node(left, right, array[right]);
        indices[right] = index;
        update(index / 2);
        return;
    }
    arbre[index] = Node(left, right, 0);
    createTree(left, right - (right - left) / 2 - 1, index * 2);
    createTree(right - (right - left) / 2, right, index * 2 + 1);
}

int     search(int left, int right, int index){
    int     RRChild, RLChild, LRChild, LLChild;

    LLChild = arbre[index * 2].left;
    LRChild = arbre[index * 2].right;
    RLChild = arbre[index * 2 + 1].left;
    RRChild = arbre[index * 2 + 1].right;
    if (left == arbre[index].left && right == arbre[index].right)
        return (arbre[index].sum);
    if (LLChild == left && LRChild == right)
        return (arbre[index * 2].sum);
    if (RLChild == left && RRChild == right)
        return (arbre[index * 2 + 1].sum);
    if (left <= LRChild && right >= RLChild)
       return search(left, LRChild, index * 2) + search(RLChild, right, index * 2 + 1);
    else if (left <= LRChild)
        return search(left, right, index * 2);
    else if  (right >= RLChild)
        return search(left, right, index * 2 + 1);
    else
        return (arbre[index].sum);
}

int     main(void){
    cin >> sizeArray;
    for (int i = 0 ; i < sizeArray ; i++)
        cin >> array[i];
    createTree(0, sizeArray - 1, 1);
    cin >> nbRequests;
    for (int i = 0 ; i < nbRequests ; i++){
        char    request;
        int     left, right;
        cin >> request >> left >> right;
        if (request == 'M'){
            arbre[indices[left]].sum = right;
            update(indices[left] / 2);
        }
        else
            cout << search(left, right, 1) << endl;
    }
    return (0);
}
