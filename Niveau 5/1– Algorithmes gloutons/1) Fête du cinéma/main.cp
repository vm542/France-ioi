#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Seance
{
public:
    int debut, fin;
    Seance(int d, int f){
        debut = d;
        fin = f;
    }
    Seance();
};

bool comparator(const Seance& lhs, const Seance& rhs) {
    if (lhs.fin == rhs.fin)
        return lhs.debut < rhs.debut;
    return lhs.fin < rhs.fin;
}

int   nbSeances, nbElements = 0, lastFin = -1;
vector<Seance> seances;

int   main(void){
    cin >> nbSeances;
    for (int i = 0 ; i < nbSeances ; i++){
        int   debut, fin;
        cin >> debut >> fin;
        seances.push_back(Seance(debut, fin));
    }
    sort(seances.begin(), seances.end(), &comparator);
    
    for (int i = 0 ; i < nbSeances ; i++){
        if (seances[i].debut > lastFin){
            lastFin = seances[i].fin;
            nbElements++;
        }
    }
    cout << nbElements << endl;
    return (0);
} 
