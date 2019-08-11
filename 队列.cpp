#include<stdio.h>
#include<malloc.h>


/*typedef struct p
{
	int data;
	struct p * pNext;
} node,*pNode;
typedef struct queue
{
	pNode que_top;
	pNode que_bottom; 
 } queue,* pqueue;
*/
#define size 5 
typedef struct 
{
	int data[size];
	int front;
	int rear;
}squeue;
void init_queue(squeue *Q);
bool out_queue(squeue *Q,int *val);
bool insert_queue(squeue *Q,int val);
int  getlength(squeue Q);
void traverse(squeue *Q);
bool empty_queue(squeue *Q);
bool fully_queue(squeue *Q);
int main(void)
{    
    int value;
    int length;
	squeue queue;
	init_queue(&queue);
	traverse(&queue);
	insert_queue(&queue,1);
	insert_queue(&queue,2);
	insert_queue(&queue,3);
	insert_queue(&queue,4);
	traverse(&queue);
	out_queue(&queue,&value);
	//length=getlength(queue);
	printf("delete:%d,length:%d\n",value,length);
	traverse(&queue);
	
	return 0;
	
}
void init_queue(squeue *Q)
{
	Q->front=0;
	Q->rear=0;
}
bool out_queue(squeue *Q,int *val)
{
     if(empty_queue(Q))
     {
     	return false;
	 }
	 else
	 {
	 	*val=Q->data[Q->front];
	 	Q->front=(Q->front+1)%size;
	 	return true;
	 }
}
bool insert_queue(squeue *Q,int val)
{
	if(fully_queue(Q))
	{
		return false;
	}
	else
	{ 
	  Q->data[Q->rear]=val;
	  Q->rear=(Q->rear+1)%size;
	  return true;
	} 
}
bool empty_queue(squeue *Q)
{
	if(Q->rear==Q->front)
	{
	  return true;	
	}
	else
	{
		return false;
	}
}
bool fully_queue(squeue *Q)
{
	if((Q->rear+1)%size==Q->front)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void traverse(squeue *Q)
{   
    printf("start\n");
	if(Q->rear==Q->front)
	{
		printf("this squeue is empty\n");
	}
	if((Q->rear ) > (Q->front))
	{  
	    int i;
		for(i = (Q->front);i<Q->rear;i++)
       {  
       	  printf("%d\n",Q->data[i]);
	   }

	}
	if(Q->rear<Q->front)
	{
		for(int i = Q->front;i<size;i++)
		{
			printf("%d\n",Q->data[i]);
		}
		if(Q->rear!=0)
		{
			for(int j = 0;j<Q->rear;j++)
			{
				printf("%d\n",Q->data[j]);
			}
		 } 
	}
}
