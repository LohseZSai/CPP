
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
typedef int keytype;

const int ListInitSize = 100;
const int StackInitSize = 50;
const int StackInc = 50;

void Random(int *a, int n, int l, int r)
{
    srand(time(0));
    for (int i = 0; i < n; i++) {
        a[i] = rand();
    }
}

struct ElemType
{
    keytype key;
};

struct SList
{
    ElemType *elem;
    int length;
};


bool ListCreate(SList &list, int n, ElemType *r)
{
    int i;
    list.elem = new ElemType[n+1];
    if (!list.elem)
        return false;
    list.length = n;
    for (i = 0; i < n; i++)
        list.elem[i+1].key = r[i].key;
    return true;
}

void ListTraverse(SList list)
{
    int i;
    for (i = 0; i < list.length; i++)
        cout << list.elem[i+1].key << " ";
}

void InsertSort(SList &list, int &compareCount, int &assignCount)
{
    int compare_sum = 0, assign_sum = 0;
    int i, j;
    ElemType x;
    for (i = 2; i <= list.length; i++) {
        for (x = list.elem[i], j = i - 1; j >= 1 && (++compare_sum, x.key < list.elem[j].key); j--) {
            list.elem[j + 1] = list.elem[j];
            assign_sum++;
        }
        list.elem[j + 1] = x;
        assign_sum++;
    }
    compareCount = compare_sum;
    assignCount = assign_sum;
}

void SelectSort(SList &list, int &compareCount, int &assignCount)
{
    int i, j, k;
    ElemType x;
    int compare_sum = 0, assign_sum = 0;
    for (i = 1; i <= list.length - 1; i++) {
        k = i;
        for (j = i + 1; j <= list.length; j++)
            if (++compare_sum, list.elem[j].key < list.elem[k].key)
                k = j;
        if (k != i) {
            x = list.elem[i];
            list.elem[i] = list.elem[k];
            list.elem[k] = x;
            assign_sum += 3;
        }
    }
    compareCount = compare_sum;
    assignCount = assign_sum;
}

// 快速排序
int Partition(SList &l,int a,int b,int &c,int &A)
{
    ElemType x = l.elem[a];
    A++;
    while(a<b)
    {
        while (a<b && (++c,l.elem[b].key >= x.key)) b--;
        l.elem[a] = l.elem[b];
        A ++;
        while (a<b && (++c,l.elem[a].key <= x.key)) a++;
        l.elem[b] = l.elem[a];
        A ++;
    }
    l.elem[a] = x; A ++;
    return a;
}
void QSort(SList &l,int a,int b,int &c,int &A)
{
    int p;
    if (a >= b) return ;
    p = Partition(l,a,b,c,A); QSort(l,a,p-1,c,A); QSort(l,p+1,b,c,A);
}
void QuickSort(SList &l,int &c,int &A)
{
    QSort(l,1,l.length,c,A);
}

// 堆排序
void HeapAdjust(SList &l,int s,int m,int &c,int &a)
{
    int j; ElemType x;
    x = l.elem[s]; a++; j = 2*s;
    while(j <= m)
    {
        if (j<m && (++c,l.elem[j].key < l.elem[j+1].key)) j++;
        if ((++c,x.key >= l.elem[j].key)) break;
        l.elem[s] = l.elem[j]; a++; s = j; j = 2*j;
    }
    l.elem[s] = x; a++;
}
void HeapSort(SList &l,int &c,int &a)
{
    int i; ElemType x;
    for(i=l.length/2;i>=1;i--) HeapAdjust(l,i,l.length,c,a);
    for(i=l.length;i>=2;i--)
    {
        x = l.elem[1]; a++; l.elem[1] = l.elem[i]; a++; l.elem[i] = x; a++;
        HeapAdjust(l,1,i-1,c,a);
    }
}


// 归并排序
void Merge(SList &l, int a, int m, int b, int &c, int &A)
{
    int i, j, k, s;
    ElemType *t;
    t = new ElemType[m - a + 1];
    i = 0;
    j = m + 1;
    k = a - 1;
    for (s = a; s <= m; s++)
    {
        t[s - a] = l.elem[s];
        A++;
    }
    while (i <= m - a && j <= b)
    {
        k++;
        if (++c,t[i].key <= l.elem[j].key)
        {
            l.elem[k] = t[i];
            i++;
            A++;
        }
        else
        {
            l.elem[k] = l.elem[j];
            j++;
            A++;
        }
    }
    while (i <= m - a)
    {
        k++;
        l.elem[k] = t[i];
        A++;
        i++;
    }
    delete[] t;
}
void MergeSort(SList &l, int &c,int &A)
{
    int a, m, b, h;
    for (h = 1; h < l.length; h *= 2)
    {
        for (a = 1;; a += 2 * h)
        {
            m = a + h - 1;
            if (m >= l.length )
                break;
            b = m + h;
            if (b > l.length )
                b = l.length;
            Merge(l, a, m, b, c, A);
        }
    }
}



int main()
{
    SList list1, list2, list3, list4, list5;
    int n = 1000;
    int a[n];
    ElemType A[n];
    Random(a, n, 1, 1001);
    for (int i = 0; i < 1000; i++)
        A[i].key = a[i];
    ListCreate(list1, 1000, A);ListCreate(list2, 1000, A);ListCreate(list3, 1000, A);ListCreate(list4, 1000, A);ListCreate(list5, 1000, A);
    int compareCount1 = 0;
    int assignCount1 = 0;
    InsertSort(list1, compareCount1, assignCount1);
    cout << "直接插入法  "
         << "比较次数:" << compareCount1 << "  "
         << "赋值次数:" << assignCount1 << endl;

    int compareCount2 = 0;
    int assignCount2 = 0;
    SelectSort(list2, compareCount2, assignCount2);
    cout << "简单选择法  "
         << "比较次数:" << compareCount2 << "  "
         << "赋值次数:" << assignCount2 << endl;

    int compareCount3 = 0;
    int assignCount3 = 0;
    QuickSort(list3, compareCount3, assignCount3);
    cout << "快速排序法  "
         << "比较次数:" << compareCount3 << "  "
         << "赋值次数:" << assignCount3 << endl;

    int compareCount4 = 0;
    int assignCount4 = 0;
    HeapSort(list4, compareCount4, assignCount4);
    cout << "堆排序  "
         << "比较次数:" << compareCount4 << "  "
         << "赋值次数:" << assignCount4 << endl;

    int compareCount5 = 0;
    int assignCount5 = 0;
    MergeSort(list5, compareCount5, assignCount5);
    cout << "归并排序  "
         << "比较次数:" << compareCount5 << "  "
         << "赋值次数:" << assignCount5 << endl;
}