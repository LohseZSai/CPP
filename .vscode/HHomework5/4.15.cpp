#include <iostream>

using namespace std;
typedef int keytype;

const int ListInitSize=100;
const int StackInitSize=50;
const int StackInc=50;
struct ElementType
{
	keytype key;
};
struct SortedList
{
	ElementType *element;
	int length;
};


bool createList(SortedList &L,int n,ElementType *r)
{
	int i;
	L.element=new ElementType[n+1];
	if(!L.element)
		return false;
	L.length=n;
	for (i=0;i<n;i++)
		L.element[i+1].key=r[i].key;
	return true;
}

void traverseList(SortedList L)
{
	int i;
	for(i=0;i<L.length;i++)
        cout << L.element[i+1].key <<" ";
}

struct StackElementType
{
	int lower;
	int upper;
};

struct Stack
{
	StackElementType *base,*top;
	int stacksize;
};

bool initializeStack(Stack &S)
{
	S.base=new StackElementType[StackInitSize];
	if(!S.base) return false;
	S.top=S.base;
	S.stacksize=StackInitSize;
	return true;
}

bool push(Stack &S,StackElementType e)
{
	StackElementType *base;
	if(S.top-S.base==S.stacksize)
	{
		if(!base) return false;
		S.base=base;
		S.top=S.base+S.stacksize;
		S.stacksize+=StackInc;
	}
	*S.top=e;
	S.top++;
	return true;
}

bool pop(Stack &S,StackElementType &e)
{
	if(S.top==S.base) return false;
	S.top--;
	e=* S.top;
	return true;
}

int partition(SortedList &L, int a, int b)
{
    ElementType x;
    x = L.element[a];
    while (a < b)
    {
        while (a < b && (L.element[b].key >= x.key))
            b--;
        L.element[a] = L.element[b];
        while (a < b && (L.element[a].key <= x.key))
            a++;
        L.element[b] = L.element[a];
    }
    L.element[a] = x;
    return a;
}

void insertionSort(SortedList &L)
{
    int i, j;
    ElementType x;
    for (i = 2; i <= L.length; i++)
    {
        x = L.element[i];
        for (j = i - 1; j >= 1 && x.key < L.element[j].key; j--)
        {
            L.element[j + 1] = L.element[j];
        }
        L.element[j + 1] = x;
    }
}

void quickSort(SortedList &L)
{
	Stack S;
	initializeStack(S);
	StackElementType x={1,L.length},y;
	push(S,x);
	while(pop(S,x))
	{
		int m=partition(L,x.lower,x.upper);
		if(m-x.lower>8)
		{
			y.lower=x.lower;
			y.upper=m-1;
			push(S,y);
		}
		if(x.upper-m>8)
		{
			y.upper=x.upper;
			y.lower=m+1;
			push(S,y);
		}
	}
	insertionSort(L);
}

int main()
{
    SortedList list;
	ElementType a[]={1,3,5,7,2};
	createList(list,sizeof(a)/4,a);
	cout<<"原始数据为: "<<endl;
	traverseList(list);
	cout << endl;
	quickSort(list);
	cout<<"排序后: "<<endl;
	traverseList(list);
	cout<<endl;

}