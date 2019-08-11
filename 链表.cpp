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
bool is_empty(pNode phead);
int length(pNode phead); 
void sort(pNode phead);
bool insert(pNode phead,int pos,int val);
bool delet(pNode phead,int pos,int * val);
bool getele(pNode phead,int i,int * value);
bool clearlist(pNode phead);


int main(void) 
{   int len = 0;

	int val = 0;

    pNode phead = NULL;
   
    phead=creat_list();
    
	traverse(phead);
    
    if(is_empty(phead))
    {
    	printf("该链表为空！\n");
	}
	else
	{
		printf("该链表不为空！\n");
	}
	
	//sort(phead);
	
	//traverse(phead);
	
	//insert(phead,4,2);
	
	//traverse(phead);

	len = length(phead);
	
	//delet(phead,1,&val);
	
	//traverse(phead);
	
	//printf("该链表长度为:%d\n",len);
	getele(phead,3,&val);
	printf("取出的值为：%d",val);
	
    return 0;
}
pNode creat_list(void)
{
	int len;
	int val;
	pNode phead = (pNode)malloc(sizeof(Node));
	printf("输入链表的长度:len=");
	scanf("%d",&len);
	if(NULL == phead)
	{
		printf("分配失败，程序终止！\n");
		exit(-1);
	}
	pNode ptrail=NULL;
	ptrail = phead;
	for (int i=0 ; i<len;i++)
	{
		printf("请输入第%d个节点的值:",i+1);
		scanf("%d",&val);
		pNode pNew = (pNode)malloc(sizeof(Node));
		if(NULL == pNew)
		{
			printf("分配失败，程序终止！\n");
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
bool is_empty(pNode phead)
{
	if(NULL==phead->pNext)
	return true;
	else 
	return false;
}
int length(pNode phead)
{
	int i ;
	pNode p =phead->pNext;
	while(NULL!=p)
	{
		i++;
		p=p->pNext;
	}
	return i;
}
void sort(pNode phead)
{
	pNode p;
	pNode q;
	int t;
	
	for(p=phead->pNext;p!=NULL ; p=p->pNext)
	{
		for(q=p->pNext;q!=NULL ;q=q->pNext)
		{
			if(p->data>q->data)   //shunxu 
			{
				t=p->data;
				p->data=q->data;
				q->data=t;
			}
		}
	}
	return;
}
bool insert(pNode phead,int pos,int val)
{   
    int i = 0;
    pNode q;
    pNode p;
	if(pos>length(phead))
	{
		printf("参数过大！\n");
		return false;
	}
	else
	{
		for(p=phead;p!=NULL;p=p->pNext)
		{
			i++;
			if(pos==i)
			{
				q->pNext=p->pNext;
				q->data=val;
				p->pNext=q;
				return true;
			}
		}
	}
}
bool delet(pNode phead,int pos,int * val)
{
	int i = 0;
	pNode p =phead;
	while(p->pNext!=NULL&&i<pos-1)
	{
		i++;
		p=p->pNext;
	}
	if(i>pos-1||p->pNext==NULL)
	{
		return false;
	}
	pNode q = p->pNext;
	*val = q->data;
	
	p->pNext=p->pNext->pNext;
	free(q);
	return true;
}
bool getele(pNode phead,int i,int * value)
{
	pNode pnew;
	int j=1;
	pnew=phead->pNext;
	while(pnew!=NULL&&j<i)
	{
		pnew=pnew->pNext;
		j++;
	}
	if((pnew== NULL) || j>i)
	{
		return false;
	}
	*value  = pnew->data;
	return true;
}
bool clearlist(pNode phead)
{
	pNode p,q ;
	p=phead->pNext;
	while(p)
	{
		q=p->pNext;
		free(p);
		p=q;
	}
	phead->pNext=NULL;
	return true;
} 
