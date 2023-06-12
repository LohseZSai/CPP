#include <bits/stdc++.h>
using namespace std;
int a[10005];

int main(){
    int n, maxn = 0, ans = 0;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];     //记忆：in大大out小小
        maxn = max(maxn, a[i]);
    }
    //上面的代码时为了计算出最高的层数，以便于循环遍历
    for(int i=0;i<=maxn;i++){
        //层数遍历，i是层数
        int last = -1;
        for(int j=0;j<n;j++){
            
            if(a[j]>=i){
                if (last != -1)
                ans += j - last - 1;
                last = j;
                }
            }
        }
        cout << ans;
        return 0;
    }