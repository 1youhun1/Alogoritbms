/* heap.c 堆：左平衡树，数组实现*/
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "heap.h"

#define heap_parent(npos) ((int)(((npos) - 1) / 2)) /*获取堆父节点*/
#define heap_left(npos) (((npos) * 2) + 1)          /*获取堆左节点*/
#define heap_right(npos) (((npos) * 2) + 2)         /*获取堆右节点*/

void heap_init(Heap *heap, int (*compare)(const void *key1,const void *key2),
               void (*destroy)(void *data))
{
    heap->size = 0;
    heap->compare = compare;
    heap->destroy = destroy;
    heap->tree = NULL;

    return;
}

void heap_destroy(Heap *heap)
{
    int i;

    /*删除heap所有结点*/
    if (heap->destroy != NULL)
    {
        for (i = 0; i < heap_size(heap); i++)
        {
            heap->destroy(heap->tree[i]);
        }
    }

    free(heap->tree); 
    memset(heap, 0, sizeof(Heap));

    return;
}

int heap_insert(Heap *heap,const void *data)
{
    void *temp;
    int ipos,ppos;

    /*将heap->tree分配新的大小的内存*/
    if ((temp = (void **)realloc(heap->tree, (heap_size(heap) + 1) * sizeof(void *))) == NULL)
    {
        return ERR;
    }

    heap->tree = temp;
    heap->tree[heap_size(heap)] = (void *)data;

    ipos = heap_size(heap);
    ppos = heap_parent(ipos);

	/*新插入节点与父节点比较，如果大于则交换*/
    while (ipos > 0 && heap->compare(heap->tree[ppos], heap->tree[ipos]) < 0)
    {
        temp = heap->tree[ppos];
        heap->tree[ppos] = heap->tree[ipos];
        heap->tree[ipos] = temp;

        ipos = ppos;
        ppos = heap_parent(ipos);
    }

    heap->size++;
    return OK;
}

/*释放堆顶端节点*/
int heap_extract(Heap *heap,void **data)
{
    void *save,*temp;
    int ipos,lpos,rpos,mpos;

    if (heap_size(heap) == 0)
        return ERR;

    /*提取heap的首结点*/
    *data = heap->tree[0];
    save = heap->tree[heap_size(heap) - 1];

    if (heap_size(heap) - 1 > 0)
    {
        if ((temp = (void **)realloc(heap->tree, (heap_size(heap) - 1) * sizeof(void *))) == NULL)
        {
            return ERR;
        }

        heap->tree = temp;
        heap->size--;
    }
    else
    {
        /*最后一个结点，则直接清空heap*/
        free(heap->tree);
        heap->tree = NULL;
        heap->size = 0;
        return OK;
    }

    /*将最后一个节点复制到顶端*/
    heap->tree[0] = save;

    ipos = 0;
    lpos = heap_left(ipos);
    rpos = heap_right(ipos);

    while(1)
    {
        lpos = heap_left(ipos);
        rpos = heap_right(ipos);

        if (lpos < heap_size(heap) && 
                heap->compare(heap->tree[lpos], heap->tree[ipos]) > 0)
        {
            mpos = lpos;
        }
        else
        {
            mpos = ipos;
        }

        if (rpos < heap_size(heap) && 
            heap->compare(heap->tree[rpos], heap->tree[mpos]) > 0)
        {
            mpos = rpos;
        }

        /*mpos与ipos相等，证明heap已经恢复*/
        if (mpos == ipos)
        {
            break;
        }
        else
        {
            temp = heap->tree[mpos];
            heap->tree[mpos] = heap->tree[ipos];
            heap->tree[ipos] = temp;

            ipos = mpos;
        }
    }
    return OK;
}