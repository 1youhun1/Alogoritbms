/*graph.c ͼ*/
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "graph.h"

void graph_init(Graph *graph, int (*match)(const void *key1, const void *key2),
                void (*destroy)(void *data))
{
    graph->vcount = 0;
    graph->ecount = 0;
    graph->match = match;
    graph->destroy = destroy;

    /*��ʼ���ڽӱ�*/
    List_Init(&graph->adjlists, NULL);
    return;
}

void graph_destroy(Graph *graph)
{
    AdjList *adjlist;

    /*����ڽӱ�*/
    while(List_Size(&graph->adjlists))
    {
        if (List_Rem_Next(&graph->adjlists, NULL, (void **)&adjlist) == 0)
        {
            Set_Destroy(&adjlist->adjacent);
            if (graph->destroy != NULL)
            {
                graph->destroy(adjlist->vertex);
            }

            free(adjlist);
        }
    }

    List_Destroy(&graph->adjlists);
    memset(graph, 0, sizeof(Graph));
    return;
}

//���붥��
int graph_ins_vertex(Graph *graph, const void *data)
{
    ListElmt *element;
    AdjList *adjlist;
    int result;

    /*����Ƿ����ظ�����*/
    for (element = List_Head(&graph->adjlists); element != NULL;
            element = List_Next(element))
    {
        if (graph->match(data, ((AdjList *)List_Data(element))->vertex))
        {
			return OK;
        }
    }

    if ((adjlist = (AdjList *)malloc(sizeof(AdjList))) == NULL)
    {
        return ERR;
    }

    adjlist->vertex = (void *)data;

	//��ʼ���ö�������ӱ������뵽�ڽӱ�����
    Set_Init(&adjlist->adjacent, graph->match, NULL);    
    if ((result = List_Ins_Next(&graph->adjlists, List_Tail(&graph->adjlists), adjlist)) != 0)
    {
        return result;
    }

    graph->vcount++;
    return OK;
}

//����ߣ����Ϊ��������
int graph_ins_edge(Graph *graph, const void *data1, const void *data2)
{
    ListElmt *element;
    int result;

    /*�ߵ�������������Ѿ���ͼ��*/
    for (element = List_Head(&graph->adjlists); element != NULL;
        element = List_Next(element))
    {
        if (graph->match(data2, ((AdjList *)List_Data(element))->vertex))
        {
            break;
        }
    }
    if (element == NULL)
    {
        return ERR;
    }

    for (element = List_Head(&graph->adjlists); element != NULL;
        element = List_Next(element))
    {
        if (graph->match(data1, ((AdjList *)List_Data(element))->vertex))
        {
            break;
        }
    }
    if (element == NULL)
    {
        return ERR;
    }

	//������2���뵽����1���ڽӱ���
    if ((result = Set_Insert(&((AdjList *)List_Data(element))->adjacent, data2)) != 0)
    {
        return result;
    }

    graph->ecount++;
	return OK;
}

int graph_rem_vertex(Graph *graph, void **data)
{  
    ListElmt *element, *temp, *prev = NULL;
    AdjList *adjlist;
    int found = 0;
                      
    for (element = List_Head(&graph->adjlists); element != NULL;
        element = List_Next(element))
    {
        /*�������λ���ڽӱ�������ɾ��*/
        if (Set_is_Member(&((AdjList *)List_Data(element))->adjacent, *data))
        {
            return ERR;
        }

        if (graph->match(*data, ((AdjList *)List_Data(element))->vertex))
        {
            temp = element;
            found = 1;
        }

        if (!found)
            prev = element;
    }

    /*���㲻���ڣ����ش���*/
    if (!found)
        return ERR;

    /*�����ڽӱ�Ϊ�գ����ش���*/
    if (Set_Size(&((AdjList *)List_Data(temp))->adjacent) > 0)
        return ERR;

    /*ɾ������*/
    if (List_Rem_Next(&graph->adjlists, prev, (void **)&adjlist) != 0)
        return ERR;

    *data = adjlist->vertex;
    free(adjlist);

    graph->vcount--;
	return OK;
}

int graph_rem_edge(Graph *graph, void *data1, void **data2)
{
    ListElmt *element; 
    
    for (element = List_Head(&graph->adjlists); element != NULL;
        element = List_Next(element))
    {
        if (graph->match(data1, ((AdjList *)List_Data(element))->vertex))
            break;
    }

    if (element == NULL)
        return ERR;

    if (Set_Remove(&((AdjList *)List_Data(element))->adjacent, data2) != 0)
        return ERR;

    graph->ecount--;
	return OK;

}

//��ȡ������ڽӱ�
int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist)
{
    ListElmt *element,*prev = NULL;

    for (element = List_Head(&graph->adjlists); element != NULL;
        element = List_Next(element))
    {
        if (graph->match(data, ((AdjList *)List_Data(element))->vertex))
            break;

        prev = element;
    }

    if (element == NULL)
        return ERR;

    *adjlist = (AdjList *)List_Data(element);
	return OK;
}

//�ж����������Ƿ��ڽ�
int graph_is_adjacent(const Graph *graph, const void *data1, const void *data2)
{
    ListElmt *element,*prev = NULL;

    for (element = List_Head(&graph->adjlists); element != NULL;
        element = List_Next(element))
    { 
        if (graph->match(data1, ((AdjList *)List_Data(element))->vertex))
            break;

        prev = element;
    }

    if (element == NULL)
        return ERR;

    return Set_is_Member(&((AdjList *)List_Data(element))->adjacent, data2);
}