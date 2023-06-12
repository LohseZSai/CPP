//该程序实现了习题2.15中的把单链表就地逆置的功能
//姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include<iostream>
using namespace std;
typedef int LElemType;
//构建单链表的数据类型，并实现基础的功能，如求长度、元素的查找、删除、插入等功能

typedef struct LNode{
    LElemType data;
    LNode * next;
}*LList;
//单链表的初始化
void ListInit(LList &L){
    L = new LNode;L->next = NULL;
}

//单链表的建立与元素存储
void ListCreat(LList &L, int n, LElemType a[]){
    LList p;
    int i;
    L = new LNode;
    L -> next = NULL;
    for(i=n-1;i>=0;i--){
        p = new LNode; 
        p -> data = a[i];              //定数据域
        p -> next = L -> next;         //定指针域，完成了对数据的插入
        L -> next = p;                 //表示L的下一个指针是P
    }
}
//获取单链表的长度
int length(LList L){
    LList p;
    int i;
    for(i=0,p=L->next;p;i++) p = p -> next;//初始化：让p为第一个结点，若p非空，就继续指向下一个结点
    return i;
}
//思路：使用表头或表尾插入法来实现链表的逆置

//表头插入法
void ListReverse_from_head(LList &L){//n为链表的长度
    LList p = L->next; // 指向第一个结点
    L->next = NULL; // 将头结点与原链表断开
    while(p){
        LList q = p->next; // 保存下一个结点
        p->next = L->next; // 将当前结点插入到头结点之后
        L->next = p;
        p = q; // 继续遍历原链表
    }
}

//实现链表的打印
void ListTraverse(LList &L)
{
	LList p;
	for(p=L->next;p;p=p->next)     cout<<p->data<<" ";
}


int main(){
    LList L;
    int n;
    cin >> n; //输入n，n为链表的长度，案例中n=4
    int a[n];
    for(int i=0;i<n;i++) cin >> a[i];
    //链表的初始化
    ListInit(L);
    //链表的创建
    ListCreat(L,n,a);
    //进行逆置
    ListReverse_from_head(L);
    //打印链表
    ListTraverse(L);
}


