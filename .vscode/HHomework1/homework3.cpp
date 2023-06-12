//该程序实现了习题2.11中的把共同元素保存到新表的功能
//姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include<iostream>
using namespace std;
typedef int LElemType;
//构建线性表的数据类型，并且实现初始化、创建、遍历等功能
const int ListInitSize = 105;
const int ListInc = 105;

struct SList{
    LElemType *elem;
    int length, listsize;   //创建SList并规定数据类型，元素、长度和内存大小
};

//顺序表的初始化
bool ListInit(SList &L){
    L.elem = new LElemType[ListInitSize];
    if (!L.elem) return false;
    L.length = 0;
    L.listsize = ListInitSize;
    return true;
}
//顺序表的创建、元素的存储
bool ListCreat(SList &L,int n,LElemType a[]){
    int i;
    L.elem = new LElemType[n + ListInitSize];
    if(!L.elem) return false;
    L.length = n;
    L.listsize = n + ListInitSize;
    for(i=0;i<n;i++) L.elem[i] = a[i];
    return true;
}
//元素的访问
void visit(LElemType e){
    cout << e << " ";
}
//元素的遍历，访问作为形参
void ListTraverse(SList &L, void visit(LElemType e)){
    int i;
    for(i=0;i<L.length;i++) visit(L.elem[i]);
}

//元素的比较，两个元素是否一样
bool compare(LElemType e1,LElemType e2){
    if (e1 == e2)
        return true;
    else 
        return false;
}

//元素的查找，是否存在于顺序表中
int ListLocate(SList L,LElemType e,bool compare(LElemType e1,LElemType e2)){
    int i = 1;
    while(i<=L.length && !compare(L.elem[i-1],e)) i++;
    if (i>L.length) i = 0; 
    return i;//如果存在返回元素的位序，否则返回0
}


//思路：查找两个顺序表的相同元素，如果相同就放到新表中,为新顺序表另分配储存空间
// void comment_elem_creat(SList &A,SList &B,SList &C){
//     int flag = 0;
//     for(int i=0;i<A.length;i++){
        
//         //元素查找
//         //找到了相同元素，则添加入C数组中,且不改变相对位置
//         if(ListLocate(B,A.elem[i],compare) != 0)        
//             C.elem[flag++] = A.elem[i];
//     }
//     C.length = flag;
// }

//优化以上思路，运用双指针的办法实现功能，减少循环的次数
//定义两个指针 i 和 j，分别指向 A 和 B 的开头位置。
//只要 i 和 j 都没有越界，就执行以下循环：
//如果 A[i] < B[j]，那么 i 向右移动一位。
//如果 A[i] > B[j]，那么 j 向右移动一位。
//如果 A[i] = B[j]，那么将 A[i]（或者 B[j]）添加到 C 中，然后 i 和 j 都向右移动一位。
//循环结束后，C 中就存放了 A 和 B 中的共同元素。
void Opitimized_comment_elem_creat(SList &A,SList &B,SList &C){
    int i, j;
    int times = min(A.length,B.length),flag = 0;
    for(i=j=0;i< times;){
        if (A.elem[i] < B.elem[j]) i++;
        else if(A.elem[i] > B.elem[j]) j++;
        else {
            C.elem[flag++] = A.elem[i];
            i++; j++;
        }
    }
    C.length = flag;
}


//主函数
int main(){
    SList A,B,C;
    //对顺序表进行初始化
    ListInit(A);ListInit(B);ListInit(C);
    //进行案例的输入
    //输入数组A的长度m，B的长度n,由案例可得m=n=5
    int m,n;    
    cin >> m >> n;
    int a[m]={0},b[n]={0};    
    int c[10]={0};
    for(int i=0;i<m;i++) cin >> a[i];   //a[]为{1,2,3,4,5}
    for(int i=0;i<n;i++) cin >> b[i];   //b[]为{1,3,5,7,9}
    //创建顺序表,给C分配新的储存空间
    ListCreat(A,m,a);ListCreat(B,n,b);ListCreat(C,10,c);
    //调用函数进行数据处理
    Opitimized_comment_elem_creat(A,B,C);
    //打印输出C
    for(int i=0;i<C.length;i++) cout << C.elem[i] << " ";


}
