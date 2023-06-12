// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef int KeyType;

const int ListInitSize = 105;
struct ElemType{
    KeyType key;
};

struct SList{
    ElemType *r;
    int length;
    int compare_count; // 记录比较次数
    int assign_count; // 记录赋值次数
};


// 初始化静态查找表
void ListInit(SList &L) {
    L.r = new ElemType[ListInitSize]; // 创建一个长度为 length + 1 的动态数组，从下标 1 开始存储元素
    if(!L.r) return;
    L.length = 0;
    L.compare_count = 0;
    L.assign_count = 0;
}
//创建静态查找表
void CreatList(SList &L,int length, int *a){
    int i;
    L.r = new ElemType[length+1];
    if(!L.r)
        return;
    L.length = length;
    L.compare_count = 0;
    L.assign_count = 0;
    for(i=1;i<=length;i++) {
        L.r[i].key = a[i-1];
    }
}

//直接插入排序
void InsertSort(SList &L){
    int i,j;
    ElemType x;
    for(i=2;i<=L.length;i++){
        for(x = L.r[i],j = i-1;j >= 1 && x.key < L.r[j].key;j--){
            L.r[j+1] = L.r[j];
            L.assign_count++;
            L.compare_count++;
        }
        L.r[j+1] = x;
        L.assign_count++;
    }
}

//简单选择排序
void SelectSort(SList &L){
    int i,j,k;
    ElemType x;
    for(i=1;i<=L.length-1;i++){
        k = i;
        for(j = i + 1; j<= L.length; j++){
            L.compare_count++;
            if (L.r[j].key < L.r[k].key) k = j;
        }
        if (k > i) { 
            x = L.r[i];
            L.r[i] = L.r[k];
            L.r[k] = x;
            L.assign_count += 3;
        }
    }
}

//快速排序
int Partition(SList &L, int a, int b){
    ElemType x = L.r[a];
    while(a < b){
        while(a < b && L.r[b].key >= x.key){
            L.compare_count++;
            b--;
        }
        L.r[a] = L.r[b];
        L.assign_count++;
        while(a < b && L.r[a].key <= x.key){
            L.compare_count++;
            a++;
        }
        L.r[b] = L.r[a];
        L.assign_count++;
    }
    L.r[a] = x;
    L.assign_count++;
    return a;
}

void QSort(SList &L, int a,int b){
    int p;
    if(a >= b) return;
    p = Partition(L, a, b);
    QSort(L, a, p-1);
    QSort(L, p+1, b);
}

void QuickSort(SList &L){
    QSort(L, 1, L.length);
}

//堆排序
void HeapAdjust(SList &H,int s,int m){
    int j;
    ElemType x;
    x = H.r[s];
    j = 2*s;
    while(j <= m){
        if(j<m && H.r[j].key < H.r[j+1].key){
            j++;
            H.compare_count++;
        }
        if(x.key >= H.r[j].key) break;
        H.r[s] = H.r[j];
        H.assign_count++;
        s = j;
        j = 2 * j;
    }
    H.r[s] = x;
    H.assign_count++;
}

void HeapSort(SList &H){
    int i;
    ElemType x;
    for(i = H.length/2;i>=1;i--) HeapAdjust(H,i,H.length);
    for(i = H.length;i>=2;i--){
        x = H.r[1];
        H.r[1] = H.r[i];
        H.r[i] = x;
        H.assign_count += 3;
        HeapAdjust(H,1,i-1);
    }
}
//归并排序
void Merge(SList &L,int a,int m,int b){
    int i,j,k,s;
    ElemType *t;
    t = new ElemType[m-a+1];
    i = 0;
    j = m + 1;
    k = a - 1;
    for(s = a;s <= m;s++) t[s - a] = L.r[s];
    while(i<=m-a && j <= b){
        k++;
        if(t[i].key <= L.r[i].key){
            L.r[k] = t[i];
            L.assign_count++;
            i++;
        }
        else{
            L.r[k] = L.r[j];
            L.assign_count++;
            j++;
        }
        L.compare_count++;
    }
    while(i <= m-a){
        k++;
        L.r[k] = t[i];
        L.assign_count++;
        i++;
    }
    while(j <= b){
        k++;
        L.r[k] = L.r[j];
        L.assign_count++;
        j++;
    }
}

void MSort(SList &L,int a,int b){
    int m;
    if(a < b){
        m = (a + b) / 2;
        MSort(L,a,m);
        MSort(L,m+1,b);
        Merge(L,a,m,b);
    }
}

void MergeSort(SList &L){
    MSort(L,1,L.length);
}

int main(){
    int a[2000];
    int i,length=1000;
    SList L1,L2,L3,L4,L5;
    srand(time(0));
    //随机数生成
    for (int i = 0; i < 1000; i++)
    {
        int num = rand() + 1;
        a[i]=num;
    }
    CreatList(L1,1000,a);
    InsertSort(L1);
    cout << "插入排序比较次数: " << L1.compare_count << endl;
    cout << "插入排序赋值次数: " << L1.assign_count << endl;
    CreatList(L2,1000,a);
    SelectSort(L2);
    cout << "选择排序比较次数: " << L2.compare_count << endl;
    cout << "选择排序赋值次数: " << L2.assign_count << endl;
    CreatList(L3,1000,a);
    QuickSort(L3);
    cout << "快速排序比较次数: " << L3.compare_count << endl;
    cout << "快速排序赋值次数: " << L3.assign_count << endl;
    CreatList(L4,1000,a);
    HeapSort(L4);
    cout << "堆排序比较次数: " << L4.compare_count << endl;
    cout << "堆排序赋值次数: " << L4.assign_count << endl;
    CreatList(L5,1000,a);
    MergeSort(L5);
    cout << "归并排序比较次数: " << L5.compare_count << endl;
    cout << "归并排序赋值次数: " << L5.assign_count << endl;

}

