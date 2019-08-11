#include<stdio.h>
#include<malloc.h>
# include <stdlib.h>



typedef struct Node
{
	int data;
	struct Node * pNext;
} Node,* pNode;
typedef struct stack
{
	pNode ptop;
	pNode pbottom;
}stack,*pstack;
void initstack(pstack ps);
void traverse(pstack ps);
bool pop(pstack ps,int * val);
bool push(pstack ps,int val);
bool isempty(pstack ps);
bool clear(pstack ps);

int main(void)
{   int val;
	stack s;
	initstack(&s);
	push(&s,1);
	push(&s,2);
	traverse(&s);
	pop(&s,&val);
	traverse(&s);
	printf("删除的值为：%d\n",val);
	clear(&s);
	push(&s,3);
	traverse(&s);
	return 0;
 } 
void initstack(pstack ps)
{   
    ps->ptop=(pNode)malloc(sizeof(Node));
    if(ps->ptop==NULL)
    {
    	exit(-1);
	}
	else
	{
    ps->pbottom=ps->ptop;
    ps->ptop->pNext=NULL;
    }
} 
bool push(pstack ps,int val)
{
	pNode p;
	p=(pNode)malloc(sizeof(Node));
	if(p==NULL)
    {
    	exit(-1);
    	return false;
	}
	else
	{   p->data=val;
		p->pNext=ps->ptop;
		ps->ptop=p;
		return true;
	}
}
void traverse(pstack ps)
{
	pNode p = ps->ptop;

	while (p != ps->pbottom)
	{
		printf("%d  ", p->data);
		p = p->pNext;
	}
	printf("\n");

	return ;
}
bool pop(pstack ps,int * val)
{   
    if(isempty(ps))
    {
    	printf("栈为空！\n");
    	return false;
	}
	else
	{
		pNode p = ps->ptop;
  	 	*val=ps->ptop->data;
    	ps->ptop=p->pNext;
    	free(p);
    	return true;
	}
}
bool isempty(pstack ps)
{
	if(ps->pbottom==ps->ptop)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool clear(pstack ps)
{
	if(isempty(ps))
    {
    	printf("栈为空！\n");
    	return false;
	}
	else
	{
		pNode p = ps->ptop;
		while(ps->ptop!=ps->pbottom)
		{
			ps->ptop=p->pNext;
			free(p);
			p=ps->ptop;
		}
		return true;
	}
}
