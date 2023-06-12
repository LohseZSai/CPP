// 该程序实现了习题3.29中进行统计三个量的功能
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

struct Result{
    int leaf;
    int singleChild;
    int doubleChild;
};

//统计二叉树的具有双孩子结点数、单孩子结点数、叶子节点数
Result countNodes(BiTree T) {
    Result result = {0, 0, 0};
    if(!T) {
        return result;
    }
    Result leftResult = countNodes(T->lc);
    Result rightResult = countNodes(T->rc);
    result.doubleChild = leftResult.doubleChild + rightResult.doubleChild;
    result.singleChild = leftResult.singleChild + rightResult.singleChild;
    result.leaf = leftResult.leaf + rightResult.leaf;
    if(T->lc && T->rc) {
        result.doubleChild++;
    } else if(T->lc || T->rc) {
        result.singleChild++;
    } else {
        result.leaf++;
    }
    return result;
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

void printResult(Result r){
    cout << "该树的双孩子结点为：" << r.doubleChild << endl;
    cout << "该树的单孩子结点为：" << r.singleChild << endl;
    cout << "该树的叶子结点为：" << r.leaf << endl;
}
  


int main(){
        BiTree T;
        //书p49页上面的例子来试试
        TElemType a[] = "ABC###DE##F##";
        CreatAtree(T, a);
        cout << "该树的广义表形式为：" ;
        BitreeLists(T,visit);
        cout << endl;
        printResult(countNodes(T));
}











