// 该程序解决了习题2.28中的马踏棋盘问题
// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
using namespace std;

const int StackInitSize = 105;
const int StackInc = 105;

typedef struct position
{
    int x, y, step;
} SElemtype;

const int N = 5;
bool visited[N][N] = {0};                 // 记录每个位置是否已经被访问过,若标记为1则为已访问
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2}; // 马走的8个方向
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// 栈的定义
struct SStack
{
    position *base, *top;
    int stacksize;
};

// 栈的初始化
bool StackInit(SStack &S)
{
    S.base = new SElemtype[StackInitSize];
    if (!S.base)
        return false;
    S.top = S.base;
    S.stacksize = StackInitSize;
    return true;
}

// 入栈操作
bool Push(SStack &S, SElemtype e)
{
    SElemtype *base;
    if (S.top - S.base == S.stacksize)
    {
        base = (SElemtype *)realloc(S.base,
                                    (S.stacksize + StackInc) * sizeof(SElemtype));
        if (!base)
            return false;
        S.base = base;
        S.top = S.base + S.stacksize;
        S.stacksize += StackInc;
    }
    *S.top = e;
    S.top++;
    return true;
}

// 顺序栈的出栈操作
bool Pop(SStack &S, SElemtype &e)
{
    if (S.top == S.base)
        return false;
    S.top--;
    e = *S.top;
    return true;
}

// 获取栈顶元素
bool Gettop(SStack &S, SElemtype &e)
{
    if (S.top == S.base)
        return false;
    e = *(S.top - 1);
    return true;
}

position visittop(SStack &S)
{
    position e;
    e = *(S.top - 1);
    return e;
}
// 检查是否为空栈
bool Stackempty(SStack S)
{
    if (S.top == S.base)
        return true;
    else
        return false;
}

struct ChessBoard
{
    int a[N][N] = {0}; // 棋盘规模,没有走过的格子标记为0
    // 0表示未走过，1,2,....,表示已经走过的路径，
};

// 判断位置是否越界
bool isOutofbound(position p)
{
    if (p.x >= 0 && p.x < N && p.y >= 0 && p.y < N)
        return true;
    return false;
}

bool isRepeat(position p)
{
    if (visited[p.x][p.y] == true)
        return false;
    else
        return true;
}

// 返回能走的位置的数目
int howmany_ways_cango(SStack &S, position p, int j)
{
    int i, countx = 0;
    for (i = 0; i < 8; i++)
    {
        int new_x = p.x + dx[i];
        int new_y = p.y + dy[i];
        position new_pos = {new_x, new_y, j}; // j为此时的步数
        if (isOutofbound(new_pos) && isRepeat(new_pos))
        {
            countx += 1;
            Push(S, new_pos);
        }
    }
    return countx;
}

// 上面那个函数他妈的其实用不着把元素压进去，导致后面一系列奇怪的问题
// 压入元素，纯享版
void kick_their_assto_chessboard(SStack &S, position p, int s)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        int new_x = p.x + dx[i];
        int new_y = p.y + dy[i];
        position new_pos = {new_x, new_y, s};
        if (isOutofbound(new_pos) && isRepeat(new_pos))
        {
            Push(S, new_pos);
        }
    }
}

int only_return_thenumber(SStack &S, position p)
{
    int i, county = 0;
    for (i = 0; i < 8; i++)
    {
        int new_x = p.x + dx[i];
        int new_y = p.y + dy[i];
        position new_pos = {new_x, new_y};
        if (isOutofbound(new_pos) && isRepeat(new_pos))
        {
            county += 1;
        }
    }
    return county;
}

bool is_all_visited(bool visited[][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!visited[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

int return_the_max(int a[][N])
{
    int maxmum = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            maxmum = max(a[i][j], maxmum);
        }
    }
    return maxmum;
}

// 输出解的函数
void prinln_the_result(int a[][N])
{
    for (int i = 0; i < N; i++)
    {
        cout << endl;
        for (int j = 0; j < N; j++)
            cout << a[i][j] << " ";
    }
}

void search_and_delete_the_number(int a[][N], int value, int &m, int &n)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (a[i][j] == value)
            {
                m = i;
                n = j;
                break;
            }
        }
}

// 重新写一下该题的思路，该题只需要找到一个解即可，那么思路即如下：
// 找到下一个能走的位置 -> 走过去 -> 在visited数组中标记为已访问 -> 把路径数组标记为现在的步数 -> 如果没有能走的位置，回退到上一步

void ChessPath(ChessBoard &C, position p)
{ // 输入棋盘以及初始位置
    SStack S;
    StackInit(S);
    // 将初始位置压入栈中
    Push(S, p);
    int j = 1;
    while (!Stackempty(S))
    {
        position e;
        Pop(S, e); // 避免以后回溯的时候还tm回溯到原来的元素
        j += 1;
        if (j == e.step)
            j++;
        int cangoways = howmany_ways_cango(S, e, j);
        visited[e.x][e.y] = true;
        C.a[e.x][e.y] = e.step;

        // 如果无路可走就进入回溯
        if (cangoways == 0)
        {
            int count;
            kick_their_assto_chessboard(S, e, e.step + 1);
            int a = only_return_thenumber(S, e);
            if (only_return_thenumber(S, e) == 0)
            {
                position no_pos;
                Pop(S, no_pos);
                count = j - no_pos.step;
            }

            else
                count = j - e.step;
            while (1)
            {
                int m, n;
                search_and_delete_the_number(C.a, j - 1, m, n);
                visited[m][n] = false;
                C.a[m][n] = 0;
                count--;
                j--;
                if (count == 0)
                    break;
            }
            position nice;
            Gettop(S,nice);
            visited[nice.x][nice.y] = true;
            C.a[nice.x][nice.y] = nice.step;
        }
    }
}
int main()
{
    // 规定棋子的初始位置
    ChessBoard C;
    position p;
    p.x = 0;
    p.y = 0, p.step = 1;
    ChessPath(C, p);
}