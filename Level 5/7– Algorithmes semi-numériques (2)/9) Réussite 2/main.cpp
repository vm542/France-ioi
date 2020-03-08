#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int     main(void){
    unsigned long long     n;
    cin >> n;
    vector<unsigned long long> diviseurs;
    for (unsigned long long i = 2 ; i <= sqrt(n) ; i++){
        if (n % i == 0){
            diviseurs.push_back(i);
            if (i != n / i)
               diviseurs.push_back(n / i);
        }
    }
    sort(diviseurs.begin(), diviseurs.end());
    for (int i = 0 ; i < diviseurs.size() ; i++){
        cout << diviseurs.at(i) << endl;
    }
    if (diviseurs.size() == 0)
       cout << "0";
    return (0);
}