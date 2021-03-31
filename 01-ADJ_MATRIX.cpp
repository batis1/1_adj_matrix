#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<string>
#include<conio.h>

#define INF 999
#define MAX_VNUM 100
#define MAX 10
int visited[MAX_VNUM];
int adj[MAX][MAX], tree[MAX][MAX], n;
typedef char VertexData[10];
typedef int DataType;

typedef struct{
	VertexData vertex[MAX_VNUM];
	int m[MAX_VNUM][MAX_VNUM];
	int vn,en;

}AdjMatrix;
typedef struct node{
    DataType elem[MAX_VNUM];
    int top;
}SeqStack;
typedef struct{
	DataType data[MAX_VNUM];
	int front;
	int rear;
}SeqQueue;

void InitQueue(SeqQueue *Q);
int IsEmpty(SeqQueue *Q);
int IsFull(SeqQueue *Q);
int EnQueue(SeqQueue *Q,DataType x);
int DeQueue(SeqQueue *Q,DataType *x);
int GetFront(SeqQueue *Q,DataType *x);
void InitStack(SeqStack *S);
int IsFull(SeqStack *S);
int IsEmpty(SeqStack *S);
int Push(SeqStack *S,DataType x);
int Pop(SeqStack *S, DataType *e);
int GetTop(SeqStack *S, DataType *e);
int LocateVertex(AdjMatrix *G,VertexData ve);
int InsertEdge(AdjMatrix *G,VertexData v1,VertexData v2,int w);
int DeletEdge(AdjMatrix *G,VertexData v1,VertexData v2,int w);
void CreateAdjMatrix(AdjMatrix *G);
void DFS_R(AdjMatrix *G,int v0);
void DFS_NoR(AdjMatrix *G,int v0);
void BFS_NoR(AdjMatrix *G,int v0);
void Print(AdjMatrix *G);
void Dijkstra(AdjMatrix *G,int source);
void readmatrix();
int spanningtree(int src);
void display(int cost);
int main()
{
	AdjMatrix G;
	VertexData v1,v2;
	int w,v0,i,select;

	do{
		for(i=0;i<MAX_VNUM;i++)
			visited[i]=0;
		printf("\n********************* The MANUE *********************\n");
		printf("\n************************************************\n\n");
		printf("0.Exit\n");
		printf("1.Create adjacency matrix with keyboard input \n");
		printf("2.Insert an edge\n");
		printf("3.Delete an edge\n");
		printf("4.DFS traversal Recursive\n");
		printf("5.DFS traversal Non-recursive way\n");
		printf("6.BFS traversal\n");
		printf("7.Print\n");
		printf("8.Get MST using Prim\n");
		printf("9.Get Shortest path tree using Dijkstras Algorithm\n");
		

		printf("************************************************\n");
		printf("Enter your select:");
		
		scanf("%d",&select);
		switch(select){
				case 1:
					CreateAdjMatrix(&G);
					printf("Done!");
					break;
				case 2:
					printf("Enter the two end points and weigth to Insert:\n");
					fflush(stdin);
					scanf("%s %s %d",v1,v2,&w);
					if(InsertEdge(&G,v1,v2,w)==1){
							printf("Inserted successfully\n");
							G.en++;
					}else{
							printf("Inserted failed\n");
					}
					break;
				case 3:
					printf("Enter the two end points and weigth to Delete:\n");
					fflush(stdin);
					scanf("%s %s %d",v1,v2,&w);
					if(DeletEdge(&G,v1,v2,w)==1){
						printf("Deleted successfully\n");
					    G.en--;
					}else
						printf("Deleted failed\n");
					break;
				case 4:
					printf("Enter the starting vertex location:\n");
					scanf("%d",&v0);
					visited[v0]=0;
					for(i=0;i<G.vn;i++){ 
						
						if(!visited[i]){
							DFS_R(&G,v0);
							visited[v0]=1;
						}
					}	
					break;
				case 5:
					printf("Enter the starting vertex location:\n");
					scanf("%d",&v0);
					DFS_NoR(&G,v0);
					break;
				case 6:
					printf("Enter the starting vertex location:\n");
					scanf("%d",&v0);
					BFS_NoR(&G,v0);
					break;
				case 7:
					Print(&G);
					break;
				case 8:
					int source, treecost;
					readmatrix();
					printf("\nEnter the Source : ");
					scanf("%d", &source);
					treecost = spanningtree(source);
					display(treecost);
					break;
				case 9:
					printf("Enter the index of strating location:\n");
					fflush(stdin);
					scanf("%d",&v0);

					Dijkstra(&G,v0);
					break;
				default : 
					printf("Selected failed\n");
					break;
		}

	}while(select!=0);
	return 0;
}

void InitQueue(SeqQueue *Q){
     Q->front=Q->rear=0;
}
int IsEmpty(SeqQueue *Q){
   return Q->rear==Q->front;
}
int IsFull(SeqQueue *Q){
  return (Q->rear+1)%MAX_VNUM==Q->front;
}
int EnQueue(SeqQueue *Q,DataType x){	
       if(IsFull(Q))
			return 0;
      Q->data[Q->rear]=x;
      Q->rear=(Q->rear+1)%MAX_VNUM;
      return 1;
}
int DeQueue(SeqQueue *Q,DataType *x){	
      if(IsEmpty(Q))
            return false;
     *x=Q->data[Q->front];
      Q->front=(Q->front+1)%MAX_VNUM;
       return true;
}
int GetFront(SeqQueue *Q,DataType *x){	
      if(IsEmpty(Q))
            return false;
       *x=Q->data[Q->front];
        return true;
}
void InitStack(SeqStack *S){
        S->top=-1;
} 
int IsFull(SeqStack *S){
	return S->top == MAX_VNUM-1;
}
int IsEmpty(SeqStack *S){
    return S->top==-1;
}

int Push(SeqStack *S,DataType x){
     if(IsFull(S))
           return 0; //overflow ,error
      ++S->top;
      S->elem[S->top]=x;
      return 1;
}
int Pop(SeqStack *S, DataType *e)
{
      if(IsEmpty(S))
	     return 0; //underflow
      *e= S->elem[S->top];
      S->top--;
      return 1;
}
int GetTop(SeqStack *S, DataType *e){
      if(IsEmpty(S))
	     return 0; //underflow
      *e= S->elem[S->top];
      return 1;
}
int LocateVertex(AdjMatrix *G,VertexData ve){
	int i;
	for(i=0;i<G->vn;i++)
	{   if(strcmp(G->vertex[i],ve)==0)
            return i;
     }
   return -1;

}
// insert an edge(v1,v2,w) into the graph
int InsertEdge(AdjMatrix *G,VertexData v1,VertexData v2,int w){
       int vi,vj;
       vi=LocateVertex(G,v1);
       if(vi<0){    
			printf("Wrong vertex data \n");
            return 0;
		 }
        vj=LocateVertex(G,v2);
       if(vj<0){ 
		   printf("wrong vertex data \n");
           return 0 ;
		 }
		 G->m[vi][vj]=w;
		 G->m[vj][vi]=w;
     return 1;
}
int DeletEdge(AdjMatrix *G,VertexData v1,VertexData v2,int w)
{ 
	 int vi,vj;
     vi=LocateVertex(G,v1);
     if(vi<0){    
		 printf("wrong vertex data \n");
         return 0;
      }
      vj=LocateVertex(G,v2);
      if(vj<0){ 
		  printf("wrong vertex data \n");
           return 0 ;
      }
	  G->m[vi][vj]=0;
	  G->m[vj][vi]=0;

     return 1;
}
//Create AdjMatrix for a UDG
void CreateAdjMatrix(AdjMatrix *G)
{   
	int i,j,k;
    VertexData ic,jc;
    int w;

// step 1: input vertex and edge number
	 printf("Enter vertex number and edge number:");
	 scanf("%d %d",&G->vn,&G->en);
	 printf("\nEnter all vertex:\n");
	
//step2 input all the vertex data to create vertex list
    for(i=0;i<G->vn;i++)
	{
		scanf("%s",G->vertex[i]);
	}			
    for(i=0;i<MAX_VNUM;i++)
            for(j=0;j<MAX_VNUM;j++)
				G->m[i][j]=INF;
// step3 input all edge information to edge matrix
	
    printf("\nEnter edge's two endpoints:\n");
    for(k=0;k<G->en;k++) 
	{    
		   scanf("%s %s %d",ic,jc,&w); 
				InsertEdge(G,ic,jc,w);
    }//end for
} // end CreateALGraph
 

/*Depth first travase the graph in recursive way it can traverse all connected vertex
v0 is starting vertex
*/
void  DFS_R(AdjMatrix *G,int v0) 
{
       int i;
	   printf("%s",G->vertex[v0]);// visit v0, and set the flag of it as visited
       visited[v0]=1;
       for(i=0;i<G->vn;i++)
      { 
              if(G->m[v0][i]>0 && !visited[i])   
                   DFS_R(G,i);  
              /* in the same way traverse the rest of graph but now start from vertex i*/
       }
} /*DepthFirstSearch*/

/*  depth first traverse the graph in non-recursive way  v0 is starting vertex  we need a stack to store the traversed vertex  */
void DFS_NoR(AdjMatrix *G,int v0)  
{
    SeqStack S;
    int v,i;
    InitStack(&S);  /*initialze the stack */
    Push(&S,v0);
    while(!IsEmpty(&S))
   {  
	    Pop(&S,&v);     // pop a vertex from stack
        if(!visited[v])  /*if this vertex is not visited */
          { 
               printf("%s",G->vertex[v]);
               visited[v]=1; 
          }
     // find its first adjacency vertex  which is not visited and push it into stack
    for(i=0;i<G->vn;i++)
            if( G->m[v][i]>0 && !visited[i])  
                Push(&S,i);
      }
}

/* Breadth-first search the graph in non recursive starting from  vertex v0 it can traverse all the connected vertex it needs a queue  to stored the traversed vertex */
void BFS_NoR(AdjMatrix *G,int v0) 
{    int w,v;
     SeqQueue Q;
     InitQueue(&Q);  /*Initialize the Queue*/ 
     printf("%s",G->vertex[v0]); // visit v0
     visited[v0]=1;// set flag of it as visited
     EnQueue(&Q,v0);/* enqueue v0 */
      while(!IsEmpty(&Q))
    {       DeQueue(&Q,&v);  /*dequeue from queue*/
          for(w=0;w<G->vn;w++)
          {        // find all v's adjacency vertices that has not been visited and put it into queue
                 if(G->m[v][w]>0 && !visited[w])
                {      printf("%s",G->vertex[w]);
                        visited[w]=1;
                       EnQueue(&Q, w);
              }
        }
   }
}

void Print(AdjMatrix *G)
{
	printf("Vertex number:%d\nEdge number:%d\n",G->vn,G->en);
	for(int i=0;i<G->vn;i++)
		printf("%s ",G->vertex[i]);
	printf("\n");
	for(int i=0;i<G->vn;i++)
	{
		for(int j=0;j<i;j++)
			if(G->m[i][j]!=0)
				printf("%s %s %d\n",G->vertex[i],G->vertex[j],G->m[i][j]);
	}
}


using namespace std;

void Dijkstra(AdjMatrix *G,int source)
{
    string path[MAX_VNUM +1];
    bool visited[MAX_VNUM];
		int dist[MAX_VNUM];
		int i,v=source;
		int k,j,min;
    for(i=0;i<G->vn;i++)
    {  
      dist[i]=INF; 
      visited[i]=false;
      path[i] = G->vertex[v];
    }
        	 
   dist[v] = 0;
		
   for (j = 1; j < G->vn; j++) 
   {
  	  min =INF ;
	  // find shortest edge.
      for (i = 0; i <G->vn; i++)
      {
		    if (dist[i] < min && visited[i] == false) 
          {
					      min = dist[i];
					      k = i;
				  }
			}
			visited[k] = true;
		
      for (i = 0; i < G->vn; i++) 
      {
        if (dist[i] > dist[k] + G->m[k][i] && visited[i] == false) 
        {
					  dist[i] = dist[k] + G->m[k][i];
            path[i] = path[k] + G->vertex[i];//vertex[i];
			  }
		  }
	  }
   for(i=0;i<G->vn;i++)
     printf("%s %d\n",path[i].c_str(),dist[i]);
}

void readmatrix()
{
	int i, j;
	printf("\nEnter the number of nodes in the Graph : ");
	scanf("%d", &n);
	printf("\nEnter the adjacency matrix of the Graph For Example:\n");
    printf("0 3 4 9999\n");
    printf("9999 0 9999 9\n");
     printf("9999 9999 0 4\n");
    printf("9999 9999 9999 0\n\n");
	printf("Enter the adj matrix:\n");
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			 scanf("%d", &adj[i][j]);
}
int spanningtree(int src)
{
		int visited[MAX], d[MAX], parent[MAX];
		int i, j, k, min, u, v, cost;
		for (i = 1; i <= n; i++){
				d[i] = adj[src][i];
				visited[i] = 0;
				parent[i] = src; 
		}
		visited[src] = 1;
		cost = 0;
		k = 1;
		for (i = 1; i < n; i++)
		{
					min = INF;
					for (j = 1; j <= n; j++){
							if (visited[j]==0 && d[j] < min){
								min = d[j];
								u = j;
							}
					}
					visited[u] = 1;
					cost = cost + d[u];
					tree[k][1] = parent[u];
					tree[k++][2] = u;
					for (v = 1; v <= n; v++)
							if (visited[v]==0 && (adj[u][v] < d[v])){
									d[v] = adj[u][v];
									parent[v] = u;
							}
		}
		return cost;
}
void display(int cost)
{
		int i;
		printf("\nThe Edges of the Mininum Spanning Tree are:\n");
		for (i = 1; i < n; i++)
				printf(" %d %d \n", tree[i][1], tree[i][2]);
		printf("\nThe Total cost of the Minimum Spanning Tree is : %d\n", cost);
}
/*
9 17
A B C D E F G H I
A B 3
A C 7
A E 5
B D 7
B C 1
E C 3
E F 2
C D 2
C H 1
C F 3
D G 1
F I 4
F H 3
D H 3
H G 3
H I 2
G I 5
****
Sample for MST:
5
0 7 3 9999 9999
7 0 4 9 11
3 4 0 10 9999
9999 9 10 0 9999
9999 11 9999 9999 0

the result:
1 3
3 2
2 4
2 5
cost is : 27
****
5 6
ABCDE
A B 1
A D 1
C B 1
E C 1
B D 1
D E 1
****
5 6
A
B
C
D
E
A B 
A D 
C B 
E C 
B D 
D E
*****
4 4
A B C D
A B 3
A C 4
B D 9
C D 4
****
0 3 4 9999
9999 0 9999 9
9999 9999 0 4
9999 9999 9999 0


*/










