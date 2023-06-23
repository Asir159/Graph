/*深度，和广度算法，邻接表*/
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

#define MAXVEX 9
#define MAXEDGE 15
#define MAXSIZE 9

typedef int Status;
typedef char VextexType;
typedef int EdgeType;
typedef int Boolean;

typedef struct EdgeNode
{
    int adjvex;
    int weigth;
    struct EdgeNode *next;
}EdgeNode;

typedef struct 
{
    VextexType vexs[MAXVEX];
    EdgeType arc[MAXVEX][MAXVEX];
    int numVertexs,numEdges;
}MGraph;

typedef struct VextesNode
{
    int in;
    char data;
    EdgeNode *fristedge;
}VextesNode,AdjList[MAXVEX];

typedef struct 
{
    AdjList adjList;
    int numVertexs,numEdges;
}graphAdjList, *GraphAdjList;



typedef struct Queue
{
    int data[MAXSIZE];
    int front;
    int rear;
}Queue;

Status InitQueue(Queue *Q)
{
    Q->front = 0;
    Q->rear = 0;

    return OK;
}

Status EnQueue(Queue *Q,int e)
{
    if((Q->rear+1)%MAXSIZE == Q->front)
        return ERROR;
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear+1)%MAXSIZE;
    return OK;
}

Status QueueEmpty(Queue Q)
{
    if(Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

Status DeQueue(Queue *Q,int *e)
{
    if(QueueEmpty(*Q))
        return ERROR;
    *e = Q->data[Q->front];
    Q->front = (Q->front+1)%MAXSIZE;
    return OK;
}



void CreateMGarph(MGraph *G)
{
    int i,j;
    G->numEdges= 15;
    G->numVertexs = 9;

    G->vexs[0]='A';
	G->vexs[1]='B';
	G->vexs[2]='C';
	G->vexs[3]='D';
	G->vexs[4]='E';
	G->vexs[5]='F';
	G->vexs[6]='G';
	G->vexs[7]='H';
	G->vexs[8]='I';

    for(i=0; i<G->numVertexs ;i++)
    {
        for(j=0; j<G->numVertexs; j++)
        {
            G->arc[i][j] = 0;
        }
    }

    G->arc[0][1]=1;
	G->arc[0][5]=1;

	G->arc[1][2]=1; 
	G->arc[1][8]=1; 
	G->arc[1][6]=1; 
	
	G->arc[2][3]=1; 
	G->arc[2][8]=1; 
	
	G->arc[3][4]=1;
	G->arc[3][7]=1;
	G->arc[3][6]=1;
	G->arc[3][8]=1;

	G->arc[4][5]=1;
	G->arc[4][7]=1;

	G->arc[5][6]=1; 
	
	G->arc[6][7]=1; 

    for(i=0 ;i<G->numVertexs; i++)
    {
        for(j=0;j<G->numVertexs; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

void CreateALGraph(MGraph G, GraphAdjList *GL)
{
    int i,j;
    EdgeNode *e;

    *GL = (GraphAdjList)malloc(sizeof(graphAdjList));   //创建头指针

    (*GL)->numEdges = G.numEdges;
    (*GL)->numVertexs = G.numVertexs;   

    for(i=0;i<G.numVertexs;i++)         //读取顶点信息，建立顶点表
    {
        (*GL)->adjList[i].data = G.vexs[i];
        (*GL)->adjList[i].fristedge = NULL;
        (*GL)->adjList[i].in = 0;
    }

    for(i=0;i<G.numVertexs;i++)
    {
        for(j=0; j<G.numVertexs-1;j++)
        {
            if(G.arc[i][j] == 1)                    //创建邻接边表
            {
                e = (EdgeNode *)malloc(sizeof(EdgeNode));           //创建邻接边顶点
                e->adjvex = j;

                e->next = (*GL)->adjList[i].fristedge;              //将e的指针指向当前，i序号的第一条边，第一次为空
                (*GL)->adjList[i].fristedge = e;                    //将i顶点的第一条边，指向e
                (*GL)->adjList[j].in++;                             //(vi,vj)进行连接，此时vj的入度加一
            }

        }
    }
}

Boolean visted[MAXVEX];

//深度遍历，相当于树的前序遍历
void DSF(GraphAdjList GL, int i)
{
    EdgeNode *p;
    visted[i] = TRUE;
    printf("%c ",GL->adjList[i].data);
    p = GL->adjList[i].fristedge;

    while(p)
    {
        if(!visted[p->adjvex])
            DSF(GL , p->adjvex);   //对位访问的邻接顶点递归调用
        p = p->next;
    }
}

void DSF_Traverse(GraphAdjList GL)
{
    int i;
    for(i=0; i<GL->numVertexs; i++)         //初始化访问过节点
    {
        visted[i] = FALSE;
    }

    for(i=0;i<GL->numVertexs; i++)          //进行深度遍历
    {
        if(!visted[i])
         DSF(GL, i);
    }
}

//邻接表广度遍历，相当于树的层序遍历
void BFS_Traverse(GraphAdjList GL)
{
    int i;
    Queue Q;
    EdgeNode *p;
    for(i=0; i<GL->numVertexs; i++)
     visted[i] = FALSE;
    
    InitQueue(&Q);
    for(i=0; i<GL->numVertexs; i++)
    {
        if(!visted[i])
        {
            visted[i] = TRUE;
            printf("%c ",GL->adjList[i].data);
            EnQueue(&Q,i);
            while(!QueueEmpty(Q))
            {
                DeQueue(&Q,&i);
                p = GL->adjList[i].fristedge;
                while(p)
                {
                    if(!visted[p->adjvex])
                    {
                        visted[p->adjvex] = TRUE;
                        EnQueue(&Q,p->adjvex);
                        printf("%c ",GL->adjList[p->adjvex].data);
                    }
                    p = p->next;
                }
            }
        }
    }

}

int main()
{
    MGraph G;
    GraphAdjList GL;
    CreateMGarph(&G);
    CreateALGraph(G,&GL);

    printf("深度遍历\n");
    DSF_Traverse(GL);

    printf("\n广度遍历\n");
    BFS_Traverse(GL);
    return 0;
}