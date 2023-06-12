//该程序实现了习题2.12中的把重复元素删除的功能
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

//元素的比较，两个元素是否一样
bool compare(LElemType e1,LElemType e2){
    if (e1 == e2)
        return true;
    else 
        return false;
}

//元素的查找，是否存在于顺序表中
int ListLocate(SList L,LElemType e,bool compare(LElemType e1,LElemType e2)){
    int i = 1;
    while(i<=L.length && !compare(L.elem[i-1],e)) i++;
    if (i>L.length) i = 0; 
    return i;//如果存在返回元素的位序，否则返回0
}

//算法思路：用两个指针i和j，第一个指针i指向顺序表的第一位，第二个指针j指向第二位，
//第二个指针先进行循环，当找到不重复的元素时就进行a[i+1] = *j,从而避免重复移动

bool delete_comment_elem(SList &L){
    if(L.length <= 1) return false;
    int i = 0;
    for(int j=1;j<L.length;j++){  //j从1开始循环
        if(L.elem[j] != L.elem[i]) {
            i++;
            L.elem[i] = L.elem[j]; //将不相同的元素赋值给下一个位置
        }
    }
    L.length = i + 1;
    return true;
}




int main(){
    //进行顺序表的初始化和创建
    SList L;
    ListInit(L);
    int n,a[105]={0};  //案例为1 1 2 2 3 4 4 4 
    cin >> n;
    for(int i=0;i<n;i++) cin >> a[i];
    //输入顺序表的长度n，n在案例中为8
    ListCreat(L,8,a);
    //进行具体操作
    delete_comment_elem(L);
    //输出该顺序表
    for(int i=0;i<L.length;i++) {
        //发现错误出在这里，总会无端输出1个0，于是进行处理
    if (i == L.length-1 && L.elem[i] == 0) break; //如果是最后一个元素且为0，跳出循环
    cout << L.elem[i] << " ";
}
}