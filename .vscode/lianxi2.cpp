#include <bits/stdc++.h>
using namespace std;
int c[10005]={0},b[10005],a[10005];
//创建两个数组，第一个a为地图，第二个为存储方向的数组
int main(){
    //完成数据的输入，首先输入的是车的数量和时间
    int car_num, time;
    cin >> car_num >> time;
    //然后是循环，完成对a数组和b数组的输入
    for(int i=0;i<car_num;i++){
        cin >> b[i];
    }
    //测试看该功能是否成功
    // cout << "Array a: ";
    // for(int i = 0; i < car_num; i++){
    //     cout << a[i] << " ";
    // }
    // cout << endl;

    // cout << "Array b: ";
    // for(int i = 0; i < car_num; i++){
    //     cout << b[i] << " ";
    // }
    //在完成输入之后，实现车车的移动，进行循环，设定循环次数为t次
    //把每辆车的位置赋值成1
    //开始把问题想的过于复杂了，其实只要考虑最后的位置就行，然后倒序输出
    for(int i=0;i<car_num;i++){
        int result;
        result = b[i] * time + a[i];
        c[i] = result;
    }
    for(int i=0;i<car_num;i++){
        int number = a[i];
        for(int j=0;j<car_num;j++){
            if(a[j] == number){
                b[j] = 0;
            }
        }
        
    }
    }