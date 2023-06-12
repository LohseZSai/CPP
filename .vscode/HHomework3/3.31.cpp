// 该程序实现了习题3.31中判断完全二叉树的功能
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

int depth(BiTree T){
    int dl, dr;
    if (!T) return 0;
    dl = depth(T -> lc);
    dr = depth(T -> rc);
    return dl > dr ? dl + 1 :dr + 1;
}

int maximum_depth(BiTree  root) {
	if (!root) {
		return 0;                                 // return 0 for null node
	}
	int left_depth = maximum_depth(root->lc);
	int right_depth = maximum_depth(root->rc);
	return max(left_depth, right_depth) + 1;	  // return depth of the subtree rooted at root
}

//一个简单的实现思路是深度与结点个数之间的关系,可是用到了两次递归
// bool isA_strict_2childsTree(BiTree T){
//     if(!T) return false;
//     int deep = depth(T);
//     int counts = count(T);
//     if(pow(2,deep)-1 == counts) return true;
//      else false;
//     //得到结点总个数
// }

//另一个想法是用递归判断
bool isA_strict_2childsTree(BiTree T){
    if (!T) return false;
    //如果是叶子节点，return true
    if(!T -> lc && !T -> rc) return true;
    //如果是双孩子结点，继续往下判断后面结点是不是双孩子节点
    if(T -> lc && T -> rc) return isA_strict_2childsTree(T -> lc) && isA_strict_2childsTree(T -> rc);
    else return false;
}

int main(){
    BiTree T;
    TElemType a[] = "ABC###DE##F##";
    CreatAtree(T, a);
    cout << "该树的广义表形式为：" ;
    BitreeLists(T,visit);
    cout << endl;
    if(isA_strict_2childsTree(T)) cout << "这是一棵严格二叉树";
    else cout << "这不是一棵严格二叉树";
}