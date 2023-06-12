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

// int find_x_and_depth(BiTree T, char x) {
//     if (!T) return 0;
//     if (T->data == x) {
//         return depth(T);
//     }
//     //之前为      find_x_and_depth(T->lc, x) || find_x_and_depth(T->rc, x));错误！返回的是布尔值
//     return max(find_x_and_depth(T->lc, x), find_x_and_depth(T->rc, x));
// }


//对上述函数进行优化
struct Result {
    int depth;
    bool found;
};

Result optimized_find_x_and_depth(BiTree T, char x) {
    if (!T) {
        return {0, false};
    }
    if (T->data == x) {
        return {depth(T), true};
    }
    Result left_result = optimized_find_x_and_depth(T->lc, x);
    if (left_result.found) {
        return {left_result.depth, true};
    }
    Result right_result = optimized_find_x_and_depth(T->rc, x);
    if (right_result.found) {
        return {right_result.depth, true};
    }
    return {0, false};
}

int main(){
    BiTree T;
    TElemType a[] = "ABC###DE##F##";
    CreatAtree(T, a);
    cout << "该树的广义表形式为：" ;
    BitreeLists(T,visit);
    cout << endl;
    char theX = 'D';
    Result thedepth = optimized_find_x_and_depth(T,theX);
    cout << "要寻找的x结点为" << theX << "," << "其根的子树的深度为:" << thedepth.depth;
}
