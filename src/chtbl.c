/* chtbl_init 链式哈希表*/
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "list.h"
#include "chtbl.h"

int  Chtbl_Init(CHTbl *htbl, int buckets, int (*h)(const void *key), int 
                (*match)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    int i;

	//申请存放桶的数组
    if (NULL == (htbl->table = (List *)malloc(buckets * sizeof(List))))
        return ERR;

    htbl->buckets = buckets;
    /* 初始化哈希链的每个桶 */
    for (i = 0; i < htbl->buckets; i++)
    {
        List_Init(&htbl->table[i], destroy);
    }
    //求hash值的函数
    htbl->h = h;
    htbl->match = match;
    htbl->destroy = destroy;
    htbl->size = 0;

    return OK;
}

void Chtbl_Destroy(CHTbl *htbl)
{
    int i;

	//销毁每个桶存储的链表
    for (i = 0; i < htbl->buckets; i++)
    {
        List_Destroy(&htbl->table[i]);
    }

	//释放存储每个桶的数组的内存
    free(htbl->table);
    memset(htbl, 0 , sizeof(CHTbl));

    return;
}

int  Chtbl_Insert(CHTbl *htbl, const void *data)
{
    void *temp = NULL;
    int  bucket = 0;
    int  result = 0;

    /* 如果数据已存在，则返回*/
    temp = (void *)data;
    if (OK == Chtbl_Lookup(htbl, &temp))
		return OK;

    //计算hash值
    bucket = htbl->h(data) % htbl->buckets;

    //将数据插入hash值链的链头
    if (OK == (result = List_Ins_Next(&htbl->table[bucket], NULL, data)))
        htbl->size++;

    return result;
}

int  Chtbl_Remove(CHTbl *htbl, void **data)
{
    ListElmt *element = NULL;
    ListElmt *prev = NULL;  //暂存前一项元素的内容，便于释放list
    ListElmt *start_element = NULL;
    int bucket = 0;

    bucket = htbl->h(*data) % htbl->buckets;
    start_element = List_Head(&htbl->table[bucket]);

    /* 在桶里查找数据 */
    for (element = start_element; element != NULL; element = List_Next(element))
    {
        if (htbl->match(*data, List_Data(element)))
        {
            if (OK == List_Rem_Next(&htbl->table[bucket], prev, data))
            {
                htbl->size--;
                return OK;
            } 
            else
            {
                return ERR;
            }
        }        
        prev = element;
    }
    
    //未查找到数据
    return ERR; 
}

int  Chtbl_Lookup(CHTbl *htbl, void **data)
{
    ListElmt *element = NULL;
    ListElmt *start_element = NULL;
    int bucket = 0;

	//计算所在桶的位置
    bucket = htbl->h(*data) % htbl->buckets;
    start_element = List_Head(&htbl->table[bucket]);

    /* 在桶里查找数据 */
    for (element = start_element; element != NULL; element = List_Next(element))
    {
        if (htbl->match(*data, List_Data(element)))
        {
            *data = List_Data(element); 
            return OK;
        }
    }
    
    //未查找到数据
    return ERR; 
}
