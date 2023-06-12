// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
#include <cstring>
using namespace std;
const int MaxTreeSize = 100;
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

bool Reborn_A_Tree(BiTree &T,char *a,char *b,int n,int m){
    //先序遍历的第一个元素为根节点
    if(n <= 0 || m <= 0) {
        T = NULL;
        return true;
    }
    T = new BiTNode;
    T -> data = a[0];
    int i;
    //找到中序遍历的根节点就退出
    for(i=0;i<m;i++){
        if(b[i] == a[0]) break;
    }
    return Reborn_A_Tree(T->lc,a+1,b,i,i) && Reborn_A_Tree(T->rc,a+i+1,b+i+1,n-i-1,m-i-1);
}

int main(){
    BiTree T;
    char a[] = "ABCDEF";
    char b[] = "CBAEDF";
    //传入参数需要包括长度
    Reborn_A_Tree(T,a,b,6,6);
    cout << "已知前序遍历序列和中序遍历序列求出来的二叉树为：";
    BitreeLists(T,visit);
}
