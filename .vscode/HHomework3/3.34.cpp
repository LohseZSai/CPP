// 该程序实现了习题3.34中删除所有根节点为X的子树的功能
// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
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


//对广义表形式的树进行转化，使其变成先序遍历序列
// void ListsTransform(TElemType *a){
//     TElemType *q = a,*p = a;
//     while(*p != '\0'){
//         q++;
//         if(*q != '(' && *q != ',' && *q != ')' && *q != '#'){
//             p++;
//             *p = *q;
//         }
//     }
//     p++;
//     *p = '\0';
// }
             


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




void DeleteAllX(BiTree &T, TElemType x){
    if(!T) return;
    if(T -> data == x){
        //找到了就删除
        DeleteBitree(T);
        T = NULL;
    }
    else{
        //没找到就继续找
        DeleteAllX(T -> lc, x);
        DeleteAllX(T -> rc, x);
    }
}





int main(){
    BiTree T;
    TElemType a[] = "ABXE##F##D##CXH##X##G##";
    //这个输入的树必须变成包含空子树的序列
    CreatAtree(T, a);
    char theX = 'X';
    //输出与删除后的树进行对比
    cout << "删除指定的元素结点子树前为：" ;
    BitreeLists(T,visit);
    cout << endl;
    DeleteAllX(T,theX);
    cout << "删除指定的元素结点子树后为：" ;
    BitreeLists(T,visit);
    
}