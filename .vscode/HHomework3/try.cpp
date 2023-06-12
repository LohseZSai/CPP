#include<bits/stdc++.h>
using namespace std;

int n, num;
int mem[1000000]; // 定义一个大小为 1000000 的记忆数组，初始化为 0

int judge(int x) {
    if (mem[x] != 0) { // 如果已经计算过，直接返回结果
        return mem[x];
    }
    int ans = 1;
    for (int i = 1; i <= x/2; i++) {
        ans += judge(i); // 递归调用 judge 函数，并将结果累加到 ans 中
    }
    return mem[x] = ans; // 将结果存入记忆数组中，并返回结果
}

int main() {
    cin >> n;
    num = judge(n); // 调用 judge 函数，并将结果保存在 num 变量中
    cout << num << endl;
    return 0;
}