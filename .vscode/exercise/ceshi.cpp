#include<iostream>
using namespace std;
typedef char TElemType;

const int MaxTreeSie = 100;
typedef struct BiTNode//链式存储结构
{
	TElemType data;//数据元素
	BiTNode* lc,//指向左孩子
		* rc;//指向右孩子
}*BiTree;
typedef BiTree QElemType;
typedef struct QNode
{
	QElemType data;
	QNode* next;
}*LQueuePtr;
struct LQueue
{
	LQueuePtr front, rear;
};
void QueueInit(LQueue& Q)
{
	Q.front = new QNode;
	Q.front->next = NULL;
	Q.rear = Q.front;
}
void Enqueue(LQueue& Q, QElemType e)
{
	LQueuePtr p;
	p = new QNode;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
}
bool Dequeue(LQueue& Q, QElemType& e)
{
	LQueuePtr p;
	if (Q.front == Q.rear)return false;
	p = Q.front;
	Q.front = p->next;
	e = Q.front->data;
	delete p;
	return true;
}
void preBiTreeLists(BiTree T)//以广义表形式先序遍历输出二叉树
{
	if(!T){
		cout << '#';
		return;
	}
	cout << T->data;
	if (T->lc || T->rc){
		cout << '(';
		preBiTreeLists(T->lc);
		cout << ',';
		preBiTreeLists(T->rc);
		cout << ')';
	}
}
void CreateBiTree(BiTree& T, char s[], int& i)
{
	i++;
	if (s[i] == '#'){
		T = NULL;
		return;
	}
	T = new BiTNode;
	T->data = s[i];
	CreateBiTree(T->lc, s, i);
	CreateBiTree(T->rc, s, i);
}
void CreateBiTree(BiTree& T, char s[])
{
	int i = -1;
	CreateBiTree(T, s, i);
}//以上两个同名不同参函数联合实现先序遍历建立二叉树（带有空子树信息）的操作，使用时只需调用第二个即可
void pre_count(BiTree T, int& count_double, int& count_single, int& count_leafs)//先序遍历统计各种结点个数
{
	if (!T)
		return;
	if (!T->lc && !T->rc){
		count_leafs++;
		return;
	}
	else if (T->lc && T->rc){
		count_double++;
		pre_count(T->lc, count_double, count_single, count_leafs);
		pre_count(T->rc, count_double, count_single, count_leafs);
	}
	else if (!T->lc && T->rc){
		count_single++;
		pre_count(T->rc, count_double, count_single, count_leafs);
	}
	else if (!T->rc && T->lc){
		count_single++;
		pre_count(T->lc, count_double, count_single, count_leafs);
	}
}
void level_count(BiTree T, int& count_double, int& count_single, int& count_leafs)//层序遍历统计各种结点个数
{
	LQueue q;
	BiTree p;
	if (!T)return;
	QueueInit(q);
	Enqueue(q, T);
	while (Dequeue(q, p)){
		if (!p->lc && !p->rc){
			count_leafs++;
			return;
		}
		else if (p->lc && p->rc){
			count_double++;
			level_count(p->lc, count_double, count_single, count_leafs);
			level_count(p->rc, count_double, count_single, count_leafs);
		}
		else if (p->lc && !p->rc){
			count_single++;
			level_count(p->lc, count_double, count_single, count_leafs);
		}
		else if (p->rc && !p->lc){
			count_single++;
			level_count(p->rc, count_double, count_single, count_leafs);
		}
	}
}
void bt_is_strict(BiTree T, int &flag)
{
	if (!T)return;
	else if (T->lc && T->rc){
		flag *= 1;
		bt_is_strict(T->lc, flag);
		bt_is_strict(T->rc, flag);
	}
	else if (!T->lc && !T->rc){
		flag *= 1;
		bt_is_strict(T->lc, flag);
		bt_is_strict(T->rc, flag);
	}
	else{
		flag *= 0;
		return;
	}
}
bool bt_is_strict(BiTree T)//判断树是否为严格二叉树
//除了叶结点外每个结点有且仅有两个子节点或只有一个根节点
{
	if (!T)return false;
	int flag = 1;
	bt_is_strict(T, flag);
	if (flag)return true;
	return false;
}
bool found(BiTree T, TElemType x)//在二叉树中查找数据元素，返回逻辑值表示是否查找成功
{
	if (!T)return false;
	if (x == T->data)return true;
	return found(T->lc, x) || found(T->rc, x);
}
int depth(BiTree T)//计算二叉树的深度
{
	int dl, dr;
	if (!T)return 0;
	dl = depth(T->lc);
	dr = depth(T->rc);
	return dl > dr ? dl + 1 : dr + 1;
}
BiTree found_adress(BiTree T,TElemType x)//返回二叉树中x元素的相关信息
{
	if (!T)return 0;
	if (x == T->data)return T;
	found_adress(T->lc,x);
	if (found_adress(T->lc, x))return found_adress(T->lc, x);
	return found_adress(T->rc, x);
}
int depth(BiTree T,TElemType x)//计算二叉树中以x为根的子树的深度
{
	if (!found(T,x))return 0;
	BiTree T1;
	T1 = found_adress(T, x);
	return depth(T1);
}
void DeleteBiTree(BiTree &T)//后续遍历删除二叉树
{
	if (!T)return;
	DeleteBiTree(T->lc);
	DeleteBiTree(T->rc);
	delete T;
}
void DeleteXTree(BiTree &T, TElemType X)
{
	if (!T) return;
	if (T->data == X) {
		DeleteBiTree(T);
		T = NULL;
	}
	DeleteXTree(T->lc, X);
	DeleteXTree(T->rc, X);
}
int main()
{
	BiTree T,T1,T2;
	char s[] = "ABC###DE##F##";
	char s1[] = "AB##C##";
	char s2 [] = "#";
	CreateBiTree(T2, s2);
	CreateBiTree(T1, s1);
	CreateBiTree(T, s);
	int count_double=0, count_single=0, count_leafs = 0;
	pre_count(T,count_double,count_single,count_leafs);
	cout << "二叉树:" << endl;
	preBiTreeLists(T);
	cout << endl<< "具有双孩子的结点数:" << count_double << endl;
	cout << "具有单孩子的结点数:" << count_single << endl;
	cout << "叶子结点数:" << count_leafs << endl;
	int count_double2 = 0, count_single2 = 0, count_leafs2 = 0;
	level_count(T, count_double2, count_single2, count_leafs2);
	cout << "二叉树:" << endl;
	preBiTreeLists(T);
	cout << endl << "具有双孩子的结点数:" << count_double2 << endl;
	cout << "具有单孩子的结点数:" << count_single2 << endl;
	cout << "叶子结点数:" << count_leafs2 << endl;
	cout << "二叉树:" << "";
	preBiTreeLists(T);
	cout << (bt_is_strict(T) ? "是严格二叉树" : "不是严格二叉树")<<endl;
	cout << "二叉树:" << "";
	preBiTreeLists(T1);
	cout << (bt_is_strict(T1) ? "是严格二叉树" : "不是严格二叉树")<<endl;
	cout << "二叉树:" << "";
	preBiTreeLists(T2);
	cout << (bt_is_strict(T2) ? "是严格二叉树" : "不是严格二叉树")<<endl;
	cout << "T中以M为根的子树的深度为:" << depth(T, 'M') <<endl;
	cout << "T中以M为根的子树的深度为:" << depth(T, 'B') <<endl;
	BiTree T3;
	char s3[] = "ABXE##F##D##CXH##X##G##";
	CreateBiTree(T3, s3);
	preBiTreeLists(T3);
	cout << 1;
	preBiTreeLists(T);
	cout << 1;
	DeleteXTree(T3, 'X');
	preBiTreeLists(T3);


	return 0;
}