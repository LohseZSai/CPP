// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
#include <cstring>
using namespace std;
const int MaxTreeSize = 100;
typedef int KeyType;

struct ElemType
{
    KeyType key;
    bool exist;
};

// LElemType 限定类型
// ElemType 普通类型

typedef struct BiTNode
{
    ElemType data;
    BiTNode *lc, // 左孩子
        *rc;
} *BiTree;


struct SqTree
{
    ElemType bt[MaxTreeSize + 1];
    int n;
}; // 该结构体用于储存二叉树的元素

void visit(ElemType e)
{
    cout << e.key << " ";
}

// 二叉树的先序遍历
void preorder(BiTree T, void visit(ElemType))
{
    if (!T)
        return;
    // 如果遍历到了空结点，遍历结束
    visit(T->data);         // 根
    preorder(T->lc, visit); // 左
    preorder(T->rc, visit); // 右
}

// 中序遍历
void midorder(BiTree T, void visit(ElemType))
{
    if (!T)
        return;
    // 如果遍历到了空结点，遍历结束
    midorder(T->lc, visit); // 左
    visit(T->data);         // 根
    midorder(T->rc, visit); // 右
}

// 后序遍历
void lasorder(BiTree T, void visit(ElemType))
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

// 以广义表的形式输出二叉树
void BitreeLists(BiTree T, void visit(ElemType))
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

int depth(BiTree T)
{
    int dl, dr;
    if (!T)
        return 0;
    dl = depth(T->lc);
    dr = depth(T->rc);
    return dl > dr ? dl + 1 : dr + 1;
}

void DeleteBitree(BiTree &T)
{
    if (!T)
        return;
    DeleteBitree(T->lc);
    DeleteBitree(T->rc);
    delete T;
}


void CreateBiTree(BiTree &T, ElemType s[], int &i)
{
    i++;
    if (!s[i].exist)
    {
        T = NULL;
        return;
    }
    T = new BiTNode;
    T->data = s[i];            // 生成根结点
    CreateBiTree(T->lc, s, i); // 构造左子树
    CreateBiTree(T->rc, s, i); // 构造右子树
}
void CreateBiTree(BiTree &T, ElemType s[])
{
    int i = -1;
    CreateBiTree(T, s, i);
}


bool isValidBST(BiTree T, BiTree &pre)
{
    if (!T)
        return true;
    if(!isValidBST(T->lc,pre)) return false;
    if(pre && pre->data.key>=T->data.key) return false;
    pre = T;
    return isValidBST(T->rc,pre);
}

bool isValidBST(BiTree T)
{
    BiTree pre = nullptr;
    return isValidBST(T, pre);
}


// 二叉树的插入

BiTree CreatNode(ElemType x)
{
    BiTree p;
    p = new BiTNode;
    p->data = x;
    p->lc = p->rc = NULL;
    return p;
}

bool InsertBST(BiTree &T, ElemType x)
{
    if (!T)
    {
        T = CreatNode(x);
        return true;
    }
    else if (T->data.key == x.key)
        return false;
    else if (x.key < T->data.key)
        return InsertBST(T->lc, x);
    else
        return InsertBST(T->rc, x);
}

void CreatBST(BiTree &T, int n, ElemType a[])
{
    int i;
    T = NULL;
    for (i = 0; i < n; i++)
        InsertBST(T, a[i]);
}

void judge_systemout(bool result){
    if(result) cout << "该树是二叉排序树";
    else cout << "该树不是二叉排序树";
}

int main()
{
    BiTree T1, T2;
    ElemType a[] = {{4}, {6}, {2}, {5}, {7}, {1}, {3}, {8}};
    CreatBST(T1, 8, a);
    cout << "二叉排序树：";
    BitreeLists(T1, visit);
    cout << endl;
    judge_systemout(isValidBST(T1));
    ElemType b[] = {{10, true}, {6, true}, {2, true}, {0, false}, {0, false}, {5, true}, {0, false}, {0, false}, {7, true}, {0, false}, {0, false}};
    CreateBiTree(T2, b);
    cout << endl;
    cout << "二叉树：";
    BitreeLists(T2, visit);
    cout << endl;
    judge_systemout(isValidBST(T2));
    cout << endl;
    return 0;
}

