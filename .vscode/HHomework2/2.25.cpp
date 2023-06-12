// 该程序实现了习题2.25中只设队尾指针而不设队头指针，实现队列的初始化、入队和出队算法
// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
using namespace std;

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


//循环链队列的初始化
void QueueInit(LQueue &Q){
    Q.rear = new QNode;
    Q.rear -> next = Q.rear;
    Q.length = 0;
}


//循环链队列的入队
void Enqueue(LQueue &Q,QElemType e){
    LQueuePtr p = new QNode;
    p -> data = e;     //定义Q的数据域
    p -> next  = Q.rear -> next;                         //尾部插入队尾
    Q.rear -> next = p;
    Q.rear = p;                 // 更新队尾指针
    Q.length ++;   //循环链队列的长度+1，实现了入队的标记
}


//循环链队列的出队，因为只定义了尾指针，出队的元素是尾指针的前驱结点
bool Dequeue(LQueue &Q,QElemType &e){
    if(Q.rear->next==Q.rear)
	{
		return false;
	}
	LQueuePtr p;
	p = Q.rear->next;        //指向队列第一个节点
	Q.rear->next = p->next;  //把p的下一个结点和队尾接上，以此达到出队的效果
	e = p -> data;  //把p的data返回
	delete p;
	return true;
}

//循环链队列元素的遍历
void queueTraverse(LQueue &Q){
    LQueuePtr p = Q.rear -> next;
    while (p != Q.rear){
        p = p -> next;
        cout << p -> data << " ";
    }   
}


int main(){
    LQueue Q;
    //初始化链表
    QueueInit(Q);
    int n = 6,m = 7,l = 8;
    Enqueue(Q,n);
    Enqueue(Q,m);
    Enqueue(Q,l);
    cout << "入队完成，此时循环链队列为:" << endl;
    queueTraverse(Q);
    Dequeue(Q,n);
    cout << endl <<"完成一次出队操作，此时循环链队列为:" << endl; 
    queueTraverse(Q);
}
