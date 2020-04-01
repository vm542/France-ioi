#include<cstdio>
#include<vector>
#include<stack>

using namespace std;

const int MAX_NB_NOEUDS = 1000, INF = 1000*1000*1000;
void lireEntree();
bool trouverCheminAugmentant(int iNoeud);
bool trouverCheminDiminuant(int iNoeud);

bool initial[MAX_NB_NOEUDS+1][MAX_NB_NOEUDS+1];
bool marque[MAX_NB_NOEUDS+1][MAX_NB_NOEUDS+1];
vector<int> vois[MAX_NB_NOEUDS+1];
bool parcouru[MAX_NB_NOEUDS+1];
int nbNoeuds, nbArcs, nbChemins, iSource, iPuit;
stack<int> chemin;
int longueurChemin;
int nbResultat = 0;
int resultat[10000][2;]


int main(void){
    lireEntree();
    for(int iChemin = 0; iChemin < nbChemins; iChemin++){
        for(int iNoeud = 1; iNoeud <= nbNoeuds; iNoeud++)
            parcouru[iNoeud] = false;
        trouverCheminAugmentant(iSource);
    }
    for(int iChemin = 0; iChemin < nbChemins; iChemin++){
        for(int iNoeud = 1; iNoeud <= nbNoeuds; iNoeud++)
            parcouru[iNoeud] = false;
        trouverCheminDiminuant(iSource);
        printf("%d\n", (int)(chemin.size()));
        vector<int> chem;
        while(!chemin.empty()){
            //printf("%d\n", chemin.top());
            chem.push_back(chemin.top());
            chemin.pop();  
        }

        longueurChemin = 0;  
    }
    return 0;
}

void lireEntree(){
    scanf("%d%d", &nbNoeuds, &nbArcs);
    for(int iArc = 0; iArc < nbArcs; iArc++){
        int iNoeud1, iNoeud2, valeur;
        scanf("%d%d%d", &iNoeud1, &iNoeud2, &valeur);
        vois[iNoeud1].push_back(iNoeud2);
        vois[iNoeud2].push_back(iNoeud1);
        initial[iNoeud1][iNoeud2] = valeur;
    }
    iSource = 1;
    iPuit = nbNoeuds;
}

bool    trouverCheminAugmentant(int iNoeud){
    if(iNoeud == iPuit)
        return true;
    for(int iVois = 0; iVois < (int)(vois[iNoeud].size()); iVois++){
        int iFils = vois[iNoeud][iVois];
        if( (!marque[iNoeud][iFils] && initial[iNoeud][iFils]) || marque[iFils][iNoeud] )
            if(!parcouru[iFils]){
                parcouru[iFils] = true;
                if(trouverCheminAugmentant(iFils)){
                    marque[iNoeud][iFils] = !marque[iFils][iNoeud];
                    marque[iFils][iNoeud] = false;
                    return true;     
                }
            }
    }
    return false;
}

bool    trouverCheminDiminuant(int iNoeud){
    if(iNoeud == iPuit){
        chemin.push(iNoeud);
        return true;
    }
    for(int iVois = 0; iVois < (int)(vois[iNoeud].size()); iVois++){
        int iFils = vois[iNoeud][iVois];
        if(marque[iNoeud][iFils] && !parcouru[iFils]){
            parcouru[iFils] = true;
            if(trouverCheminDiminuant(iFils)){
                chemin.push(iNoeud);
                marque[iNoeud][iFils] = false;
                return true;     
            }
        }
    }
    return false;
}

/*

4 5
1 2 4
2 4 1000
2 3 7
1 3 2
3 4 1

*/