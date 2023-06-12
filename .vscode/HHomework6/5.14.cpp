// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
#include <fstream>
using namespace std;
const int Infinity = 0;
typedef char VexType;
const int MVN = 21;
// 图的邻接表表示方法
typedef struct ArcNode
{
    int adjvex;       // 弧指向的顶点位置
    int adj;          // 权
    ArcNode *nextarc; // 指向下一弧的顶点
} *ArcPtr;
struct VexNode
{
    VexType data;    // 顶点数据
    ArcPtr firstarc; // 指向第1条依附于该顶点
    bool visited;    // 该顶点是否被访问过
    int ind;
};
struct ALGraph
{
    VexNode vexs[MVN];
    int kind, vexnum, arcnum; // 类型，顶点数，弧数
};

int LocatedVex(ALGraph &G, VexType v) // 在图中查找顶点
{
    int i;
    for (i = G.vexnum; i > 0 && G.vexs[i].data != v; i--)
        ;
    return i;
}

bool InsertArc(ALGraph &G, VexType u, VexType v, int w = 1) // 在图中插入弧
{
    ArcPtr p;
    int i, j;
    bool found;
    i = LocatedVex(G, u);
    if (i == 0)
        return false;
    j = LocatedVex(G, v);
    if (j == 0 || j == i)
        return false;
    for (found = false, p = G.vexs[i].firstarc; p && !found; p = p->nextarc)
    {
        if (p->adjvex == j)
            found = true;
    }
    if (found)
        return false;
    G.arcnum++;
    p = new ArcNode;
    p->adjvex = j;
    p->adj = w;
    p->nextarc = G.vexs[i].firstarc;
    G.vexs[i].firstarc = p;
    if (G.kind <= 2)
        return true;
    G.arcnum++;
    p = new ArcNode;
    p->adjvex = i;
    p->adj = w;
    p->nextarc = G.vexs[i].firstarc; // 表头插入，假设对弧的次序无要求
    G.vexs[j].firstarc = p;
    return true; // 插入弧成功
}

void CreatGraph(ALGraph &G, char fn[]) // 建立图，图的数据来自文件，文件名为fn
{
    int i, w;
    VexType u, v;
    ifstream f;
    f.open(fn);
    f >> G.kind;
    G.arcnum = 0;
    i = 0;
    while (true)
    {
        f >> u;
        if (u == '#')
            break;
        i++;
        G.vexs[i].data = u;
        G.vexs[i].firstarc = NULL;
    }
    G.vexnum = i;
    while (true)
    {
        f >> u >> v;
        if (u == '#' || v == '#')
            break;
        if (G.kind == 1 || G.kind == 3)
            w = 1;
        else
            f >> w;
        InsertArc(G, u, v, w);
    }
    f.close();
}

bool DFS(ALGraph& G, int i, int b) {
    int j;
    ArcPtr p;
    
    if (i == b) {
        return true;  // 找到了目标顶点b，返回true
    }
    
    G.vexs[i].visited = true;

    for (p = G.vexs[i].firstarc; p; p = p->nextarc) {
        j = p->adjvex;
        if (!G.vexs[j].visited && DFS(G, j, b)) {
            return true;  // 在邻接顶点j的连通部分中找到了目标顶点b，返回true
        }
    }
    
    return false;  // 未找到目标顶点b，返回false
}

bool DFSTraverse(ALGraph& G, int a, int b) {
    int i;

    for (i = 1; i <= G.vexnum; i++) {
        G.vexs[i].visited = false;
    }
    
    return DFS(G, a, b);
}


int main()
{
    ALGraph graph;
    char fn[] = "test.txt";
    VexType start, end;
    int a, b;

    // 创建图
    CreatGraph(graph, fn);

    // 输出初始图的信息
    cout << "初始图的顶点数: " << graph.vexnum << endl;
    cout << "初始图的弧数: " << graph.arcnum << endl;

    // 输入起始顶点和目标顶点
    cout << "请输入起始顶点: ";
    cin >> start;
    cout << "请输入目标顶点: ";
    cin >> end;

    // 判断从起始顶点到目标顶点是否存在路径
    a = LocatedVex(graph, start);
    b = LocatedVex(graph, end);
    if (a == 0 || b == 0) {
        cout << "起始顶点或目标顶点不存在！" << endl;
    } else {
        bool hasPath = DFSTraverse(graph, a, b);
        if (hasPath) {
            cout << "从顶点 " << start << " 到顶点 " << end << " 存在路径。" << endl;
        } else {
            cout << "从顶点 " << start << " 到顶点 " << end << " 不存在路径。" << endl;
        }
    }

}
