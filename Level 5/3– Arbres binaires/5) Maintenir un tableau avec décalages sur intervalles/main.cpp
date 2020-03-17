#include <stdio.h>
#include <math.h>

using namespace std;

class   Noeud{
    public:
        int gauche, droite, valeur = 0;
        Noeud(int gauche, int droite){
            this->gauche = gauche;
            this->droite = droite;
        }
        Noeud(){};
};

int     tailleTableau, nbRequetes;
int     tailleArbre = 1;
Noeud   arbre[524289];

void    creerArbre(int indice, int gauche, int droite){
    arbre[indice] = Noeud(gauche, droite);
    if (gauche >= droite)
        return;
    int     milieu = arbre[indice].gauche + (arbre[indice].droite - arbre[indice].gauche) / 2;
    creerArbre(indice * 2, gauche, milieu);
    creerArbre(indice * 2 + 1, milieu + 1, droite);
}

int     afficher(int indice, int valeur){
    if (indice < 1)
        return (valeur);
    return (afficher(indice / 2, valeur + arbre[indice].valeur));
}

void    decaler(int indice, int gauche, int droite, int valeur){
    if (gauche > arbre[indice].droite || droite < arbre[indice].gauche || gauche > droite)
        return;
    int     milieu = arbre[indice].gauche + (arbre[indice].droite - arbre[indice].gauche) / 2;
    if (gauche == arbre[indice].gauche && droite == arbre[indice].droite){
        arbre[indice].valeur += valeur;
        return;
    }
    if (droite < milieu)
        decaler(indice * 2, gauche, droite, valeur);
    else if (gauche > milieu)
        decaler(indice * 2 + 1, gauche, droite, valeur);
    else{
        decaler(indice * 2, gauche, milieu, valeur);
        decaler(indice * 2 + 1, milieu + 1, droite, valeur);
    }
}

int     main(void){
    scanf("%d%d", &tailleTableau, &nbRequetes);
    tailleTableau = pow(2, tailleTableau);
    creerArbre(1, 0, tailleTableau - 1);
    for (int i = 0 ; i < nbRequetes ; i++){
        char    requete;
        scanf(" %c", &requete);
        if (requete == 'D'){
            int valeur, gauche, droite;
            scanf("%d%d%d", &gauche, &droite, &valeur);
            decaler(1, gauche, droite, valeur);
        }
        else{
            int    indice;
            scanf("%d", &indice);
            printf("%d\n", afficher(tailleTableau + indice, 0));
        }
    }
    return (0);
}