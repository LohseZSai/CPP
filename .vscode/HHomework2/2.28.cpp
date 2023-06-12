// 该程序解决了习题2.28中的马踏棋盘问题
// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
using namespace std;

//因为本题中存放的数据是字符串类型所以定义为char


const int StackInitSize = 105;
const int StackInc = 105;


typedef struct position{
    int x,y;
}position;


const int N = 5;
bool visited[N][N]={0}; // 记录每个位置是否已经被访问过,若标记为1则为已访问
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2}; // 马走的8个方向
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

//栈的定义
struct SStack {
    position *base, *top;
    int stacksize;
};

//栈的初始化
bool StackInit(SStack &S){
    S.base = new position[StackInitSize];
    if (!S.base) return false;
    S.top = S.base;
    S.stacksize = StackInitSize;
    return true;
}

//入栈操作
bool Push(SStack &S,position e){
    position *base;
    if (S.top - S.base == S.stacksize){
        base = (position*)realloc(S.base,
        (S.stacksize + StackInc)* sizeof(position));
        if (!base) return false;
        S.base = base; S.top = S.base + S.stacksize;  
        S.stacksize += StackInc;
    }
        *S.top = e;
        S.top++;
        return true;
    }


//顺序栈的出栈操作
bool Pop(SStack &S,position &e){
    if (S.top == S.base) return false;
    S.top --; e = *S.top;
    return true;
}

//获取栈顶元素
bool Gettop(SStack &S,position &e){
    if (S.top == S.base) return false;
    e = *S.base;
    return true;
}
//检查是否为空栈
bool Stackempty(SStack S){
    if (S.top == S.base) return true;
    else return false;
}


struct ChessBoard{
    int a[N][N] = {0};//棋盘规模,没有走过的格子标记为0
    //0表示未走过，1,2,....,表示已经走过的路径，
};


bool chesspath(int x, int y, int cnt, int result[][N]){
    visited[x][y] = true;
    result[x][y] = cnt;  // 记录当前位置的遍历顺序
    if (cnt == N * N) { // 所有位置都已经访问完
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                cout << result[i][j] << '\t';
            }
            cout << endl;
        }
        visited[x][y] = false; // 回溯时取消该位置的标记
        return true;
    }

    for (int i = 0; i < 8; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < N && ny >= 0 && ny < N && !visited[nx][ny]){
            if (chesspath(nx, ny, cnt+1, result)) {
                return true;
            }
        }
    }

    visited[x][y] = false; // 回溯时取消该位置的标记
    result[x][y] = 0;
    return false;
}

int main(){
    int path[N][N] = {0}; // 记录每个位置的遍
    chesspath(0,0,1,path);
}