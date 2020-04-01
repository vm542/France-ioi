#include <iostream>
using namespace std;
int     nbCartes, nbOperations = 0, cartes[10001], operations[10001][2];
int     main(void){
    cin >> nbCartes;
    for (int i = 1 ; i <= nbCartes ; i++)
        cin >> cartes[i];
    int     currNb = 1;
    while (currNb != 0){
        currNb = 0;
        for (int i = 1 ; i <= nbCartes ; i++){
            int     temp;
            if (cartes[i] != i){
                currNb++;
                operations[nbOperations][0] = i;
                operations[nbOperations][1] = cartes[i];
                temp = cartes[cartes[i]];
                cartes[cartes[i]] = cartes[i];
                cartes[i] = temp;
                nbOperations++;
            }
        }
    }
    cout << nbOperations << endl;
    for (int i = 0 ; i < nbOperations ; i++){
        cout << operations[i][0] << " " << operations[i][1] << endl;
    }
    return (0);
}
