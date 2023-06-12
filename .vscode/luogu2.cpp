#include <iostream>
using namespace std;
bool check(int a[], int length, int b)
{
    for (int i = 0; i < length; i++)
    {
        if (a[i] == b)
            return true;
    }
    return false;
}

int main()
{
    // 首先实现输入功能
    int n, maxn = 0;
    int ans[100] = {0};
    cin >> n;
    int a[n] = {0};
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        maxn = max(a[i], maxn);
    }
    // for(int i=0;i<n;i++)
    //     cout << a[i];
    // 输入功能完成
    // 建立一个N*N的矩阵用于存储相加的数据
    int data[n][n];
    // 建立答案矩阵，并且初始化为0
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            data[i][j] = 0;
    }
    // 向data中输入值
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            data[i][j] = a[i] + a[j];

            if (check(a, n, data[i][j]) == false)
            {
                data[i][j] = 0;
            }

            // 如果在原始数据里找不到相加后的值，去掉该值

            if (data[i][j] > maxn)
                data[i][j] = 0;
        }
        data[i][i] = 0;
    }
    int count = 0;
    // 此时还要进行答案的筛选去除，如果data里相加得到的数字不是原来的几个数之一，那么必须去掉
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (data[i][j] != 0)
                ans[data[i][j]] = 1;
        }
    }
    // ans里的数据一定是data里的！
    // 接下来进行比对，data里的数据不属于ans就去掉。
    for (int i = 0; i < maxn + 1; i++)
    {
        if (ans[i] == 1)
        {
            count += 1;
        }
    }
    cout << count;
}
