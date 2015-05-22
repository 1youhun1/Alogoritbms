/*set.c 集合*/
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "list.h"
#include "set.h"

void Set_Init(Set *set, int (*match)(const void *key1, const void *key2), 
              void (*destroy)(void *data))
{
    List_Init(set, destroy);
	//判断元素是否相同函数
    set->match = match; 

    return;
}


int Set_Insert(Set *set, const void *data)
{
    if (Set_is_Member(set, data))
        return TRUE;

    return List_Ins_Next(set, List_Tail(set), data);
}

int Set_Remove(Set *set, void **data)
{
    ListElmt *member, *prev;

    prev = NULL; 

    /*查找需删除的member*/
    for (member = List_Head(set); member != NULL; member = List_Next(member))
    {
        if (set->match(*data, List_Data(member)))
            break;
		//单项链表删除需要前节点，所以这里记录删除的member前一项
        prev = member; 
    }

    if (NULL == member)
        return ERR;

    return List_Rem_Next(set, prev, data);
}

int Set_Union(Set *setu, const Set *set1, const Set *set2)
{
    ListElmt *member;
    void     *data;

    Set_Init(setu, set1->match, NULL);

    /*先将Set1中元素拷贝到Setu里*/
    for (member = List_Head(set1); member != NULL; member = List_Next(member))
    {
        data = List_Data(member);
        if (OK != List_Ins_Next(setu, List_Tail(setu), data))
        {
            Set_Destroy(setu);
            return ERR;
        }
    }

    //将Set2中元素排除相同元素后拷贝到SetU中，
    for (member = List_Head(set2); member != NULL; member = List_Next(member))
    {
        if (Set_is_Member(set1, List_Data(member)))
        {
            continue; //只拷贝不同项
        } 
        else
        {
            data = List_Data(member);
            if (OK != List_Ins_Next(setu, List_Tail(setu), data))
            {
                Set_Destroy(setu);
                return ERR;
            }
        }
    }
    return OK;
}

int Set_Intersection(Set *seti, const Set *set1, const Set *set2)
{
    ListElmt *member;
    void     *data;

    Set_Init(seti, set1->match, NULL);

    /* 同时存在两个集合的元素才插入到Seti */
    for (member = List_Head(set1); member != NULL; member = List_Next(member))
    {
        if (Set_is_Member(set2, List_Data(member)))
        {
            data = List_Data(member);
            if (OK != List_Ins_Next(seti, List_Tail(seti), data))
            {
                Set_Destroy(seti);
                return ERR;
            }
        }
    }

    return OK;
}

int Set_Difference(Set *setd, const Set *set1, const Set *set2)
{
    ListElmt *member;
    void     *data;

    Set_Init(setd, set1->match, NULL);

    /* 存在set1，但不存在Set2的元素才插入Setd */
    for (member = List_Head(set1); member != NULL; member = List_Next(member))
    {
        if (!Set_is_Member(set2, List_Data(member)))
        {
            data = List_Data(member);
            if (OK != List_Ins_Next(setd, List_Tail(setd), data))
            {
                Set_Destroy(setd);
                return ERR;
            }
        }
    }

    return OK;
}

int Set_is_Member(const Set *set, const void *data)
{
    ListElmt *member;

    for (member = List_Head(set); member != NULL; member = List_Next(member))
    {
        if (set->match(data, List_Data(member)))
            return TRUE;
    }

    return OK;
}

int Set_is_Subset(const Set *set1, const Set *set2)
{
    ListElmt *member;

    /*set1所有元素必须都要在set2中才是子集*/
    for (member = List_Head(set1); member != NULL; member = List_Next(member))
    {
        if (!Set_is_Member(set2, List_Data(member)))
        {
            return OK;
        }
    }

    return TRUE;
}

//判断集合相同，可以判断大小后直接判断是否为子集
int Set_is_Equal(const Set *set1, const Set *set2)
{
    if (Set_Size(set1) != Set_Size(set2))
        return OK;

    return Set_is_Subset(set1, set2);
}