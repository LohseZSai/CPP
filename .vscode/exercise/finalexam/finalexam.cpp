#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
typedef int LElemType;
typedef int ElemType;
//构建线性表的数据类型，并且实现初始化、创建、遍历等功能
const int ListInitSize = 105;
const int ListInc = 105;

struct SList{
    LElemType *elem;
    int length, listsize;   //创建SList并规定数据类型，元素、长度和内存大小
};

typedef int QElemType;
// 构建循环链队列的数据类型，并实现基础的功能，如求长度、元素的查找、删除、插入等功能

//定义结点类型
typedef struct QNode{
    QElemType data;
    QNode* next;
}*LQueuePtr;


//定义循环链队列的结构
struct LQueue{
    LQueuePtr rear;
    int length;
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

void ListTraverse(LList &L)
{
	LList p;
	for(p=L->next;p;p=p->next)     cout<<p->data<<" ";
}

typedef char SElemType;

const int StackInitSize = 105;
const int StackInc = 105;


//栈的定义
struct SStack {
    SElemType *base, *top;
    int stacksize;
};

//栈的初始化
bool StackInit(SStack &S){
    S.base = new SElemType[StackInitSize];
    if (!S.base) return false;
    S.top = S.base;
    S.stacksize = StackInitSize;
    return true;
}

//入栈操作
bool Push(SStack &S,SElemType e){
    SElemType *base;
    if (S.top - S.base == S.stacksize){
        base = (SElemType*)realloc(S.base,
        (S.stacksize + StackInc)* sizeof(SElemType));
        if (!base) return false;
        S.base = base; S.top = S.base + S.stacksize;  
        S.stacksize += StackInc;
    }
        *S.top = e;
        S.top++;
        return true;
    }


//顺序栈的出栈操作
bool Pop(SStack &S,SElemType &e){
    if (S.top == S.base) return false;
    S.top --; e = *S.top;
    return true;
}

bool Stackempty(SStack S){
    if (S.top == S.base) return true;
    else return false;
}



//2.09 删除大于x元素
void delete_elments(SList &L,int x){
    int flag = 0;//flag用于标记，进行赋值，以及最后的输出，是本算法的核心   
    for(int i=0;i<L.length;i++){        
            if(L.elem[i] <= x) L.elem[flag++] = L.elem[i];
    //最后改变L.length就可以实现“删除”功能    
}
    L.length = flag;
}

//2.10 第奇数个移到前面第偶数个移到后面
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

//2.11 保存递增顺序表的共同元素到新顺序表
void Opitimized_comment_elem_creat(SList &A,SList &B,SList &C){
    int i, j;
    int times = min(A.length,B.length),flag = 0;
    for(i=j=0;i< times;){
        if (A.elem[i] < B.elem[j]) i++;
        else if(A.elem[i] > B.elem[j]) j++;
        else {
            C.elem[flag++] = A.elem[i];
            i++; j++;
        }
    }
    C.length = flag;
}

//2.12 删除表中重复元素
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

//2.13把两个递增有序的顺序表归并为递减的顺序表
bool ListMerge(SList a, SList b, SList &c){
    int i, j, k;
    c.listsize = c.length = a.length + b.length;
    c.elem = new LElemType[c.listsize];
    if (!c.elem) return false;
    i = j = 0;
    k = c.length - 1;
    while(i < a.length && b.length){
        if(a.elem[i] < b.elem[j])
        {c.elem[k] = a.elem[i];i++;}
        else{c.elem[k] = b.elem[j];j++;}
        k--;
    }
    while(i<a.length){c.elem[k]=a.elem[i];}
    while(j<b.length){c.elem[k]=b.elem[j];}
    return true;
}

//2.14不同元素和相同元素分别存入顺序表并didi鞥
void CrossList(SList A,SList B,SList &C,SList &D){
    int a,b,c,d;
    D.listsize = C.listsize = A.length + B.length;
    C.elem = new ElemType[C.listsize];
    D.elem = new ElemType[D.listsize];
    a=0;b=0;c=0;d=0;
    while(a<A.length && b < B.length)
        if(A.elem[a] = B.elem[b]){
            C.elem[c] = A.elem[a]; a++; b++;
        }
        else if(A.elem[a] < B.elem[b]){
            D.elem[d] = A.elem[a]; a++; d++;
        }
        else{
            D.elem[d] = A.elem[a];a++;d++;
        }
    while(a < A.length){
        D.elem[d] = A.elem[a];a++;d++;
    }
    while(b < B.length){
        D.elem[d] = B.elem[b];b++;d++;
    }
    C.length = c; D.length = d;
}

//2.15 对单链表实行就地逆置
void ListReverse_from_head(LList &L){//n为链表的长度
    LList p = L->next; 
    L->next = NULL; 
    while(p){
        LList q = p->next; p->next = L->next; L->next = p;
        p = q; 
    }
}

//2.16 删除链表中重复元素
void PurgeLList1(LList &L){
    LList p,r,s;
    r = L;p = L->next;
    while(p){
        if(r==L||p->data > r -> data){
    r->next=p;r=p;p=p->next;}
    else{
        s=p;p=p->next;delete s;
    }
    r -> next = NULL;
    }
}

//2.17把两个链表合并为一个链表，要求元素交错排列
void cross_creat_newlinklist(LList &A, LList &B,LList &C) {
    LList p,q,r;
    int i = 0;
    p = A -> next;
    q = B -> next;
    r = C = A;
    delete B;
    while(p && q){
        if(p && i % 2 == 0){r->next=p;r=p;p=p->next;}
        else if(q && i%2!=0){
            r->next=q;r=q;q=q->next;
        }
        i+=1;
    }
    r->next=p?p:q;
}

//2.18 把两个递增有序的单链表归并为递减的单链表
void UnionList(LList &A,LList &B,LList &C){
    LList p,q,r;
    C=A;p=A->next;A->next=NULL;q=B->next;delete B;
    while(p && q){
        if(p->data<q->data){r = p;p = p ->next;}
        else{r = p; q = q -> next;}
        r->next = C->next; C->next = r;
    }
    if(!p) p=q;
    while(p){
        r=p;p=p->next;r->next=C->next;C->next=r;
    }
}

//2.19 删除单链表的第偶数个元素
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
    q = p->next;p->next = q->next;delete q;return true;
}

//2.20 删除单链表中元素为e的结点 跟上面差不多，略
//2.21 按元素的奇偶次序分割链表
void odd_and_even_elem_inlinklist(LList &L,LList &A,LList &B) {
    LList p = L -> next;LList q = A;LList r = B;
    int count = 1;//定义该计数器标记链表的位置
    while(p){
        LList temp = p -> next;//定义临时节点
        if (count % 2 != 0) {
            q -> next = p;q = q -> next;p = temp;  
        } 
         else {
            r -> next = p;r = r -> next;p = temp;    
        }
        count += 1;
    }q -> next = NULL;r -> next = NULL;
}

//2.22 按元素e分割链表
void ListSplit(LList &L,LList &A,LList &B,ElemType e){
    LList p,q,r;p=L->next;A=L;q=A;
    B=new LNode;r=B;
    while(p)
        if(p->data <= e){q->next;q=p;p=p->next;}
        else r->next=p;r=p;p=p->next;
        q->next=NULL;r->next=NULL;
}

//2.23归并3个链表
void ListUnion3(LList &L,LList &A,LList &B,LList &C){
    LList p,q,r,s;p=A->next;q=B->next;r=C->next;
    L=A;s=L;delete B;delete C;
    while(p && q && r)
        if(p->data<=q->data && p->data <= r->data)
        {s->next=p;s=p;p=p->next;}
        else if(q->data<=p->data && q->data<=r->data)
        {s->next=p;s=q;q=q->next;}
        else
        {s->next=r;s=r;r=r->next;}
        if(!p) p=r;else if (!q) q=r;
        while(p&&q)
            if(p->data<=q->data){s->next=p;s=p;p=p->next;}
            else{s->next=q;s=q;q=q->next;}
            s->next=p?p:q;
}

//2.24 把位序为奇数的元素放在后半部分，保持原来的相对次序
void odd_and_even_elem_inlinklist(LList &A,LList &B) {
   LList p = A -> next;LList q = B;int count = 1;
   while(p){
    LList temp = p -> next;
    if(count % 2 != 0){
        q -> next = p;q = q -> next;p = temp;q -> next = NULL;//断开后面的结点
    }
    else{//如果是偶数个结点就头部插入             **插入时先考虑后继再看前面
        p -> next = B -> next;B -> next = p;p = temp;
    }count += 1;}
}

//2.25 循环链队列的初始化入队出队
//循环链队列的初始化
void QueueInit(LQueue &Q){
    Q.rear = new QNode;Q.rear -> next = Q.rear;Q.length = 0;
}
//循环链队列的入队
void Enqueue(LQueue &Q,QElemType e){
    LQueuePtr p = new QNode;
    p -> data = e;  p -> next  = Q.rear -> next;                         //尾部插入队尾
    Q.rear -> next = p;Q.rear = p; Q.length ++;   
}
//循环链队列的出队，因为只定义了尾指针，出队的元素是尾指针的前驱结点
bool Dequeue(LQueue &Q,QElemType &e){
    if(Q.rear->next==Q.rear) return false;
	LQueuePtr p; p = Q.rear->next; Q.rear->next = p->next;  
	e = p -> data; delete p;return true;
}

//2.26识别依次输入的字符序列是否符合这个对称模式
bool match(char x[]){
    SStack S;int i;SElemType c,d;bool f;
    StackInit(S);f = true;
    for(i=0;x[i];i++){
        c = x[i];
        if(c=='&') f=false;
        else if(c=='&') break;
        else if(f) Push(S,c);
        else if(!Pop(S,d)||d!=c) return false;
    }return !f && Stackempty(S);
}

//2.27括号匹配
bool check_it_or_not_pattern(char* a){
    char* p = a;
    SStack(S);StackInit(S);
    for(;*p != '\0';p++){
        if (*p == '(' || *p == '[' || *p == '{')  Push(S, *p);
        SElemType e;
        if (*p == ')' || *p == ']' || *p == '}'){
            if(Stackempty(S) == true) return false;Pop(S, e);
            if(*p == ')' && e == '(' || *p == ']' && e == '[' || *p == '}' && e == '{') {
                continue;
            }
            else return false;
        }
    }
    if(Stackempty(S) == false) return false;
    return true;
}

//2.29循环顺序队列的初始化求长度入队和出队
// void QueueInit(CSQueue &Q)
// {
//     Q.rear = -1;  // 初始化为空，队尾指针指向-1
//     Q.length = 0;
// }
// int lengthofque(CSQueue &Q)
// {
//     return Q.length;     
// }       
// bool Enqueue(CSQueue &Q,int e)                   
//     //循环顺序表的入队函数
// {
//    if(Q.length == MaxQSize) return false;//队列已满，不能再入队了
//    Q.rear = (Q.rear + 1) % MaxQSize;
//    Q.elem[Q.rear] = e;
//    Q.length++;
//    return true;
// }
// bool Dequeue(CSQueue &Q,int &e)                   
// //出队函数
// {
//     if(Q.length == 0) return false;//如果队列的长度为0，则返回false
//     e = Q.elem[(Q.rear - Q.length + 1 + MaxQSize) % MaxQSize]; // 取出队头元素
//     Q.length--;
//     return true;
// }



