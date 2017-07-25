#include "Graph.h"

/*
    邻接表存储方法
    adjvex      ：   该弧所指向顶点的位置
    *nextarc    ：   指向下一条弧指针
    *info       ：   该弧相关信息指针
*/
typedef struct ArcNode
{
    int             adjvex;
    struct ArcNode  *nextarc;
    InfoType        *info;
} ArcNode;

/*
    data        ：   顶点信息
    *firstarc   ：   指向第一条依附该定点的弧
*/
typedef struct VNode
{
    VertexType  data;
    ArcNode     *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];


/*
    邻接表结构定义
    kind            ：   图种类标志   
*/
typedef struct
{
    AdjList     vertices;
    int         vexnum, arcnum;
    int         kind;
} ALGraph;

int LocateVex_ALG( ALGraph G, VertexType x )
{
    int k;
    for ( k = 0; strcmp(G.vertices[k].data,x) ; k++ ) ;
    return k;
}

/*
    邻接表的形式说明和建立算法
    构造有向图
*/
void CreateDG_ALG( ALGraph &G )
{
    VertexType v1, v2;
    ArcNode *p;
    int i, j;
 
    cout << "Input vexnum, arcnum = ";
    cin >> G.vexnum >> G.arcnum;
    cout << "Input vertics[vexnum] = ";
    for ( int i = 0; i < G.vexnum; i++ ) {
        G.vertices[i].data = new char[10];
        cin >> G.vertices[i].data;
        G.vertices[i].firstarc = NULL;
    }

    cout << "Input v1, v2 = ";
    for ( int k = 0; k < G.arcnum; k++ ) {
        v1 = new char[10];  v2 = new char[10];
        cin >> v1 >> v2;

        i = LocateVex_ALG(G, v1);
        j = LocateVex_ALG(G, v2);
        p = new ArcNode;
        p->adjvex   = j;
        p->nextarc  = G.vertices[i].firstarc;
        p->info     = NULL;
        G.vertices[i].firstarc = p;
    }
}

void showAdj( ALGraph G )
{
    ArcNode * p;
    cout << "图G的邻接表： " << endl;
    for ( int i = 0; i < G.vexnum; i++ ) {
        cout << G.vertices[i].data << " ";
        p = G.vertices[i].firstarc;
        while ( p != NULL ) {
            cout << p->adjvex << " ";
            p = p->nextarc;
        }
        cout << endl;
    }
}