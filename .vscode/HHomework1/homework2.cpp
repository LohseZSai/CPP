//该程序实现了习题2.10中的改变元素次序功能
//姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include<iostream>
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

void List_elementmove(SList &L,int length){
    int ans[length];
    int odd = 0,even = (length + 1)/2;
    for(int i=0;i<length;i++){
        if(i % 2 == 0)         //这个if-else判断是该算法的精髓
            ans[odd++] = L.elem[i]; //如果i是偶数，即循环到的元素是“第奇数个元素”
        else
            ans[even++] = L.elem[i]; //类似于上面的，最终完成“调换顺序”
    }   
    for(int i=0;i<length;i++) 
        L.elem[i] = ans[i];                            
}
// 思路1:创建两个新线性表用于储存值,最后进行拼接
// 思路2：只创建一个新列表用于储存值！   (采纳该思路)
int main(){
    //完成案例的输入
    int n;
    cin >> n;//n为线性表的长度，案例中为7
    int a[n]={0};
    for(int i=0;i<n;i++)
        cin >> a[i];  //输入案例为1 2 3 4 5 6 7
    //下面是程序的主体部分
    //初始化顺序表
    SList L;
    ListInit(L);
    //创建顺序表
    ListCreat(L,n,a);
    //用函数完成数据的处理
    List_elementmove(L,n);
    ListTraverse(L,visit);
}

//两个算法的比较：时间复杂度，感觉两个算法在时间复杂度上差不太多，但是在空间复杂度上，显然方法2更为优秀
