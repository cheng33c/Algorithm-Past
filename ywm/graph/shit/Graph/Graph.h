#include <iostream>
#include <cstring>
using namespace std;

#define MAX_VERTEX_NUM 20
#define TRUE           1
#define FALSE          0
#define INF            32767

/*
    DG      ：     有向连接表
    DN      ：     有向连接表矩阵
    UDG     ：     无向邻接表
    UDN     ：     无向邻接矩阵

*/
#ifndef _GRAPH_ENUM_
#define _GRAPH_ENUM_
typedef enum {DG,DN,UDG,UDN} GraphKind;
#endif
typedef char                 InfoType;
typedef int                  VRType;
typedef char                 *VertexType;