#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

class   Sentier{
    public:
        int     debut, arrivee, longueur;
        Sentier(int d, int a, int l){
            debut = d;
            arrivee = a;
            longueur = l;
        }
        Sentier(){}
};

class   Intersection{
    public:
        int     indice;
        vector<Sentier> voisins;
        int     valeur = -1;
        Intersection(){}
};

Intersection     intersections[1001];

int     nbIntesections, nbSentiers, iDepart, iArrivee;

int     main(void){
    scanf("%d%d%d%d", &nbIntesections, &nbSentiers, &iDepart, &iArrivee);
    for (int i = 0 ; i <= nbIntesections ; i++)
        intersections[i].indice = i;
    for (int i = 0 ; i < nbSentiers ; i++){
        int     debut, arrivee, longueur;
        scanf("%d%d%d", &debut, &arrivee, &longueur);
        intersections[debut].voisins.push_back(Sentier(debut, arrivee, longueur));
        intersections[arrivee].voisins.push_back(Sentier(arrivee, debut, longueur));
    }
    queue<Intersection>   fileAttente;
    fileAttente.push(intersections[iDepart]);
    while (!fileAttente.empty()){
        Intersection    current = fileAttente.front();
        fileAttente.pop();
        for (int i = 0 ; i < current.voisins.size() ; i++){
            int     iArrivee = current.voisins.at(i).arrivee;
            if (intersections[iArrivee].valeur == -1 || current.valeur + current.voisins.at(i).longueur < intersections[iArrivee].valeur){
                intersections[iArrivee].valeur = current.valeur + current.voisins.at(i).longueur;
                fileAttente.push(intersections[current.voisins.at(i).arrivee]);
            }
        }
    }
    fileAttente.push(intersections[iArrivee]);
    vector<int>     sequence;
    sequence.push_back(iArrivee);
    while (!fileAttente.empty()){
        Intersection    current = fileAttente.front();
        fileAttente.pop();
        for (int i = 0 ; i < current.voisins.size() ; i++){
            int     iAr = current.voisins.at(i).arrivee;
            if (intersections[iAr].valeur + current.voisins.at(i).longueur == current.valeur){
                fileAttente.push(intersections[iAr]);
                sequence.push_back(iAr);
            }
        }
    }
    sequence.push_back(iDepart);
    printf("%d %d\n", intersections[iArrivee].valeur + 1, sequence.size());
    for (int i = sequence.size() - 1 ; i >= 0 ; i--)
        printf("%d ", sequence.at(i));
    return (0);
}