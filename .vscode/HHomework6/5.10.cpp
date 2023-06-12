#include <iostream>
#include <fstream>

using namespace std;
const int Infinity = 0;
const int MVN = 21;
typedef char VexType;

struct VexCell
{
    VexType data;
    bool visited;
};

struct ArcCell
{
    int adj;
};

struct MGraph
{
    VexCell vexs[MVN];
    ArcCell arcs[MVN][MVN];
    int kind,vexnum,arcnum;
};

int LocateVex(MGraph &G,VexType v)
{
    int i;
    for(i=G.vexnum;i>0 && G.vexs[i].data!=v;i--);
    return i;
}

bool InsertArc(MGraph &G,VexType u,VexType v,int w=1)
{
    int i,j;
    i = LocateVex(G,u); if (i==0) return false;
    j = LocateVex(G,v);
    if (j==0 || j==i || G.arcs[i][j].adj!=Infinity) return false;
    G.arcs[i][j].adj = w; G.arcnum++;
    if (G.kind>=3) { G.arcs[j][i].adj=w; G.arcnum++; }
    return true;
}

void CreateGraph(MGraph &G,char fn[])
{
    int i,j,w; VexType u,v; ifstream f;
    f.open(fn); f >>G.kind; i=0;
    while(true)
    {
        f>>u;if (u == '#') break; i++; G.vexs[i].data = u;
    }
    G.vexnum = i;
    for(i=1;i<=G.vexnum;i++)
        for(j=1;j<=G.vexnum;j++)
            G.arcs[i][j].adj = Infinity;
    G.arcnum = 0;
    while(true)
    {
        f>>u>>v; if (u=='#' || v=='#') break;
        if (G.kind == 1 || G.kind == 3) w = 1; else f>>w;
        InsertArc(G,u,v,w);
    }
    f.close();
}

void GraphTraverse(MGraph G)
{
    int i,j;
	if(G.vexnum == 0) cout << "图为空" <<endl;
	cout <<"顶点集为: ";
	for(i=1;i<=G.vexnum;i++) cout << G.vexs[i].data <<' ';
	cout <<endl;
	cout << "顶点数:" << G.vexnum <<endl;
	if(G.kind <= 2) // 有向图（网）
	{
	    cout << "弧数： " << G.arcnum << endl;
		cout <<"邻接矩阵: " <<endl;
		for(i=1;i<=G.vexnum;i++)
            {
                for(j=1;j<=G.vexnum;j++)
				    cout << G.arcs[i][j].adj <<" ";
                cout << endl;
            }
	}
	else // 无向图（网）
	{
	    cout << "边数： " << G.arcnum / 2 << endl;
		cout << "边: ";
		for(i=1;i<=G.vexnum;i++)
            {
                for(j=1;j<=G.vexnum;j++)
				    cout << G.arcs[i][j].adj <<" ";
                cout << endl;
            }
	}
}

bool InsertVex(MGraph &G,VexType v)
{
    int i,j;
    i = LocateVex(G,v);
    if (i != 0) return false;
    if (G.vexnum >= MVN) return false;
    G.vexnum++;
    G.vexs[G.vexnum].data = v;
    G.vexs[G.vexnum].visited = false;
    for (j=1;j<=G.vexnum;j++)
    {
        G.arcs[j][G.vexnum].adj = Infinity;
        G.arcs[G.vexnum][j].adj = Infinity;
    }
    return true;
}

bool DeleteArc(MGraph &G,VexType v,VexType u)
{
    int i,j;
    i = LocateVex(G,v);
    if (i==0) return false;
    j = LocateVex(G,u);
    if (j==0 || j==i || G.arcs[i][j].adj==Infinity) return false;
    G.arcs[i][j].adj = Infinity; G.arcnum--;
    if (G.kind >= 3) { G.arcs[j][i].adj = Infinity; G.arcnum--; }
    return true;
}

bool DeleteVex(MGraph &G,VexType v)
{
    int i,j;
    j = LocateVex(G,v);
    if(j == 0) return false;
    G.vexs[j] = G.vexs[G.vexnum];
    for(i=1;i<G.vexnum;i++)
    {
        if(G.arcs[i][j].adj!=Infinity) G.arcnum--;
        G.arcs[i][j] = G.arcs[i][G.vexnum];
        if(G.arcs[j][i].adj!=Infinity) G.arcnum--;
        G.arcs[j][i] = G.arcs[G.vexnum][i];
    }
    G.vexnum--;
    return true;
}

int main()
{
    MGraph G;
    char fn[] = "test.txt";
    CreateGraph(G,fn);
    VexType v = 'a'; VexType u = 'f'; VexType p = 'c'; VexType q = 'b';
    cout << "原始图为："<<endl;
    GraphTraverse(G);
    cout << endl;
    if (InsertVex(G,v))
    {
        cout << "插入顶点成功" <<endl;
        GraphTraverse(G);
    }
    else cout << "插入顶点失败" <<endl;
    if (InsertVex(G,u))
    {
        cout << "插入顶点成功" <<endl;
        GraphTraverse(G);
    }
    else cout << "插入顶点失败" <<endl;
}

