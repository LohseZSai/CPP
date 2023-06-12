// 该程序实现了习题2.17中进行交叉的功能
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

//参考书上的merge函数进行操作
void cross_creat_newlinklist(LList &A, LList &B,LList &C) {
    LList p,q,r;
    int i = 0;
    p = A -> next;
    q = B -> next;
    r = C = A;
    delete B;
    while(p && q){
        if(p && i % 2 == 0){
            r -> next = p;
            r = p;
            p = p -> next;
            
        }
        else if(q && i % 2 != 0){
            r -> next = q;
            r = q;
            q = q -> next;
        }
        i += 1;
    }
    r -> next = p ? p : q;

}
// void cross_creat_newlinklist(LList &A, LList &B,LList &C) {
//     LList p = A->next;  // p为A的第一个结点
//     LList r = B->next;  // r为B的第一个结点

//     while (p != NULL && r != NULL) {  // 循环条件：两个链表都还有元素
//         LList s = r;  // 复制结点r用于插入
//         r = r->next;  // 使r指向B链表中的下一个元素
//         LList temp = p->next;  // 保存p节点的下一个节点
//         p->next = s;  // 插入临时节点s，使p的后继是s
//         s->next = temp;  // 使s的后继是p节点的下一个节点，至此元素的插入完成
//         p = temp;  // p指向原链表内的下一个元素
//     }

//     // if (r != NULL) {  // 如果 B 链表还有剩余元素，直接接在 A 链表的末尾
//     //     LList pEnd = A;
//     //     while (pEnd->next != NULL) {//寻找尾节点
//     //         pEnd = pEnd->next;
//     //     }
//     //     pEnd->next = r;
//     // }
// }


int main()
{
    LList A, B, C;
    int n,m;
    cin >> n >> m; // 输入n，n为链表的长度，案例中n=4
    int a[n], b[m];
    for (int i = 0; i < n; i++)    cin >> a[i];
    for (int i = 0; i < m; i++)    cin >> b[i]; 
    // 链表的初始化
    ListInit(A); 
    ListInit(B);
    ListInit(C);
    // 链表的创建
    ListCreat(A, n, a);ListCreat(B, m, b);
    // 进行插入
    cross_creat_newlinklist(A, B, C);
    // 打印链表
    ListTraverse(C);

}
