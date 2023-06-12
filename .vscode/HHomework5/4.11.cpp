#include <iostream>

using namespace std;
typedef int keytype;

struct Element
{
    keytype key, count;
};

typedef struct BiTNode
{
    Element data;
    BiTNode *lc, *rc;
}*BiTree;

BiTree createNode(Element x)
{
    BiTree p;
    p = new BiTNode;
    p->data = x;
    p->data.count = 1;
    p->lc = p->rc = NULL;
    return p;
}

bool insertBinarySearchTree(BiTree &t, Element x)
{
    if (!t) {
        t = createNode(x);
        return true;
    }
    else if (t->data.key == x.key) {
        t->data.count++;
        return true;
    }
    else if (x.key < t->data.key)
        return insertBinarySearchTree(t->lc, x);
    else
        return insertBinarySearchTree(t->rc, x);
}

void createBinarySearchTree(BiTree &t, int n, Element a[])
{
    t = NULL;
    for (int i = 0; i < n; i++) {
        insertBinarySearchTree(t, a[i]);
    }
}

void traverseBiTree(BiTree t)
{
    if (!t) {
        cout << '#';
        return;
    }
    cout << "[" << t->data.key << "," << t->data.count << "]";
    if (t->lc || t->rc) {
        cout << '(';
        traverseBiTree(t->lc);
        cout << ',';
        traverseBiTree(t->rc);
        cout << ')';
    }
}

int main()
{
    BiTree t;
    Element a[] = { {3},{2},{1},{0},{0},{9},{7},{0} };
    createBinarySearchTree(t, 8, a);
    cout << "二叉树的统计情况为: " << endl;
    traverseBiTree(t);
    cout << endl;
}