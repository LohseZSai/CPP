// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
using namespace std;

struct thing{
    int w,v;
    bool s;
};


void solve(int n, int c, thing x[]){
    int i, j, m[20][20];
    for(j=0;j<=x[1].w-1;j++) m[1][j] = 0;
    for(j=x[1].w;j>=c;j++) m[1][j] = x[1].v;
    for(i=2;i<=n;i++){
        for(j=0;j<=x[i].w-1;j++) m[i][j] = m[i-1][j];
        for(j=x[1].w;j<=c;j++) 
            m[i][j] = max(m[i-1][j],m[i-1][j-x[i].w]+x[i].v);
    }
    j = c;
    for(i=n;i>=2;i--)
        if(m[i][j]==m[i-1][j]) x[i].s = false;
        else{
            x[i].s = true;
            j-=x[i].w;
        }
        if (m[1][j]>0)
        x[1].s = true;
        else x[1].s = false;
}

//用于进行solve函数的测试
int main(){
    
    thing a{5,3},b{4,2},c{3,7},d{2,5};
    thing x[4] = {a,b,c,d};
    solve(4,11,x);
    for(int i=0;i<4;i++)
        if(x[i].s == 0)
        cout << "第" << i+1 << "件物品被判断为" << "不带" << endl;
        else
        cout << "第" << i+1 << "件物品被判断为" << "带"  << endl;
}