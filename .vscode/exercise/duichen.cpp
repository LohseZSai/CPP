// 该程序实现了习题3.35中判断完全二叉树的功能
// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
using namespace std;
const int MaxTreeSize = 100;
typedef char TElemType;
// LElemType 限定类型
// TElemType 普通类型

typedef struct BiTNode
{
    TElemType data;
    BiTNode *lc, // 左孩子
        *rc;
} *BiTree;

struct SqTree
{
    TElemType bt[MaxTreeSize + 1];
    int n;
}; // 该结构体用于储存二叉树的元素

void visit(TElemType e)
{
    cout << e << " ";
}

// 二叉树的先序遍历
void preorder(BiTree T, void visit(TElemType))
{
    if (!T)
        return;
    // 如果遍历到了空结点，遍历结束
    visit(T->data);         // 根
    preorder(T->lc, visit); // 左
    preorder(T->rc, visit); // 右
}

// 中序遍历
void midorder(BiTree T, void visit(TElemType))
{
    if (!T)
        return;
    // 如果遍历到了空结点，遍历结束
    midorder(T->lc, visit); // 左
    visit(T->data);         // 根
    midorder(T->rc, visit); // 右
}

// 后序遍历
void lasorder(BiTree T, void visit(TElemType))
{
    if (!T)
        return;
    // 如果遍历到了空结点，遍历结束
    lasorder(T->lc, visit); // 左
    lasorder(T->rc, visit); // 右
    visit(T->data);         // 根
}

// 计算树结点的总数
int count(BiTree T)
{
    if (!T)
        return 0;
    return 1 + count(T->lc) + count(T->rc);
}

// 树的创建
void CreatAtree(BiTree &T, char s[], int &i)
{
    i++;
    if (s[i] == '#')
    {
        T = NULL;
        return;
    }
    T = new BiTNode;
    T->data = s[i];
    CreatAtree(T->lc, s, i);
    CreatAtree(T->rc, s, i);
    // 采取根左右的方式构建树
}

void CreatAtree(BiTree &T, char s[])
{
    int i = -1;
    CreatAtree(T, s, i);
}

// 以广义表的形式输出二叉树
void BitreeLists(BiTree T, void visit(TElemType))
{
    if (!T)
    {
        cout << '#';
        return;
    }
    visit(T->data);
    if (T->lc || T->rc)
    {
        cout << '(';
        BitreeLists(T->lc, visit);
        cout << ',';
        BitreeLists(T->rc, visit);
        cout << ')';
    }
}

void DeleteBitree(BiTree &T)
{
    if (!T)
        return;
    DeleteBitree(T->lc);
    DeleteBitree(T->rc);
    delete T;
}

bool firstElementOfLasorder(BiTree &T, TElemType &e)
{
    if (!T)
        return 0;
    BiTree p = T;
    if (T->lc)
        return firstElementOfLasorder(T->lc, e);
    if (T->rc)
        return firstElementOfLasorder(T->rc, e);
    e = T->data;
    return 1;
}

// 判断二叉树对称

bool isSymmetric(BiTree left, BiTree right)
{
    if (left == nullptr && right == nullptr)
        return true;
    else if (left == nullptr || right == nullptr)
        return false;
    else if (left->data != right->data)
        return false;
    else
        return isSymmetric(left->lc, right->rc) && isSymmetric(left->rc, right->lc);
}

bool isSymmetric(BiTree T)
{
    if (!T)
        return true;
    else
        return isSymmetric(T->lc, T->rc);
}
// 判断深度
int depth(BiTree T)
{
    if (!T)
        return 0;
    int dl, dr;
    dl = depth(T->lc);
    dr = depth(T->rc);
    return dl > dr ? dl + 1 : dr + 1;
}


bool isBalancedHelper(BiTree T, int &depth)
{
    if (!T)
    {
        depth = 0;
        return true;
    }
    int leftDepth, rightDepth;
    bool leftBalanced = isBalancedHelper(T->lc, leftDepth);
    bool rightBalanced = isBalancedHelper(T->rc, rightDepth);
    depth = max(leftDepth, rightDepth) + 1;
    if (abs(leftDepth - rightDepth) > 1)
        return false;
    else
        return leftBalanced && rightBalanced;
}

bool isBalanced(BiTree T)
{
    int depth;
    return isBalancedHelper(T, depth);
}

int main()
{
    BiTree T;
    char s[] = "ABC###DE##F##";
    CreatAtree(T, s);
    if (isBalanced(T) == true)
        cout << "该树是一棵平衡二叉树";
    else
        cout << "该树不是一棵平衡二叉树";
    BitreeLists(T, visit);
    cout << endl;
}
