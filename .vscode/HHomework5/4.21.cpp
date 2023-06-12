// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>

using namespace std;
typedef int keytype;
const int ListInitSize = 100;

struct ElemType
{
    keytype key;
};

struct SList
{
    ElemType *elem;
    int length;
};

bool ListInit(SList &l)
{
    l.elem = new ElemType[ListInitSize];
    if (!l.elem)
        return false;
    l.length = 0;
    return true;
}

bool ListCreate(SList &l, int a[], int n)
{
    l.elem = new ElemType[n + ListInitSize];
    if (!l.elem)
        return false;
    l.length = n;
    int i;
    for (i = 0; i < n; i++)
        l.elem[i].key = a[i];
    return true;
}

void ListTraverse(SList &l)
{
    int i;
    for(i=0;i<l.length;i++) cout << l.elem[i].key << " ";
}

int Nature_calls(SList &l, int a[], int n)
{
    int cnt = 0;
    int compare = l.elem[0].key;
    a[cnt++] = 0;
    for (int i = 1; i < n; i++)
    {
        if (l.elem[i].key >= compare)
        {
            compare =l.elem[i].key;
        }
        else
        {
            a[cnt++] = i;
            compare = l.elem[i].key;
        }
    }
    a[cnt++] = n;
    return cnt;
}

void Merge(SList &l, int a, int m, int b)
{
    int i, j, k, s;
    ElemType *t;
    t = new ElemType[m - a + 1]; i = 0; j = m + 1; k = a - 1;
    for (s = a; s <= m; s++)
    {
        t[s - a] = l.elem[s];
    }
    while (i <= m - a && j <= b)
    {
        k++;
        if (t[i].key <= l.elem[j].key )
        {
            l.elem[k] = t[i];
            i++;
        }
        else
        {
            l.elem[k] = l.elem[j];
            j++;
        }
    }
    while (i <= m - a)
    {
        k++;
        l.elem[k] = t[i];
        i++;
    }
    delete[] t;
}

void MergeSort(SList &l)
{
    int n = l.length;
    int i, j;
    int a[n + 10];
    int cnt = Nature_calls(l, a, n);
    while (cnt != 2)
    {
        for (i = 0, j = 0; i < cnt; i += 2)
        {
            if (i + 2 >= cnt)
            {
                a[j++] = a[i];
                a[j] = n;
                break;
            }
            Merge(l, a[i], a[i + 1] - 1, a[i + 2] - 1);
            a[j++] = a[i];
        }
        cnt = cnt - int((cnt - 1) > 1);
    }
}
int main()
{
    SList l; ListInit(l);
    int a[]= {5,8,10,22,98,66,11};
    ListCreate(l,a,sizeof(a)/sizeof(a[0]));
    cout<<"初始元素序列为：" << endl;
    ListTraverse(l);
    cout<<endl;
    cout<<"自然归并排序后序列为：" << endl;
    MergeSort(l);
    ListTraverse(l);
}
