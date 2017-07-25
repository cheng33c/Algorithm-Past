#include "Graph.h"

/*
    ArcCell 弧的定义
    VRType         ： 顶点关系类型。无权图用1,0表示是否相邻。带权图表示权值类型
    *info          ： 改弧相关信息指针
*/
typedef struct ArcCell
{
    VRType      adj;
    InfoType    *info;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

/*
    图的定义
    vexs            :   顶点信息
    arcs            :   弧信息
    vexnum, arcnum  :   顶点数，弧数
    kind            :   图种类标志
*/
typedef struct
{
    VertexType      vexs[MAX_VERTEX_NUM];
    AdjMatrix       arcs;
    int             vexnum, arcnum;
    GraphKind       kind;
} MGraph;

/*
    定位值VertexType x在图中的位置
*/
int LocateVex_MG( MGraph G, VertexType x )
{
    int k;
    for ( k = 0; strcmp(G.vexs[k],x) ; k++ ) ;
    return k;
}

/*
    采用邻接矩阵建立无向图
*/
void CreateUDN( MGraph & G )
{
    int w, i, j;
    VertexType v1, v2;

    cout << "Input vexnum, arcnum = ";
    cin >> G.vexnum >> G.arcnum;
    cout << "Input vexs[vexnum] = ";

    // 输入顶点信息，建立顶点表
    for ( int i = 0; i < G.vexnum; i++ ) {
        G.vexs[i] = new char[10];
        cin >> G.vexs[i];
    }

    // 对矩阵进行初始化
    for ( int i = 0; i < G.vexnum; i++ ) {
        for ( int j = 0; j < G.vexnum; j++ ) {
            G.arcs[i][j].adj    = INF;
            G.arcs[i][j].info   = NULL; 
        }
    }
    
    // 读入边的权值
    cout << "Input v1, v2, w = ";
    for ( int k = 0; k < G.arcnum; k++ ) {
        v1 = new char[10];  v2 = new char[10];
        cin >> v1 >> v2 >> w;
        i = LocateVex_MG(G, v1);
        j = LocateVex_MG(G, v2);
        G.arcs[i][j].adj = w;
        G.arcs[j][i].adj = w;

        delete v1;  delete v2;
    }
}

void showAdj( MGraph G )
{
    cout << "图G的邻接矩阵： " << endl;
    for ( int i = 0; i < G.vexnum; i++ ) {
        for ( int j = 0; j < G.arcs[i][j].adj; j++ )
            cout << G.arcs[i][j].adj << " ";
        cout << endl;
    }
}