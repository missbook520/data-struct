#include<stdio.h>
typedef char vertextype;
typedef int edgetype;
#define maxvex 100
#define infinity 65535

typedef struct {
	vertextype verx[maxvex];
	edgetype arc[maxvex][maxvex];
	int numvertexs,numedge;
}graph;

void crategraph(graph *g)
{
	int i,j,k,w;
	printf("���붥�����ͱ�����\n");
	scanf("%d,%d",&g->numvertexs,&g->numedge);
	for(i=0;i<g->numvertexs;i++)
	{
		scanf(&g->verx[i]);
	}
	for(i=0;i<g->numvertexs;i++)
	{
		for(j=0;j<g->numvertexs;j++)
		{
			g->arc[i][j]=infinity;
		}
	}
	for(k=0;k<g->numedge;k++)
	{
		printf("�����(vi,vj)�ϵ��±�i���±�j��ȨW:\n");
		scanf("%d,%d,%d",&i,&j,&w);
		g->arc[i][j]=w;
		g->arc[j][i]=g->arc[i][j]; 
	}
	printf("finished!\n");
 } 
 
 int main()
 {
 	graph a;
 	crategraph(&a);
 	
 	
 	return 0;
 }
