#include <stdio.h>
#include <math.h>
#include <algorithm>

using namespace std;

class   Noeud{
    public:
        int gauche, droite, valeur = -1;
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
    int     milieu = gauche + (droite - gauche) / 2;
    creerArbre(indice * 2, gauche, milieu);
    creerArbre(indice * 2 + 1, milieu + 1, droite);
}

int     afficher(int indice, int valeur){
    if (indice < 1 || valeur != -1)
        return (valeur);
    return (afficher(indice / 2, arbre[indice].valeur));
}

void    fixer(int indice, int gauche, int droite, int valeur){
    if (gauche > droite)
        return;
    int     milieu = arbre[indice].gauche + (arbre[indice].droite - arbre[indice].gauche) / 2;
    
    if (arbre[indice].gauche <= gauche && arbre[indice].droite >= droite){
        fixer(indice * 2, gauche, milieu, arbre[indice].valeur);
        fixer(indice * 2 + 1, gauche, milieu, arbre[indice].valeur);
        arbre[indice].valeur = -1;
        return;
    }

    if (arbre[indice].gauche == gauche && arbre[indice].droite == droite){
        arbre[indice].valeur = valeur;
        return;
    }
    fixer(indice * 2, gauche, milieu, valeur);
    fixer(indice * 2 + 1, milieu + 1, droite, valeur);
}

int     main(void){
    scanf("%d%d", &tailleTableau, &nbRequetes);
    tailleTableau = pow(2, tailleTableau);
    creerArbre(1, 0, tailleTableau - 1);
    while (tailleArbre < tailleTableau)
        tailleArbre *= 2;
    for (int i = 0 ; i < nbRequetes ; i++){
        char    requete;
        int     indice, gauche, droite;
        scanf(" %c%d", &requete, &indice);
        if (requete == 'M'){
            scanf("%d%d", &gauche, &droite);
            fixer(1, indice, gauche, droite);
        }
        else
            printf("%d\n", afficher(tailleArbre + indice, arbre[tailleArbre + indice].valeur));
    }
    return (0);
}