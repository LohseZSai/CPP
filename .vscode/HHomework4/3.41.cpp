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


bool firstElementOfLasorder(BiTree &T,TElemType &e){
    if(!T) return 0;
    BiTree p = T;
    if(T -> lc) return firstElementOfLasorder(T->lc,e);
    if(T -> rc) return firstElementOfLasorder(T->rc,e);
    e = T -> data;
    return 1;
}

void Creat_A_tree_by_Bitreelists(BiTree& T, const char* s, int& i) {
    i++;
    if (s[i] == '#') {
        T = NULL;
        return;
    }
    T = new BiTNode;
    T->data = s[i];
    T->lc = NULL;
    T->rc = NULL;
    i++;
    //一个是先加一再判断，一个是先判断再加1
    if (s[i] == '(') {
        Creat_A_tree_by_Bitreelists(T->lc, s,i);  // ++i跳过左括号
        //跳过逗号
        i++;
        Creat_A_tree_by_Bitreelists(T->rc, s,i);
        //跳过右括号
        i++;
    }
    else i--;
}

void Creat_A_tree_by_Bitreelists(BiTree& T,  char* s) {
    int i = -1;
    Creat_A_tree_by_Bitreelists(T, s, i);
}

int main(){
    BiTree T;
    char a[] = "A(B(C,#),D(E,F))";
    Creat_A_tree_by_Bitreelists(T,a);
    cout << "该树创建完毕后的先序遍历序列为：" ;
    preorder(T,visit) ;
    cout << endl;
    cout << "该树创建完毕后的中序遍历序列为：" ;
    midorder(T,visit) ;
    cout << "重建后与原先的广义表形式对比：" ;
    cout << endl;
    BitreeLists(T,visit);


}
