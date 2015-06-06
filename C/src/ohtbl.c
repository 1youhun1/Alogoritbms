/* ohtbl.c 开地址哈希表*/
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "ohtbl.h"

static char vacated;//静态指针

int Ohtbl_Init(OHTbl *htbl, int positions, int (*h1)(const void *key),
               int (*h2)(const void *key), int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data))
{
    int i;

    if (NULL == (htbl->table = (void **)malloc(positions * sizeof(void *))))
        return ERR;

    htbl->positions = positions;
    for(i = 0; i < positions; i++)
        htbl->table[i] = NULL;
    
    htbl->vacated = &vacated;
	//初始化两个hash函数，h(k,i)=(h1(k) + ih2(k))%m
    htbl->h1 = h1;
    htbl->h2 = h2;
    htbl->match = match;
    htbl->destroy = destroy;

    htbl->size = 0;
    return OK;
}

void Ohtbl_Destroy(OHTbl *htbl)
{
    int i;

    if (NULL != htbl->destroy)
    {
        for(i = 0; i < htbl->positions; i++)
        {
			//表内有值且不指向vacated
            if(htbl->table[i] != NULL && htbl->table[i] != htbl->vacated)
                htbl->destroy(htbl->table[i]);
        }
    }

    free(htbl->table);
    memset(htbl,0,sizeof(OHTbl));

    return;
}

int  Ohtbl_Insert(OHTbl *htbl, const void *data)
{
    void *temp = NULL;
    int position = 0,i = 0;

    if (htbl->size == htbl->positions)
        return ERR;
    
    temp = (void *)data;
    if (OK == Ohtbl_Lookup(htbl, &temp))
		return OK;

    for (i = 0; i < htbl->positions; i++)
    {
        position = (htbl->h1(data) + (i * htbl->h2(data))) % htbl->positions;
        //当此位置为NULL或者曾删除过，则可以插入到此位置
        if(NULL == htbl->table[position] || htbl->table[position] == htbl->vacated)
        {
            htbl->table[position] = (void *)data;
            htbl->size++;
            return OK;
        }
    }

    return ERR;
}

int  Ohtbl_Remove(OHTbl *htbl, void **data)
{
    int position = 0, i = 0;

    for (i = 0; i < htbl->positions; i++)
    {
        position = (htbl->h1(data) + (i * htbl->h2(data))) % htbl->positions;
        if (NULL == htbl->table[position])
        {
            return ERR;
        } 
        else if (htbl->table[position] == htbl->vacated)
        {
            //要越过已经删除的位置继续搜索
            continue;
        }
        else if (htbl->match(htbl->table[position], *data))
        {
            *data = htbl->table[position];
            htbl->table[position] = htbl->vacated;
            htbl->size--;
            return OK;
        }
    }

    return ERR;
}

int  Ohtbl_Lookup(const OHTbl *htbl, void **data)
{
    int position = 0, i = 0;

    for (i = 0; i < htbl->positions; i++)
    {
        position = (htbl->h1(data) + (i * htbl->h2(data))) % htbl->positions;
    }

    if (NULL == htbl->table[position])
    {
        return ERR;
    }
    else if (htbl->match(htbl->table[position], *data))
    {
        *data = htbl->table[position];
        return OK;
    }

	//为vacated也失败
    return ERR;
}