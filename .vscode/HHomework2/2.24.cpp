// 该程序实现了习题2.24中把链表的偶数部分反序放在链表前一部分，奇数部分放在链表后一部分的功能
// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
using namespace std;
typedef int LElemType;
// 构建单链表的数据类型，并实现基础的功能，如求长度、元素的查找、删除、插入等功能

typedef struct LNode
{
    LElemType data;
    LNode *next;
} *LList;
// 单链表的初始化
void ListInit(LList &L)
{
    L = new LNode;
    L->next = NULL;
}

// 单链表的建立与元素存储
void ListCreat(LList &L, int n, LElemType a[])
{
    LList p;
    int i;
    L = new LNode;
    L->next = NULL;
    for (i = n - 1; i >= 0; i--)
    {
        p = new LNode;
        p->data = a[i];    // 定数据域
        p->next = L->next; // 定指针域，完成了对数据的插入
        L->next = p;       // 表示L的下一个指针是P
    }
}
// 获取单链表的长度
int length(LList L)
{
    LList p;
    int i;
    for (i = 0, p = L->next; p; i++)
        p = p->next; // 初始化：让p为第一个结点，若p非空，就继续指向下一个结点
    return i;
}
// 实现链表元素的删除，删除即改变某个结点的后继即可
bool ListDelete(LList &L, int i)
{
    LList p, q;
    int j;
    if (i < 1)
        return false; // 删除位置不合适
    for (j = 0, p = L; p->next && j < i - 1; p = p->next, j++)
        ; // 找第i-1个结点
    if (!p->next)
        return false; // 删除位置不合理
    q = p->next;
    p->next = q->next;
    delete q;
    return true;
}

// 实现链表的打印
void ListTraverse(LList &L)
{
    LList p;
    for (p = L->next; p; p = p->next)
        cout << p->data << " ";
}

//实现链表的销毁
void LListDestroy(LList& L) {
    LList p = L, temp;
    while (p != NULL) {
        temp = p;
        p = p->next;
        delete temp;
    }
    L = NULL;
}
//思路2：遍历元素，如果是偶数个结点头部插入新链表，奇数个结点就尾部插入新链表
void odd_and_even_elem_inlinklist(LList &A,LList &B) {
   LList p = A -> next;
   LList q = B;
   int count = 1;
   while(p){
    LList temp = p -> next;
    if(count % 2 != 0){//如果奇数个结点就尾部插入链表
        
        q -> next = p;
        q = q -> next;
        p = temp;
        q -> next = NULL;//断开后面的结点
    }
    else{//如果是偶数个结点就头部插入             **插入时先考虑后继再看前面
        p -> next = B -> next;
        B -> next = p;
        p = temp;
    }
    count += 1;
   }
}

int main()
{
    LList A,B,C;
    int n;
    cin >> n; // 输入n，n为链表的长度，案例中n=4
    int a[n];
    for (int i = 0; i < n; i++)    cin >> a[i];
    // 链表的初始化
    ListInit(A);ListInit(B); 
    // 链表的创建
    ListCreat(A, n, a);
    // 进行操作
    odd_and_even_elem_inlinklist(A,B);
    // 打印链表
    ListTraverse(B);
}
