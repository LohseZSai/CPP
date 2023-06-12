#include <iostream>
#include <fstream>
using namespace std;
const int Infinity=-1;
typedef char VexType;
const int MVN=21;
struct VexCell{
    VexType data;
    bool visited;
};
struct ArcCell{
    int adj;
};
struct MGraph{
    VexCell vexs[MVN];
    ArcCell arcs[MVN][MVN];
    int kind,vexnum,arcnum;
};
int LocateVex(MGraph &G,VexType v){
    int i;
    for(i=G.vexnum;i>0&&G.vexs[i].data!=v;i--);
    return i;
}
//插入点
void InsertVex(MGraph &G,VexType v){
    if(LocateVex(G,v)>0)return;
    G.vexs[G.vexnum+1].data=v;
    G.vexnum++;
    for(int i=1;i<=G.vexnum;i++){
        G.arcs[G.vexnum][i].adj=0;
        G.arcs[i][G.vexnum].adj=0;
    }
}
//删除点
void DeleteVex(MGraph &G,VexType v){
    int i,j;
    j= LocateVex(G,v);
    if(j==0)return;
    G.vexs[j].data=NULL;//改点数据归为NULL
    G.vexs[j].visited= true;//访问状态改为true
    for(int k=1;i<=G.vexnum;k++){
        if(G.arcs[j][k].adj||G.arcs[k][j].adj)G.arcnum--;  //图减去与改点相连的弧数
        G.arcs[j][k].adj=Infinity;//改点相连的弧邻接矩阵中改为-1
        G.arcs[k][j].adj=Infinity;
    }
    for(i=j;i<G.vexnum;i++){
        G.vexs[i]=G.vexs[i+1];
        for(int k=1;k<=G.vexnum;k++){
            G.arcs[i][k]=G.arcs[i+1][k];
            G.arcs[k][i]=G.arcs[k][i+1];
        }
    }
    G.vexnum--;
}
//删除弧
bool DeleteArc(MGraph &G,VexType u,VexType v,int w=Infinity){
    int i,j;
    i= LocateVex(G,u);if(i==0)return false;
    j= LocateVex(G,v);
    if(j==0||j==i||G.arcs[i][j].adj==w)return false;
    G.arcs[i][j].adj=w;G.arcnum--;
    if(G.kind>=3)G.arcs[j][i].adj=w;  //无向图反向弧的值也改为-1
    return true;
}
//插入弧
bool InsertArc(MGraph &G,VexType u,VexType v,int w=1){
    int i,j;
    i= LocateVex(G,u);if(i==0)return false;
    j= LocateVex(G,v);if(j==0||j==i||G.arcs[i][j].adj!=Infinity)return false;
    G.arcs[i][j].adj=w;G.arcnum++;
    if(G.kind>=3){G.arcs[j][i].adj=w;G.arcnum++;}
    return true;
}
//创建图
void CreateGraph(MGraph &G,char fn[]){
    int i,j,w;VexType u,v;ifstream f;
    f.open(fn);
    f>>G.kind;i=0;
    while(true){
        f>>u;if(u=='#')break;i++;G.vexs[i].data=u;
    }
    G.vexnum=i;
    for(i=1;i<=G.vexnum;i++)
        for(j=1;j<=G.vexnum;j++)G.arcs[i][j].adj=Infinity;
    G.arcnum=0;
    while(true){
        f>>u>>v;if(u=='#'||v=='#')break;
        if(G.kind==1||G.kind==3)w=1;else f>>w;
        InsertArc(G,u,v,w);
    }
    f.close();
}
int main(){
    MGraph G;VexType u,v;
    char fn[]="test.txt";
    CreateGraph(G,fn);
    cout<<G.vexnum<<endl;
    cout<<G.arcnum<<endl;
    CreateGraph(G, fn);
    cout << "Number of vertices: " << G.vexnum << endl;
    cout << "Number of arcs: " << G.arcnum << endl;
}
