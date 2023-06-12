#include <iostream>
#include <cstring>
using namespace std;
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    int data[n][m];
    int count[k][m];
    memset(count, 0, sizeof(count));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> data[i][j];
    for(int j = 0;j < m;j++){
        for(int i=0;i<n;i++){
         count[data[i][j]-1][j] = 1;//实现计数
        }
    }
    for(int i=0;i<k;i++){
        int sum = 0;
        for (int j=0;j<m;j++){
            sum += count[i][j];
        }
        cout << sum << " ";
    }
    return 0;
}

//好开心！！！用c++做出的第一道题
