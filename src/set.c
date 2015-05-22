/*set.c ����*/
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "list.h"
#include "set.h"

void Set_Init(Set *set, int (*match)(const void *key1, const void *key2), 
              void (*destroy)(void *data))
{
    List_Init(set, destroy);
	//�ж�Ԫ���Ƿ���ͬ����
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

    /*������ɾ����member*/
    for (member = List_Head(set); member != NULL; member = List_Next(member))
    {
        if (set->match(*data, List_Data(member)))
            break;
		//��������ɾ����Ҫǰ�ڵ㣬���������¼ɾ����memberǰһ��
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

    /*�Ƚ�Set1��Ԫ�ؿ�����Setu��*/
    for (member = List_Head(set1); member != NULL; member = List_Next(member))
    {
        data = List_Data(member);
        if (OK != List_Ins_Next(setu, List_Tail(setu), data))
        {
            Set_Destroy(setu);
            return ERR;
        }
    }

    //��Set2��Ԫ���ų���ͬԪ�غ󿽱���SetU�У�
    for (member = List_Head(set2); member != NULL; member = List_Next(member))
    {
        if (Set_is_Member(set1, List_Data(member)))
        {
            continue; //ֻ������ͬ��
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

    /* ͬʱ�����������ϵ�Ԫ�زŲ��뵽Seti */
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

    /* ����set1����������Set2��Ԫ�زŲ���Setd */
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

    /*set1����Ԫ�ر��붼Ҫ��set2�в����Ӽ�*/
    for (member = List_Head(set1); member != NULL; member = List_Next(member))
    {
        if (!Set_is_Member(set2, List_Data(member)))
        {
            return OK;
        }
    }

    return TRUE;
}

//�жϼ�����ͬ�������жϴ�С��ֱ���ж��Ƿ�Ϊ�Ӽ�
int Set_is_Equal(const Set *set1, const Set *set2)
{
    if (Set_Size(set1) != Set_Size(set2))
        return OK;

    return Set_is_Subset(set1, set2);
}