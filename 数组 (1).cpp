#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

struct Arr
{
    int * pBase;//the first place of variable
    int len;//the lenth
    int cnt;//the useful data

};
void init_arr(struct Arr * parr,int length);
void show_arr(struct Arr * parr);
bool is_empty(struct Arr * parr);
bool is_full(struct Arr * parr);
bool append(struct Arr * parr,int pval);
bool delet(struct Arr * parr,int pos,int * pval);
bool insert(struct Arr * parr,int pos,int pval);
bool inverse(struct Arr * parr);

int main(void)
{
	struct Arr arr;//分配了一个结构体空间  里面内容未知
	int val;
	init_arr(&arr,6);
	append(&arr,1);
	append(&arr,2);
	append(&arr,2);
	append(&arr,2);
	append(&arr,2);
	append(&arr,6);
    show_arr(&arr);
    delet(&arr,1,&val);
    show_arr(&arr);
	printf("删除的值为:%d\n",val);
	
	
	return 0;
}

void init_arr(struct Arr * parr,int length)
{
	parr->pBase=(int *)malloc(sizeof(int)*length);
	if(NULL==parr->pBase)
	{
		printf("地址分配失败\n");
		exit(-1) ;
	}
	else
	{
	parr->len=length;
	parr->cnt=0;
 	}
}
bool is_empty(struct Arr * parr)
{
	if (parr->cnt == 0)
		return true;
	else
		return false;
	
}
bool is_full(struct Arr * parr)
{
	if (parr->cnt==parr->len)
		return true;
	else
		return false;
}
void show_arr(struct Arr * parr)
{
	if(is_empty(parr))
	{
		printf("这个数组为空！\n");
	}
	else
	{
		for(int i =0 ; i < parr->cnt ; i++)
		{
			printf("%d\n",parr->pBase[i]);
		}
	}
}
bool append(struct Arr * parr,int pval)
{
	if(is_full(parr))
	{
		printf("数组已满，添加失败!\n");
		return false;
	}
	else
	{
		parr->pBase[parr->cnt]=pval;
		(parr->cnt)++;
		return true;	
	}
}
bool delet(struct Arr * parr,int pos,int * pval)
{
	if(pos<1||pos>(parr->cnt))
	{
		printf("输入参数有误!\n");
		return false;
	}
	else
	{
		if(is_empty(parr))
		{
			printf("空数组无法删除!\n");
			return false;
		}
		else 
		{   *pval=parr->pBase[pos-1];
			for( int i = pos ; i<parr->cnt ; i++)
			{
				parr->pBase[i-1]=parr->pBase[i];
			}
			//*pval=parr->pBase[pos-1]; 
			parr->cnt--;
			return true;
		}
	}
}
