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
    int adjvex;       
    int adj;          // 权
    ArcNode *nextarc; 
} *ArcPtr;
struct VexNode
{
    VexType data;    
    ArcPtr firstarc; 
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

void CreatGraph(ALGraph &G, char fn[]) // 建立图
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

// 插入一个顶点
bool InsertVertex(ALGraph &G, VexType v)
{
    int i = G.vexnum + 1;

    if (i >= MVN)
    {
        cout << "图的顶点数已达到最大限制，无法插入新顶点。" << endl;
        return false;
    }
    int j = LocatedVex(G, v);
    if (j > 0)
    {
        return false;
    }
    G.vexs[i].data = v;
    G.vexs[i].firstarc = NULL;
    G.vexs[i].visited = false;
    G.vexnum++;
    return true;
}

// 删除一条弧
bool DeleteArc(ALGraph &G, VexType u, VexType v)
{
    int i = LocatedVex(G, u);
    int j = LocatedVex(G, v);

    if (i == 0 || j == 0)
    {
        // 顶点 u 或 v 不存在
        return false;
    }

    ArcPtr p = G.vexs[i].firstarc;
    ArcPtr pre = NULL;

    while (p != NULL)
    {
        if (p->adjvex == j)
        {
            // 找到待删除的弧
            if (pre == NULL)
            {
                // 待删除的弧是第一条弧
                G.vexs[i].firstarc = p->nextarc;
            }
            else
            {
                // 待删除的弧不是第一条弧
                pre->nextarc = p->nextarc;
            }

            delete p;
            G.arcnum--;
            return true;
        }

        pre = p;
        p = p->nextarc;
    }

    // 没找到待删除的弧
    return false;
}

// 删除一个顶点
bool DeleteVertex(ALGraph &G,VexType v)
{
	int i,j;
	i=LocatedVex(G,v);
	if(i == 0) return false;
	bool f;
	ArcPtr m,n;
	m = G.vexs[i].firstarc;
	while(m)
	{
		n = m;
		m = m->nextarc;
		delete n;
		G.arcnum--;
	}
	for(j=1;j<=G.vexnum;j++)
	{
		if(i != j)
		{

			n = NULL;
			for(f=false,m=G.vexs[j].firstarc;m && !f;m=m ->nextarc)
			{
				if(m ->adjvex==i) { f=true; break; }
				else { n = m; }
			}
			if(!f) continue;
			if(n) { n ->nextarc = m ->nextarc;}
			else  { G.vexs[j].firstarc = m ->nextarc; }
			delete m;
			G.arcnum--;
		}
	}
	G.vexs[i] = G.vexs[G.vexnum];
	for(j=1;j<=G.vexnum-1;j++)
	{
		for(m=G.vexs[j].firstarc;m;m=m ->nextarc)
		{
			if(m ->adjvex==G.vexnum)
			{
				m ->adjvex = i;
				break;
			}
		}
	}
	G.vexnum--;
	return true;
}


int main()
{
    ALGraph graph;
    char fn[] = "test.txt";

    // 创建图
    CreatGraph(graph, fn);

    // 输出初始图的信息
    cout << "初始图的顶点数: " << graph.vexnum << endl;
    cout << "初始图的弧数: " << graph.arcnum << endl;

    // 插入一个顶点
    VexType newVertex = 'd';
    if (InsertVertex(graph, newVertex))
    {
        cout << "成功插入新顶点 " << newVertex << endl;
    }
    else
    {
        cout << "插入新顶点失败" << endl;
    }

    // 输出插入顶点后的图信息
    cout << "插入顶点后的顶点数: " << graph.vexnum << endl;
    cout << "插入顶点后的弧数: " << graph.arcnum << endl;

    // 删除一条弧
    VexType startVertex = 'a';
    VexType endVertex = 'b';
    if (DeleteArc(graph, startVertex, endVertex))
    {
        cout << "成功删除弧 (" << startVertex << ", " << endVertex << ")" << endl;
    }
    else
    {
        cout << "删除弧 (" << startVertex << ", " << endVertex << ") 失败" << endl;
    }

    // 输出删除弧后的图信息
    cout << "删除弧后的顶点数: " << graph.vexnum << endl;
    cout << "删除弧后的弧数: " << graph.arcnum << endl;

    // 删除一个顶点
    VexType vertexToDelete = 'c';
    if (DeleteVertex(graph, vertexToDelete))
    {
        cout << "成功删除顶点 " << vertexToDelete << endl;
    }
    else
    {
        cout << "删除顶点 " << vertexToDelete << " 失败" << endl;
    }

    // 输出删除顶点后的图信息
    cout << "删除顶点后的顶点数: " << graph.vexnum << endl;
    cout << "删除顶点后的弧数: " << graph.arcnum << endl;
}
