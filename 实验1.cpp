#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef struct Node
{
	int data;
	struct Node * pNext;
}Node,*pNode;
pNode creat_list(void);
void traverse(pNode phead);
int main(void) 
{
    pNode phead = NULL;
   
    phead=creat_list();
    
	traverse(phead);
    
    return 0;
}
pNode creat_list(void)
{
	int len;
	int val;
	pNode phead = (pNode)malloc(sizeof(Node));
	printf("��������ĳ���:len=");
	scanf("%d",&len);
	if(NULL == phead)
	{
		printf("����ʧ�ܣ�������ֹ��\n");
		exit(-1);
	}
	pNode ptrail=NULL;
	ptrail = phead;
	for (int i=0 ; i<len;i++)
	{
		printf("�������%d���ڵ��ֵ:",i+1);
		scanf("%d",&val);
		pNode pNew = (pNode)malloc(sizeof(Node));
		if(NULL == pNew)
		{
			printf("����ʧ�ܣ�������ֹ��\n");
			exit(-1);
		}
		pNew->data=val;
		ptrail->pNext=pNew;
	//	pNew->pNext=NULL;
		ptrail=pNew;		
	}
	ptrail->pNext=NULL;
	return phead;
}
void traverse(pNode phead)
{
	pNode p =phead->pNext;
	while(p!=NULL)
	{
		printf("%d ",p->data);
		p=p->pNext;
	}
	printf("\n");
	
	return;
}
