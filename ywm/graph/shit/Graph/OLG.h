#include "Graph.h"

typedef struct ArcBox
{
    int             tailvex, headvex;
    struct ArcBox   *hlink, *tlink;
    InfoType *info;
} ArcBox;

typedef struct VexNode
{
    VertexType data;
    ArcBox     *firstin, *firstout;
} VexNode;

typedef struct
{
    VexNode xlist[MAX_VERTEX_NUM];
    int     vexnum, arcnum;
} OLGraph;

int LocateVex_OLG( OLGraph G, VertexType x )
{
    int k;
    for ( k = 0; strcmp(G.xlist[k].data,x) ; k++ ) ;
    return k;
}

void CreateDG_OLG( OLGraph & G )
{
    VertexType v1, v2;
    ArcBox * p;

    cout << "Input vexnum, arcnum = ";
    cin >> G.vexnum >> G.arcnum;
    cout << "Input xlist[vexnum] = ";
    for ( int i = 0; i < G.vexnum; i++ ) {
        G.xlist[i].data = new char[10];
        cin >> G.xlist[i].data;
        G.xlist[i].firstin = NULL;
        G.xlist[i].firstout = NULL;
    }
}

/* 输出十字链表 */
void showAdj( OLGraph G )
{
    ArcBox * p;
    cout << "图G的十字链表： " << endl;
    for ( int i = 0; i < G.vexnum; i++ ) {
        cout << G.xlist[i].data << " ";
        p = G.xlist[i].firstout;
        while ( p != NULL ) {
            cout << p->tailvex << " " << p->headvex << " ";
            p = p->tlink;
        }
        cout << endl;
    }
    cout << endl;

    for( int i = 0; i < G.vexnum; i++ ) {
        cout << G.xlist[i].data << " ";
        p = G.xlist[i].firstin;
        while ( p != NULL ) {
            cout << p->tailvex << " " << p->headvex << " ";
            p = p->hlink;
        }
        cout << endl;
    }
}