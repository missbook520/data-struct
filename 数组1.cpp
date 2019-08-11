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
bool sort(struct Arr * parr,bool direction);//ð������ 
bool getelem(struct Arr * parr,int i,int * e);//���Ԫ�ز��� 


int main(void)
{
	struct Arr arr;//������һ���ṹ��ռ�  ��������δ֪
	int val;
	init_arr(&arr,6);
	append(&arr,6);
	append(&arr,5);
	append(&arr,3);
	append(&arr,4);
	append(&arr,5);
	append(&arr,6);
    show_arr(&arr);
    //delet(&arr,1,&val);
    printf("\n");
	//printf("ɾ����ֵΪ:%d\n",val);
    sort(&arr,1);
    show_arr(&arr);
    getelem(&arr,1,&val);
    //show_arr(&arr);
    printf("\n%d\n",val);
	
	
	return 0;
}

void init_arr(struct Arr * parr,int length)
{
	parr->pBase=(int *)malloc(sizeof(int)*length);
	if(NULL==parr->pBase)
	{
		printf("��ַ����ʧ��\n");
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
		printf("�������Ϊ�գ�\n");
	}
	else
	{
		for(int i =0 ; i < parr->cnt ; i++)
		{
			printf("%d  ",parr->pBase[i]);
		}
	}
}
bool append(struct Arr * parr,int pval)
{
	if(is_full(parr))
	{
		printf("�������������ʧ��!\n");
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
		printf("�����������!\n");
		return false;
	}
	else
	{
		if(is_empty(parr))
		{
			printf("�������޷�ɾ��!\n");
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
bool inverse(struct Arr * parr)
{   
     if(is_empty(parr))
     {
     	printf("������Ϊ��!\n");
     	return false;
	 }
	 else
	{
		 int t;
    	 int i=0;
     	 int j=parr->cnt-1;
     	 while(i<j)
    	 {
     		t=parr->pBase[i];
     		parr->pBase[i]=parr->pBase[j];
     		parr->pBase[j]=t;
     		i++;
     		j--;
		 }	
     return true;
	}
} 
bool sort(struct Arr * parr,bool direction)//ð������ 
{
   int t;
   if(direction)//from small to big 
   {
   	  for (int i =0;i<parr->cnt;i++)
   	  	{
   	  		for(int j =i+1;j<parr->cnt;j++)
   	  		{
   	  			if(parr->pBase[i]>parr->pBase[j])
   	  			  {
   	  			  	t=parr->pBase[j];
   	  			  	parr->pBase[j]= parr->pBase[i];
   	  			  	parr->pBase[i]=t;
				  }
				 }
			 }
   	return true;
	} 
	else//from big to small
	{
		  for (int i =0;i<parr->cnt;i++)
   	  	{
   	  		for(int j =i+1;j<parr->cnt;j++)
   	  		{
   	  			if(parr->pBase[i]<parr->pBase[j])
   	  			  {
   	  			  	t=parr->pBase[j];
   	  			  	parr->pBase[j]= parr->pBase[i];
   	  			  	parr->pBase[i]=t;
				  }
				 }
			 }
	return false;
	}
} 
bool  getelem(struct Arr * parr,int i,int * e)
{
	if(is_empty(parr))
	{
		printf("������Ϊ��!\n");
		return false;
	}
	if( i >(parr->cnt))
	{
		printf("���������д�\n");
		return false;
	}
	else
	{
		*e=parr->pBase[i-1];
		return true;
	}
}
