#include <stdio.h>
#include <vector>

using namespace std;

class   Tele{
    public:
        int     hauteur, largeur;
        vector<int> possible;
        Tele(){}
};

int     possible[1000][1000];
int     nbTeleviseurs, nbCommandes;
Tele    televiseurs[1000], commandes[1000];
int     commandesFaites[1000] = {-1};
int     maxCommandes = 0;
int     seen[1000];

int     trouverTele(int iCommande, int *seen){
    for (int i = 0 ; i < commandes[iCommande].possible.size() ; i++){
        int     iTeleviseur = commandes[iCommande].possible.at(i);
        if (!seen[iTeleviseur]){
            seen[iTeleviseur] = 1;
            if (commandesFaites[iTeleviseur] == -1 || trouverTele(commandesFaites[iTeleviseur], seen)){
                commandesFaites[iTeleviseur] = iCommande;
                return (1);
            }
        }
    }
    return (0);
}

int     main(void){
    for (int i = 0 ; i < 1000 ; i++)
        commandesFaites[i] = -1;
    scanf("%d", &nbTeleviseurs);
    for (int i = 0 ; i < nbTeleviseurs ; i++)
        scanf("%d%d", &televiseurs[i].hauteur, &televiseurs[i].largeur);
    scanf("%d", &nbCommandes);
    for (int i = 0 ; i < nbCommandes ; i++){
        scanf("%d%d", &commandes[i].hauteur, &commandes[i].largeur);
        for (int j = 0 ; j < nbTeleviseurs ; j++)
            if (televiseurs[j].hauteur >= commandes[i].hauteur && televiseurs[j].largeur >= commandes[i].largeur)
                commandes[i].possible.push_back(j);
    }
    for (int i = 0 ; i < nbCommandes ; i++){
        for (int i = 0 ; i < 1000 ; i++)
            seen[i] = 0;
        if (trouverTele(i, seen))
            maxCommandes++;;
    }
    printf("%d", maxCommandes);
    return (0);
}