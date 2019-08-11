#include<iostream>
#include<stack>
#include<queue>
#define inf 65536 
using namespace std;
#define MAX_VERTS 20
class Vertex
{
	public:
		Vertex(char lab)
		{
			Label=lab;
			wasvisited = false;
		}
	public:
		bool wasvisited;
		char Label;
};
class Graph
{
	public:
		Graph();
		~Graph();
		void addvertex(char lab);
		void addedge(int start,int end,int weight=1);
		void printmatrix();
		void showVertex(int v);
		void DFS();	
		void BFS(); 
		void prim(); 
	private:
		Vertex* vertexlist[MAX_VERTS];
		int nVerts;
		int adjMat[MAX_VERTS][MAX_VERTS];
		int getAdjUnvisited(int v); 
};
void Graph::BFS()
{
	queue<int> gQueue;
	vertexlist[0]->wasvisited=true;
	showVertex(0);
	gQueue.push(0);
	int vert1,vert2;
	while(gQueue.size()>0)
	{    
		vert1=gQueue.front();
		gQueue.pop();
		vert2=getAdjUnvisited(vert1);
		while((vert2 ) != -1)
		{
			vertexlist[vert2]->wasvisited=true;
			showVertex(vert2);
			gQueue.push(vert2);
			vert2=getAdjUnvisited(vert1);
		}
	    
	}
	for(int j =0;j<nVerts;j++)
	{
		vertexlist[j]->wasvisited=false;
	}
	    
}
void Graph::addvertex(char lab)
{
	vertexlist[nVerts++] = new Vertex(lab);
}
void Graph::addedge(int start,int end,int weight)
{
	adjMat[start][end]=weight;
	adjMat[end][start]=weight;
}
void Graph::printmatrix()
{
	for(int i =0;i<nVerts;i++)
	{
		for(int j=0;j<nVerts;j++)
		{
			cout<<adjMat[i][j]<<"  ";
		
		}	cout<<endl;
	}
}


void Graph::showVertex(int v)//v是顶点的一个下标 
{
	cout<<vertexlist[v]->Label<<" ";
}
int Graph::getAdjUnvisited(int v)
{
	for(int j =0;j<nVerts;j++)
	{
		//cout<<v;
		
		if(((adjMat[v][j])!=0&&(adjMat[v][j])!=inf)&&(vertexlist[j]->wasvisited==false))
			{
				return j;
			}
	}
	return -1;
}
Graph::Graph()
{
	nVerts =0 ;
	for (int i=0;i<MAX_VERTS;i++)
	{
		for(int j=0;j<MAX_VERTS;j++)
		{
			adjMat[i][j]=0;
		}
	}
}
Graph::~Graph()
{
	for(int i = 0;i<nVerts;i++)
	{
		delete vertexlist[i];
	}
}
void Graph::DFS()
{
	stack<int>gStack;
	vertexlist[0]->wasvisited=true;
	showVertex(0); 
	gStack.push(0);
	int v;
	while(gStack.size()>0)
	{
		v=getAdjUnvisited(gStack.top());
	
		if(v==-1)
		{
			gStack.pop();
		
		}
		else
		{
			vertexlist[v]->wasvisited=true;
			gStack.push(v);
			showVertex(v);	
			//cout<<v;
		}
	}
	cout<<endl;
	
	
	for(int j =0;j<nVerts;j++)
	{
		vertexlist[j]->wasvisited=false;
	}
}
void Graph::prim()
{
	int min,i,j,k;
	int adjvex[MAX_VERTS];//保存相关顶点下标 
	int lowcost[MAX_VERTS];//保存相关顶点间边的权值 
	lowcost[0]=0;
	adjvex[0]=0;
	for(i=1;i<nVerts;i++)
	{
		lowcost[i]=adjMat[0][i];
		adjvex[i]=0;
	}
	for(i=1;i<nVerts;i++)
	{
		min = inf;
		j=1;
		k=0;
		while(j<nVerts)
		{
			if(lowcost[j]!=0 && lowcost[j]<min)
			{
				min=lowcost[j];
				k=j;
			 } 
			 j++;
		}
		printf("\n");
		printf("(%d,%d)\n", adjvex[k],k);
		lowcost[k]=0;
		for(j=1;j<nVerts;j++)
		{
			if(lowcost[j]!=0 && adjMat[k][j]<lowcost[j])
			{
				lowcost[j]=adjMat[k][j];
				adjvex[j]=k;
			}
		}
	}
	
	
	
	
	
	
	
	
}

int main()
{
    Graph g;
	g.addvertex('A');
	g.addvertex('B');
	g.addvertex('C');
	g.addvertex('D');
	g.addvertex('E');
	g.addvertex('F');
	g.addvertex('G');
	g.addvertex('H');
	g.addvertex('I');
	g.addedge(0,1,10);
	g.addedge(0,2,inf);
	g.addedge(0,3,inf);
	g.addedge(0,4,inf);
	g.addedge(0,5,11);
	g.addedge(0,6,inf);
	g.addedge(0,7,inf);
	g.addedge(0,8,inf);
	g.addedge(1,0,10);
	g.addedge(1,2,18);
	g.addedge(1,3,inf);
	g.addedge(1,4,inf);
	g.addedge(1,5,inf);
	g.addedge(1,6,16);
	g.addedge(1,7,inf);
	g.addedge(1,8,12);
	g.addedge(2,0,inf);
	g.addedge(2,1,18);
	g.addedge(2,3,22);
	g.addedge(2,4,inf);
	g.addedge(2,5,inf);
	g.addedge(2,6,inf);
	g.addedge(2,7,inf);
	g.addedge(2,8,8); 
	g.addedge(3,0,inf);
	g.addedge(3,1,inf);
	g.addedge(3,2,22);
	g.addedge(3,4,20);
	g.addedge(3,5,inf);
	g.addedge(3,6,inf);
	g.addedge(3,7,16);
	g.addedge(3,8,21);
	g.addedge(4,0,inf);
	g.addedge(4,1,inf);
	g.addedge(4,2,inf);
	g.addedge(4,3,20);
	g.addedge(4,5,26);
	g.addedge(4,6,inf);
	g.addedge(4,7,7);
	g.addedge(4,8,inf);
	g.addedge(5,6,17);
	g.addedge(5,7,inf);
	g.addedge(5,8,inf);
	g.addedge(6,7,19);
	g.addedge(6,8,inf);
	g.addedge(7,8,inf);
	
	

	
	g.printmatrix();
	
	
	cout<<"深度优先搜索的结果：";
	g.DFS(); 
	cout<<"广度优先搜索的结果：";
	g.BFS(); 
	g.prim();
	cout<<endl;
	system("pause");
	return 0;
	

} 
 
