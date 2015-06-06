/* chtbl_init ��ʽ��ϣ��*/
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "list.h"
#include "chtbl.h"

int  Chtbl_Init(CHTbl *htbl, int buckets, int (*h)(const void *key), int 
                (*match)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    int i;

	//������Ͱ������
    if (NULL == (htbl->table = (List *)malloc(buckets * sizeof(List))))
        return ERR;

    htbl->buckets = buckets;
    /* ��ʼ����ϣ����ÿ��Ͱ */
    for (i = 0; i < htbl->buckets; i++)
    {
        List_Init(&htbl->table[i], destroy);
    }
    //��hashֵ�ĺ���
    htbl->h = h;
    htbl->match = match;
    htbl->destroy = destroy;
    htbl->size = 0;

    return OK;
}

void Chtbl_Destroy(CHTbl *htbl)
{
    int i;

	//����ÿ��Ͱ�洢������
    for (i = 0; i < htbl->buckets; i++)
    {
        List_Destroy(&htbl->table[i]);
    }

	//�ͷŴ洢ÿ��Ͱ��������ڴ�
    free(htbl->table);
    memset(htbl, 0 , sizeof(CHTbl));

    return;
}

int  Chtbl_Insert(CHTbl *htbl, const void *data)
{
    void *temp = NULL;
    int  bucket = 0;
    int  result = 0;

    /* ��������Ѵ��ڣ��򷵻�*/
    temp = (void *)data;
    if (OK == Chtbl_Lookup(htbl, &temp))
		return OK;

    //����hashֵ
    bucket = htbl->h(data) % htbl->buckets;

    //�����ݲ���hashֵ������ͷ
    if (OK == (result = List_Ins_Next(&htbl->table[bucket], NULL, data)))
        htbl->size++;

    return result;
}

int  Chtbl_Remove(CHTbl *htbl, void **data)
{
    ListElmt *element = NULL;
    ListElmt *prev = NULL;  //�ݴ�ǰһ��Ԫ�ص����ݣ������ͷ�list
    ListElmt *start_element = NULL;
    int bucket = 0;

    bucket = htbl->h(*data) % htbl->buckets;
    start_element = List_Head(&htbl->table[bucket]);

    /* ��Ͱ��������� */
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
    
    //δ���ҵ�����
    return ERR; 
}

int  Chtbl_Lookup(CHTbl *htbl, void **data)
{
    ListElmt *element = NULL;
    ListElmt *start_element = NULL;
    int bucket = 0;

	//��������Ͱ��λ��
    bucket = htbl->h(*data) % htbl->buckets;
    start_element = List_Head(&htbl->table[bucket]);

    /* ��Ͱ��������� */
    for (element = start_element; element != NULL; element = List_Next(element))
    {
        if (htbl->match(*data, List_Data(element)))
        {
            *data = List_Data(element); 
            return OK;
        }
    }
    
    //δ���ҵ�����
    return ERR; 
}
