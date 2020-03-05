#include <iostream>

using namespace std;

int     travailleurs[1000], nbTravailleurs, nbPaires;

int     findRacine(int i){
    if (i == travailleurs[i])
        return (i);
    return (findRacine(travailleurs[i]));
}

int     unir(int attaquant, int cible){
    travailleurs[findRacine(cible)] = findRacine(attaquant);
}

void    findChef(int i){
    cout << i << " ";
    if (i == travailleurs[i])
        return;
    findChef(travailleurs[i]);
}

int     main(void){
    cin >> nbTravailleurs >> nbPaires;
    for (int i = 0 ; i < nbTravailleurs ; i++)
        travailleurs[i] = i;
    for (int i = 0 ; i < nbPaires ; i++){
        int     attaquant, cible;
        cin >> attaquant >> cible;
        if (attaquant == cible){
            findChef(attaquant);
            cout << endl;
        }
        else if (findRacine(attaquant) != findRacine(cible))
            unir(attaquant, cible);
    }
    return (0);
}