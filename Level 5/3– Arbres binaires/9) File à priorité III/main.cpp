#include <queue>
#include <stdio.h>

using namespace std;

struct compare{  
    bool operator()(const int& l, const int& r){  
        return l > r;  
    }  
};  

int     main(void){
    int     nbRequetes;
    scanf("%d", &nbRequetes);
    priority_queue<int,vector<int>,compare> tas; 
    for (int i = 0 ; i < nbRequetes ; i++){
        char    requete;
        int     valeur;
        scanf(" %c", &requete);
        if (requete == 'I'){
            scanf("%d", &valeur);
            tas.push(valeur);
        }
        else{
            if (tas.empty())
                printf("-\n");
            else{
                printf("%d\n", tas.top());
                tas.pop();
            }
        }
    }
    return (0);
}