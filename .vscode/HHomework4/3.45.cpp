// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
#include <cstring>
using namespace std;
const int MaxTreeSize = 100;
typedef char TElemType;

//LElemType 限定类型
//TElemType 普通类型

//森林的定义
typedef struct TNode{
    TElemType data;
    TNode *parent,
          *fc,//第一个兄弟
          *ns;//右兄弟
} FNode, *tree, *forest;


typedef char QElemType;
// 构建循环链队列的数据类型，并实现基础的功能，如求长度、元素的查找、删除、插入等功能

struct CSQueue                  
{
    int rear, length;    
    forest elem[MaxTreeSize];         
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
bool Enqueue(CSQueue &Q,forest e)                   
    //循环顺序表的入队函数
{
   if(Q.length == MaxTreeSize) return false;//队列已满，不能再入队了
   Q.rear = (Q.rear + 1) % MaxTreeSize;
   Q.elem[Q.rear] = e;
   Q.length++;
   return true;
}

bool Dequeue(CSQueue &Q,forest &e)                   
//出队函数
{
    if(Q.length == 0) return false;//如果队列的长度为0，则返回false
    e = Q.elem[(Q.rear - Q.length + 1 + MaxTreeSize) % MaxTreeSize]; // 取出队头元素
    Q.length--;
    return true;
}
void queueTraverse(CSQueue &Q)
{
    int i, front = (Q.rear - Q.length + 1 + MaxTreeSize) % MaxTreeSize; // 计算队头指针
    for(i=0;i<Q.length;i++)
        cout << " " << Q.elem[(front + i) % MaxTreeSize];
}


void visit(TElemType e){
    cout << e << " ";
}


//已知空子树的先序遍历序列建立二叉树
void Createforest(forest &T,char *s,int &i)
{
	i++;
	if(s[i] == '#') {T = NULL; return;}
	T = new TNode;
	T -> data = s[i];
	Createforest(T->fc, s, i);
	Createforest(T->ns, s, i);
}


void Createforest(forest &T,char *s)
{
	int i=-1;
	Createforest(T,s,i);
}
//森林的先序遍历算法
void forestpreorder(forest T,void visit(TElemType)){
    if(!T) return;
    visit(T->data);
    forestpreorder(T->fc,visit);
    forestpreorder(T->ns,visit);
}


//定义一个森林的层序遍历函数
void levelOrder(forest f,void visit(TElemType)) {
    CSQueue Q;
    QueueInit(Q);
    Enqueue(Q, f);
    while (lengthofque(Q) != 0) {
        forest p;
        Dequeue(Q, p);
        visit(p->data);
        if (p->fc) {
            Enqueue(Q, p->fc);
            forest q = p->fc->ns;
            while (q) {
                Enqueue(Q, q);
                q = q->ns;
            }
        }
    }
} 


int main(){
    forest T;
    char a[] = "ABD#EH###CF##G###";
    Createforest(T,a);
    cout << "该森林的先序遍历序列为：";
    forestpreorder(T,visit);
    cout << endl;
    cout << "该森林的层序遍历序列为：";
    levelOrder(T,visit);
}


