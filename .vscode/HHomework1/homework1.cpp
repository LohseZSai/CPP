// 该程序实现了习题2.09中的元素>x进行删除的功能
// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
// #include<vector>思路二中使用到该库
using namespace std;
typedef int LElemType;
//构建线性表的数据类型，并且实现初始化、创建、遍历等功能
const int ListInitSize = 105;
const int ListInc = 105;

struct SList{
    LElemType *elem;
    int length, listsize;   //创建SList并规定数据类型，元素、长度和内存大小
};

//顺序表的初始化
bool ListInit(SList &L){
    L.elem = new LElemType[ListInitSize];
    if (!L.elem) return false;
    L.length = 0;
    L.listsize = ListInitSize;
    return true;
}
//顺序表的创建、元素的存储
bool ListCreat(SList &L,int n,LElemType a[]){
    int i;
    L.elem = new LElemType[n + ListInitSize];
    if(!L.elem) return false;
    L.length = n;
    L.listsize = n + ListInitSize;
    for(i=0;i<n;i++) L.elem[i] = a[i];
    return true;
}
//元素的访问
void visit(LElemType e){
    cout << e << " ";
}
//元素的遍历，访问作为形参
void ListTraverse(SList &L, void visit(LElemType e)){
    int i;
    for(i=0;i<L.length;i++) visit(L.elem[i]);
}


//元素的筛选删除
// 算法思路一：遍历线性表，将大于x的元素赋值为0，再进行移动，最后输出不为0的值(低效算法)
// 算法思路二：创建一个vector，用于储存满足条件的值，最后直接输出即可
// 算法思路三：创建一个flag值用于对满足条件的值进行标记，并通过赋值来实现元素的移动，最终打印时使用flag，完成对元素的“删除”（采纳该思路）


// 思路三实现
void delete_elments(SList &L,int x){
    int flag = 0;//flag用于标记，进行赋值，以及最后的输出，是本算法的核心   
    for(int i=0;i<L.length;i++){        
            if(L.elem[i] <= x) L.elem[flag++] = L.elem[i];
    //最后改变L.length就可以实现“删除”功能    
}
    L.length = flag;
}
int main(){
    int x,length;
    SList L;
    //完成原始数据的输入
    cin >> x >> length;   //输入案例为5 6
    int a[length]={0};   
    for(int i=0;i<length;i++)
        cin >> a[i];     //输入案例为 {3,7,1,5,9,4}
    //初始化顺序表
    ListInit(L);
    //创建顺序表
    ListCreat(L,length,a);
    //用函数完成数据的处理
    delete_elments(L,x);
    //完成任务，打印输出
    ListTraverse(L,visit);
    }