#include <iostream>

using namespace std;

int     nbTravailleurs, nbRencontres;
int     tab[1000];

int     find(int a, int b){
    if (tab[a] == tab[b])
        return (1);
    return (0);
}

void     reunir(int a, int b){
    for (int i = 0 ; i < nbTravailleurs ; i++)
        if (i != b && tab[i] == tab[b])
            tab[i] = tab[a];
    tab[b] = tab[a];
}

int     main(void){
    cin >> nbTravailleurs >> nbRencontres;
    for (int i = 0 ; i < nbTravailleurs ; i++)
        tab[i] = i;
    for (int i = 0 ; i < nbRencontres ; i++){
        int     a, b;
        cin >> a >> b;
        if (!find(a, b)){
            cout << a << " " << b << endl;
            reunir(a, b);
        }
    }
    return (0);
}
