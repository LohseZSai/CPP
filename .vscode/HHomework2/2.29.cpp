// 该程序实现了习题2.29中循环顺序队列的初始化、入队和出队算法
// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
using namespace std;
const int MaxQSize = 5;
struct CSQueue                  
{
    int rear, length;    
    int elem[MaxQSize];         
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
bool Enqueue(CSQueue &Q,int e)                   
    //循环顺序表的入队函数
{
   if(Q.length == MaxQSize) return false;//队列已满，不能再入队了
   Q.rear = (Q.rear + 1) % MaxQSize;
   Q.elem[Q.rear] = e;
   Q.length++;
   return true;
}
bool Dequeue(CSQueue &Q,int &e)                   
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
int main()
{
   CSQueue Q;
   QueueInit(Q);
   Enqueue(Q,6);
   Enqueue(Q,7);
   Enqueue(Q,8);
   cout << "入队成功，此时队列中的元素为"<<endl ;
   queueTraverse(Q);
   cout << endl <<"下面完成出队操作";
   int e;
   Dequeue(Q,e);
   cout << "出队后，队列中的元素为：" << endl;
   queueTraverse(Q);
   
}