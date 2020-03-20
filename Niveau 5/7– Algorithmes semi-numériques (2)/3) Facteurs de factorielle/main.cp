#include <iostream>
#include <math.h>

using namespace std;

int     n, p;

int     main(void){
    cin >> n >> p;
    unsigned long long res = 0;
    int     t = p;
    int     i = 1;
    while (n >= pow(p, i)){
        res += n / pow(p, i);
        i++;
    }
    cout << res;
}
