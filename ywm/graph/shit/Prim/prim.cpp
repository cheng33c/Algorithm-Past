#include <iostream>
#include <cstring>
using namespace std;


#define MAX_VERTEX_NUM 20
#define TRUE           1
#define FALSE          0
#define INF            32767

typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef char                 InfoType;
typedef int                  VRType;
typedef char*                VertexType;

typedef struct {
  VRType    adj;
  InfoType* info;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
  VertexType vexs[MAX_VERTEX_NUM];
  AdjMatrix  arcs;
  int        vexnum,arcnum;
  GraphKind  kind;
} MGraph;

int LocateVex_MG(MGraph G, VertexType x)
{
  int k;
  for (k = 0; strcmp(G.vexs[k],x); k++) ;
  return k;
}

void CreateUDN(MGraph& G)
{
  int w, i, j;
  VertexType v1, v2;
  cout << "Input vexnum, arcnum = ";
  cin >> G.vexnum >> G.arcnum;
  cout << "Input vexs[vexnum] = ";

  // Init Graph
  for (i = 0; i < G.vexnum; i++) {
    G.vexs[i] = new char[10];
    cin >> G.vexs[i];
  }

  for (i = 0; i < G.vexnum; i++) {
    for (j = 0; j < G.vexnum; j++) {
      G.arcs[i][j].adj = INF; G.arcs[i][j].info = NULL;
    }
  }

  cout << "Input v1, v2, w = ";
  for (int k = 0; k < G.arcnum; k++) {
    v1 = new char[10]; v2 = new char[10];
    cin >> v1 >> v2 >> w;
    i = LocateVex_MG(G, v1); j = LocateVex_MG(G, v2);
    G.arcs[i][j].adj = w; G.arcs[j][i].adj = w;
    delete v1; delete v2;
  }
}

struct {
  VertexType adjvex;
  VRType     lowcost;
} closedge[MAX_VERTEX_NUM];

void MiniSpanTree_P(MGraph G, VertexType u)
{
  int k = LocateVex_MG(G, u), mincost;
  closedge[k].lowcost = 0; closedge[k].adjvex = new char[10];
  strcpy(closedge[k].adjvex,G.vexs[k]);
  for (int j = 0; j < G.vexnum; ++j) {
    if (j != k) {
      closedge[j].adjvex = new char [10];
      strcpy(closedge[j].adjvex, G.vexs[k]);
      closedge[j].lowcost = G.arcs[k][j].adj;
    }
  }

  for (int i = 0; i < G.vexnum; ++i) {
    mincost = INF;
    for (int m = 0; m < G.vexnum; ++m) {
      if (mincost > closedge[m].lowcost && closedge[m].lowcost != 0) {
        mincost = closedge[m].lowcost;
        k = m;
      }
    }
  }

  if (closedge[k].lowcost != 0) {
    cout << closedge[k].adjvex << "   " << G.vexs[k] << "    "
         << closedge[k].lowcost << endl;
  }

  closedge[k].lowcost = 0;
  for (int j = 0; j < G.vexnum; ++j) {
    if (G.arcs[k][j].adj < closedge[j].lowcost) {
      strcpy(closedge[j].adjvex, G.vexs[k]);
      closedge[j].lowcost = G.arcs[k][j].adj;
    }
  }
}

void DispMat(MGraph G)
{
  cout << "Graph G: " << endl;
  for (int i = 0; i < G.vexnum; i++) {
    for (int j = 0; j < G.vexnum; j++)
      cout << G.arcs[i][j].adj << "  ";
    cout << endl;
  }
}

int main()
{
  MGraph MG;
  CreateUDN(MG);
  DispMat(MG);

  VertexType u = "v1";
  MiniSpanTree_P(MG, u);

  return 0;
}
