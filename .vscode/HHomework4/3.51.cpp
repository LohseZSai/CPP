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

int count_the_K(tree T,int k,int &count){
    if(!T) return count;
    //运用先序遍历计算度
    if(count_a_du(T) == k) count++;
    count_the_K(T->fc,k,count);
    count_the_K(T->ns,k,count);
}

int count_the_K(tree T,int k){
    int count = 0;
    return count_the_K(T,k,count);
}

int main(){
    tree T;
    char a[] = "ABE#F##C#DG####";
    Createtree(T,a);
    cout << "该树的先序遍历序列为：";
    treepreorder(T,visit);
    cout << endl;
    int k;
    cout << "请输入k的值：" << endl;
    cin >> k;
    cout << "该树的度为k的结点个数为：" << count_the_K(T,k);
    
}

