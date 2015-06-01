#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include "list.h"
#include "set.h"

/*邻接表结构体*/
typedef struct AdjList_
{
    void *vertex;   //顶点
    Set adjacent;   //与该顶点邻接的顶点集合
}AdjList;

/*图结构体*/
typedef struct Graph_
{
    int vcount;  //图顶点个数
    int ecount;	 //图边的个数	

    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);

    List adjlists;
}Graph;

/*顶点的颜色*/
typedef enum VertexColor_
{
    WHITE,
    GRAY,
    BLACK
}VertexColor;

void graph_init(Graph *graph, int (*match)(const void *key1, const void *key2),
                void (*destroy)(void *data));
void graph_destroy(Graph *graph);
int graph_ins_vertex(Graph *graph, const void *data);
int graph_ins_edge(Graph *graph, const void *data1, const void *data2);
int graph_rem_vertex(Graph *graph, void **data);
int graph_rem_edge(Graph *graph, void *data1, void **data2);
int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist);
int graph_is_adjacent(const Graph *graph, const void *data1, const void *data2);
#define graph_adjlists(graph) ((graph)->adjlists)
#define graph_vcount(graph) ((graph)->vcount)
#define graph_ecount(graph) ((graph)->ecount)

#endif


