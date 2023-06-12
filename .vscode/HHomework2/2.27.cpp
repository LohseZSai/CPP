// 该程序解决了习题2.27中的括号匹配检测问题
// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
using namespace std;

//因为本题中存放的数据是字符串类型所以定义为char
typedef char SElemType;

const int StackInitSize = 105;
const int StackInc = 105;


//栈的定义
struct SStack {
    SElemType *base, *top;
    int stacksize;
};

//栈的初始化
bool StackInit(SStack &S){
    S.base = new SElemType[StackInitSize];
    if (!S.base) return false;
    S.top = S.base;
    S.stacksize = StackInitSize;
    return true;
}

//入栈操作
bool Push(SStack &S,SElemType e){
    SElemType *base;
    if (S.top - S.base == S.stacksize){
        base = (SElemType*)realloc(S.base,
        (S.stacksize + StackInc)* sizeof(SElemType));
        if (!base) return false;
        S.base = base; S.top = S.base + S.stacksize;  
        S.stacksize += StackInc;
    }
        *S.top = e;
        S.top++;
        return true;
    }


//顺序栈的出栈操作
bool Pop(SStack &S,SElemType &e){
    if (S.top == S.base) return false;
    S.top --; e = *S.top;
    return true;
}

bool Stackempty(SStack S){
    if (S.top == S.base) return true;
    else return false;
}


bool check_it_or_not_pattern(char* a){
    char* p = a;
    SStack(S);StackInit(S);
    for(;*p != '\0';p++){
        // 使用 *p 来访问当前字符
        //如果是左括号就压入栈中
        if (*p == '(' || *p == '[' || *p == '{')  Push(S, *p);
        //如果是右括号就弹出栈顶元素
        SElemType e;//定义e用于储存弹出来的栈顶元素
        if (*p == ')' || *p == ']' || *p == '}'){
            //判断栈内是否有元素，没有元素直接return false
            if(Stackempty(S) == true) return false;
            Pop(S, e);
            //元素弹出后，与当前访问的元素进行比较
            if(*p == ')' && e == '(' || *p == ']' && e == '[' || *p == '}' && e == '{') {
                continue;
            }
            else return false;
        }
    }
    //如果访问完元素后栈内仍有括号，仍然是不符合需求的，return false
    if(Stackempty(S) == false) return false;
    //如果访问的元素全都没毛病，就返回true
    return true;
}

//打印结果的函数
void print_the_answer(bool result) {
    if (result == true) {
        cout << "满足括号匹配要求" << endl;
    } else {
        cout << "不满足括号匹配要求" << endl;
    }
}

int main(){
    char a[] = "sh{scott!![?lohese(lejie)selohe]lohse}lve(shile)yy" ;  //该测试案例符合条件
    //下面三种测试案例为书上的情况
    char b[] = "saodj[asd]adeggg]asdf";
    char c[] = "awfg(aasd(yjyh)scoett";
    char d[] = "[(sji;ee]zhuziln)";
    //最后一种案例方便我自己看有无判断失误
    char e[] = "{([])}";
    //预期应该为，a与e满足，其他均不满足
    cout << "a表达式为：" << a <<" 结果为：" ;
    print_the_answer(check_it_or_not_pattern(a));
    cout << "b表达式为：" << b <<" 结果为：" ;
    print_the_answer(check_it_or_not_pattern(b));
    cout << "c表达式为：" << c <<" 结果为：" ;
    print_the_answer(check_it_or_not_pattern(c));
    cout << "d表达式为：" << d <<" 结果为：" ;
    print_the_answer(check_it_or_not_pattern(d));
    cout << "e表达式为：" << e <<" 结果为：" ;
    print_the_answer(check_it_or_not_pattern(e));

}
