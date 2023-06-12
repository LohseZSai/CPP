#include <iostream>
#include <cstring>
using namespace std;
const int MaxTreeSize = 100;
typedef char TElemType;

//LElemType 限定类型
//TElemType 普通类型

//森林的定义
typedef struct TNode{
    TElemType data;
    TNode *parent,
          *fc,//第一个兄弟
          *ns;//右兄弟
} *tree;

void visit(TElemType e){
    cout << e << " ";
}

//树的先序遍历算法
void treepreorder(tree T, void visit(TElemType)){
    tree p;
    if(!T) return;
    visit(T -> data);
    for(p = T -> fc;p;p = p -> ns) treepreorder(p,visit);
}

//已知空子树的先序遍历序列建立树
void Createtree(tree &T,char *s,int &i)
{
	i++;
	if(s[i] == '#') {T = NULL; return;}
	T = new TNode;
	T -> data = s[i];
	Createtree(T->fc, s, i);
	Createtree(T->ns, s, i);
}


void Createtree(tree &T,char *s)
{
	int i=-1;
	Createtree(T,s,i);
}

//计算一个节点的度
int count_a_du(tree T){
    
    if(!T) return 0;
    int count = 0;
    tree p = T -> fc;
    while(p){
        count++;
        //转到右兄弟，当没有右兄弟的时候就算完了
        p = p -> ns;
    }
    return count;

}
//计算树的深度
int count_tree_depth(tree T){
    if(!T) return 0;
    int max_depth = 0;
    tree p = T -> fc;
    while(p){
        int depth = count_tree_depth(p);
        if(depth > max_depth) max_depth = depth;
        p = p -> ns;
    }
    return max_depth + 1;
} 
int main(){
    tree T;
    char a[] = "ABE#F##C#DG####";
    Createtree(T,a);
    cout << "该树的先序遍历序列为：";
    treepreorder(T,visit);
    cout << endl;
    cout << "这棵树的深度为：" << count_tree_depth(T);
    
}

