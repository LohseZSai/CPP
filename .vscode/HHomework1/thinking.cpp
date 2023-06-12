//实现一下链表的交叉插入
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

// 思路：遍历链表，如果发现下一个元素与上一个元素相等，就删除该结点(i-1个结点的后继指向i+1)
void ListDel_Commonelem(LList &L){
    LList p,q;
    for(p=L->next;p->next;){
        //查看该元素与下一个元素是否相等，若相等删除该结点（前提是递增链表，才会有这样的情况）
        if (p->data == p->next->data){ 
            q = p->next; //记录下一个结点
            p->next = q->next; //i-1个结点的后继指向i+1
            delete q; //删除结点i
        } else {
            p = p->next; //继续往下遍历
        }
    }
    //再做一次判断和删除操作，以确保最后一个重复元素也被删除(如果最后一个元素重复的情况，删不掉)
    if (p && p->next && p->data == p->next->data) {
        q = p->next;
        p->next = q->next;
        delete q;
    }
} 

void cross_creat_newlinklist(LList &A, LList &B) {
    LList p = A->next;  // p为A的第一个结点
    LList q = p->next;  // q为p的后继结点
    LList r = B->next;  // r为B的第一个结点

    while (p != NULL && r != NULL) {  // 循环条件：两个链表都还有元素
        LList s = r;  // 复制结点r用于插入
        r = r->next;  // 使r指向B链表中的下一个元素

        LList temp = p->next;  // 保存p节点的下一个节点
        p->next = s;  // 插入临时节点s，使p的后继是s
        s->next = temp;  // 使s的后继是p节点的下一个节点，至此元素的插入完成

        p = p->next;  // p指向原链表内的下一个元素
        q = q->next;  // q指向原链表内的下一个元素
    }

    if (r != NULL) {  // 如果B链表还有元素
        p->next = r;  // 直接将剩余元素连接到A链表的末尾
    }
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
    cross_creat_newlinklist(A, B);
    // 打印链表
    ListTraverse(A);
}
