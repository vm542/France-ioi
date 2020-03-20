#include <iostream>

using namespace std;

unsigned long long triangle[101][101];

int     main(void){
    int n, p;
    cin >> n >> p;
    triangle[0][0] = 1;
    for (int i = 1 ; i < 101 ; i++){
        for (int j = 0 ; j < i + 1 ; j++){
            if (j != 0)
                triangle[i][j] = triangle[i - 1][j] + triangle[i - 1][j-1];
            else
                triangle[i][j] = triangle[i - 1][j];
        }
    }
    cout << triangle[n][p];
    return(0);
}
