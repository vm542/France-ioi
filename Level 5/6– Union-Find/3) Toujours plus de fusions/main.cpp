#include <iostream>

using namespace std;

int     travailleurs[100000], nbTravailleurs, nbRecontres, tailles[100000];

int     findRacine(int i){
    if (i == travailleurs[i])
        return (i);
    travailleurs[i] = findRacine(travailleurs[i]);
    return (findRacine(travailleurs[i]));
}

void    unir(int num1, int num2){
    if (tailles[num1] <= tailles[num2]){
        travailleurs[num1] = travailleurs[num2];
        tailles[num2] += tailles[num1];
    }
    else{
        travailleurs[num2] = travailleurs[num1];
        tailles[num1] += tailles[num2];
    }
}

int     main(void){
    ios::sync_with_stdio(false);
    cin >> nbTravailleurs >> nbRecontres;
    for (int i = 0 ; i < nbTravailleurs ; i++){
        travailleurs[i] = i;
        tailles[i] = 1;
    }
    for (int i = 0 ; i < nbRecontres ; i++){
        int     num1, num2;
        cin >> num1 >> num2;
        travailleurs[num1] = findRacine(travailleurs[num1]);
        travailleurs[num2] = findRacine(travailleurs[num2]);
        if (travailleurs[num1] != travailleurs[num2]){
            unir(travailleurs[num1], travailleurs[num2]);
            cout << num1 << " " << num2 << '\n';
        }
    }
    return (0);
}