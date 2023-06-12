// 该程序实现了习题2.18中把两个递增列表归并为递减的功能
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
// 思路：遍历链表，如果发现下一个元素与上一个元素相等，就删除该结点(i-1个结点的后继指向i+1)

//思路一：先将两表合并再逆置
//思路二：创建一个新链表，同时进行两表的遍历，每一次遍历把较小的值用头部插入法插入新链表，实现需要的功能

//写一个用于头部插入的函数，用于复用
void head_insert(LList &L,LList head){
    head -> next = L -> next;
    L -> next = head;
}


void combine_newllst_lower(LList &A, LList &B) {
    LList p = A->next;  // p为A的第一个结点
    LList r = B->next;  // r为B的第一个结点
    LList C;ListInit(C);
    while(p && r){
        if(p->data > r->data){    //if-else为判断元素大小的语句，如果小就头部插入新链表
            LList temp = r -> next;
            head_insert(C,r);
            r = temp;
        }
        else{
            LList temp = p -> next;
            head_insert(C,p);
            p = temp;
        }
    }                             //下面处理A或者B中两个链表长度不一样的情况，谁先遍历完了，就把没遍历完的部分头部插入新链表
    if (r == NULL){
        while(p){
            LList temp = p -> next;
            head_insert(C,p);
            p = temp;
        }
    } else{
        while(r){
            LList temp = r -> next;
            head_insert(C,r);
            r = temp;
        }
    }
    A -> next = NULL;
    B -> next = NULL;
    A = C;
}

int main()
{
    LList A, B;
    int n,m;
    cin >> n >> m; // 输入n，n为链表的长度，案例中n=4
    int a[n], b[m];
    for (int i = 0; i < n; i++)    cin >> a[i];
    for (int i = 0; i < m; i++)    cin >> b[i]; 
    // 链表的初始化
    ListInit(A); 
    ListInit(B);
    // 链表的创建
    ListCreat(A, n, a);ListCreat(B, m, b);
    // 进行插入
    // 打印链表
    combine_newllst_lower(A,B);
    ListTraverse(A);
}
