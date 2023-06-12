#include <bits/stdc++.h>
using namespace std;
int a[10005];

//首先完成输入功能，n为世界的宽度
int main(){
    int n, maxn = 0,ans = 0;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
        maxn = max(a[i], maxn);
    }//完成对世界的填充,并且得到世界的最高层数
    //下面完成对每一层的遍历
    for(int i=0;i<=maxn;i++){
        //每一层遍历要完成的任务：last用于标记两个 土地块之间的距离
        int last = -1;//last为什么要等于-1？因为不等于-1的话无法标记第一个土地块
        for(int j=0;j<n;j++){//第二个条件表示的是循环的终止条件，如果是<n，为n次循环，如果是<=n,为n+1次循环
             if(a[j]>=i){
                if(last!=-1) ans += j - last - 1;
                //确认last=-1的原因是希望看出是不是第一个土地块
                last = j;
             }
             
        }
    }
    cout << ans;
    return 0;

}
