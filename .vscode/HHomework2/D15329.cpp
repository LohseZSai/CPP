//˫���ӽڵ㡢�����ӽڵ㡢Ҷ�ӽ�����
//��Ϣ1701��һ�� 1709010115
#include <iostream>
using namespace std;
typedef char TElemType;
typedef struct BiTNode//��ʼ��������
{
	TElemType data;
	BiTNode *lc,*rc;
} *BiTree;

void CreateBiTree(BiTree &T,char s[],int &i)//����������н���������
{
	i++;
	if(s[i]=='#') {T=NULL;return;}
	T=new BiTNode;
	T->data=s[i];
	CreateBiTree(T->lc,s,i);
	CreateBiTree(T->rc,s,i);
}
void CreateBiTree(BiTree &T,char s[])
{
	int i=-1;
	CreateBiTree(T,s,i);
}

void BiTreeLists(BiTree T,void visit(TElemType))//�Թ������ʽ���������
{
	if(!T){cout<<'#';return;}
	visit(T->data);
	if(T->lc || T->rc)
	{
		cout<<'(';
        BiTreeLists(T->lc,visit);
		cout<<',';
		BiTreeLists(T->rc,visit);
		cout<<')';
	}
}

void visit(TElemType a)
{
	cout<<a;
}

int CountDC(BiTree &T)//˫���ӽ����
{
	if(!T)
	{
		return 0;
	}
	if(!T->lc&&!T->rc)
	{
		return 0;
	}	
	if(T->lc&&T->rc)
	{
		return 1+CountDC(T->lc)+CountDC(T->rc);
	}
	return CountDC(T->lc)+CountDC(T->rc);
}
int CountSC(BiTree &T)//�����ӽ����
{
	if(!T)
	{
		return 0;
	}
	if((T->lc&&!T->rc)||(T->rc&&!T->lc))
	{
		return 1+CountSC(T->lc)+CountSC(T->rc);
	}
	return CountSC(T->lc)+CountSC(T->rc);
}
int CountLeaf(BiTree &T)//Ҷ�ӽ����
{
	if(!T)
	{
		return 0;
	}
	if(!T->lc&&!T->rc)
	{
		return 1;
	}
	return CountLeaf(T->lc)+CountLeaf(T->rc);
}

int main()
{
	BiTree T;
	TElemType a[]="AB##C##";
	CreateBiTree(T,a);
	cout<<"二叉树:";
	BiTreeLists(T,visit);
	cout<<endl;
	cout<<"双孩子的结点数："<<CountDC(T)<<endl;
	cout<<"单孩子结点数："<<CountSC(T)<<endl;
	cout<<"叶子结点数："<<CountLeaf(T)<<endl;
	return 0;
}