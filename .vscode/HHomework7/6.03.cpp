// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
using namespace std;


void solve(int n, int r[], int m[][20], int c[][20]){
    int i, j, k, s, t;
    for(i = 1;i <= n;i++){m[i][i] = 0;c[i][i] = 0;}
    for(i = 1;i <= n - 1;i++){
        m[i][i+1] = r[i]*r[i+1]*r[i+2];
        c[i][i+1] = i;
    }
    for(s = 2;s <= n-1;s++)
        for(i = 1;i <= n-s;i++){
            j = i + s;
            for(k = i;k <= j-1;k++){
                t = m[i][k] + m[k+1][j] + r[i]*r[k+1]*r[j+1];
                if(k == i || t < m[i][j]){
                    m[i][j] = t;
                    c[i][j] = k;
                }
            }
    }
}
//整数转化为字符串的函数
string inttostr(int i){
    string result;
    bool isnegative;
    if(i < 0) isnegative = true;
    else isnegative = false;
    while(i > 0){
        char single = '0' + (i % 10);
        result += single;
        i /= 10;
    }
    if(isnegative) result = '-' + result;
    return result;
}


string combine(int c[][20], int i, int j){
    if(i == j) return "A" + inttostr(i);
    return "(" + combine(c,i,c[i][j]) + "*" + combine(c,c[i][j]+1,j) + ")";
}

string expression(int c[][20],int n){
    return combine(c,1,c[1][n]) + "*" + combine(c,c[1][n]+1,n);
}


int main() {
    int n = 4;  // 矩阵的个数
    int r[] = {0, 5, 20, 50, 1, 100};  // 每个矩阵的行数和列数
    int m[20][20] = {0};  // 存储中间计算结果的数组
    int c[20][20] = {0};  // 存储中间计算结果的数组

    solve(n, r, m, c);  // 求解矩阵连乘问题

    string matrixExpression = expression(c, n);  // 构建矩阵连乘的表达式
    cout <<  matrixExpression << endl;

}
