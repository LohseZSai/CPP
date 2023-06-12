// 该程序实现了习题3.31中判断完全二叉树的功能
// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
using namespace std;
const int MaxTreeSize = 100;
const int MaxQSize = 20;
typedef char TElemType;
//LElemType 限定类型
//TElemType 普通类型

typedef struct BiTNode{
    TElemType data;
    BiTNode *lc, //左孩子
            *rc; 
}*BiTree;


struct SqTree{
    TElemType bt[MaxTreeSize + 1];
    int n;
};//该结构体用于储存二叉树的元素


void visit(TElemType e){
    cout << e << " ";
}

typedef char QElemType;
// 构建循环链队列的数据类型，并实现基础的功能，如求长度、元素的查找、删除、插入等功能

struct CSQueue                  
{
    int rear, length;    
    BiTree elem[MaxQSize];         
    //设置尾指针和长度
};
void QueueInit(CSQueue &Q)
{
    Q.rear = -1;  // 初始化为空，队尾指针指向-1
    Q.length = 0;
}
int lengthofque(CSQueue &Q)
{
    return Q.length;     
}       
bool Enqueue(CSQueue &Q,BiTree e)                   
    //循环顺序表的入队函数
{
   if(Q.length == MaxQSize) return false;//队列已满，不能再入队了
   Q.rear = (Q.rear + 1) % MaxQSize;
   Q.elem[Q.rear] = e;
   Q.length++;
   return true;
}

bool Dequeue(CSQueue &Q,BiTree &e)                   
//出队函数
{
    if(Q.length == 0) return false;//如果队列的长度为0，则返回false
    e = Q.elem[(Q.rear - Q.length + 1 + MaxQSize) % MaxQSize]; // 取出队头元素
    Q.length--;
    return true;
}
void queueTraverse(CSQueue &Q)
{
    int i, front = (Q.rear - Q.length + 1 + MaxQSize) % MaxQSize; // 计算队头指针
    for(i=0;i<Q.length;i++)
        cout << " " << Q.elem[(front + i) % MaxQSize];
}
//二叉树的先序遍历
void preorder(BiTree T,void visit(TElemType)){
    if(!T) return;
    //如果遍历到了空结点，遍历结束
    visit(T -> data);       //根
    preorder(T->lc,visit);  //左
    preorder(T->rc,visit);  //右
}

//中序遍历
void midorder(BiTree T,void visit(TElemType)){
    if(!T) return;
    //如果遍历到了空结点，遍历结束
    midorder(T->lc,visit);  //左
    visit(T -> data);       //根
    midorder(T->rc,visit);  //右
}

//后序遍历
void lasorder(BiTree T,void visit(TElemType)){
    if(!T) return;
    //如果遍历到了空结点，遍历结束
    lasorder(T->lc,visit);  //左
    lasorder(T->rc,visit);  //右
    visit(T -> data);       //根
}

//计算树结点的总数
int count(BiTree T){
    if(!T) return 0;
    return 1 + count(T -> lc) + count(T -> rc);
}

//树的创建
void CreatAtree(BiTree &T, char s[], int &i){
    i++;
    if(s[i] == '#') {T = NULL; return;}
    T = new BiTNode; T -> data = s[i];
    CreatAtree(T -> lc,s,i);
    CreatAtree(T -> rc,s,i);
    //采取根左右的方式构建树
}

void CreatAtree(BiTree &T, char s[]){
    int i = -1;
    CreatAtree(T,s,i);
}


//以广义表的形式输出二叉树
void BitreeLists(BiTree T,void visit(TElemType)){
    if(!T){
        cout << '#';    return;}
        visit(T -> data);
        if(T -> lc || T -> rc){
            cout << '(';
            BitreeLists(T -> lc,visit);
            cout << ',';
            BitreeLists(T -> rc,visit);
            cout << ')';
        }
    }

int depth(BiTree T){
    int dl, dr;
    if (!T) return 0;
    dl = depth(T -> lc);
    dr = depth(T -> rc);
    return dl > dr ? dl + 1 :dr + 1;
}

void DeleteBitree(BiTree &T){
    if(!T) return;
    DeleteBitree(T -> lc);
    DeleteBitree(T -> rc);
    delete T;
}


// 判断是否为完全二叉树
bool isCompleteTree(BiTree T){
    if(!T) return true;
    CSQueue Q;
    QueueInit(Q);
    Enqueue(Q,T);
    bool flag = false;
    while(lengthofque(Q)){
        BiTree p;
        Dequeue(Q,p);
        if(p -> lc){
            if(flag) return false;
            Enqueue(Q,p -> lc);
        }else{
            flag = true;
        }
        if(p -> rc){
            if(flag) return false;
            Enqueue(Q,p -> rc);
        }else{
            flag = true;
        }
    }
    return true;
}


int main(){
    BiTree T;
    char s[] = "ABC##DE#G##F###";
    CreatAtree(T,s);
    cout << "该二叉树的广义表表示为：";
    BitreeLists(T,visit);
    cout << endl;
    if(isCompleteTree(T)){
        cout << "该二叉树是完全二叉树" << endl;
    }else{
        cout << "该二叉树不是完全二叉树" << endl;
    }
}
