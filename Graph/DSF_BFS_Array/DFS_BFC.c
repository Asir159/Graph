/*深度，和广度算法，数组*/
#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXVEX 9
#define MAXSIZE 9
#define MAXEDGE 15

typedef int Status;
typedef int Boolean;
typedef char VertexType;
typedef int  EdgeType;

Boolean visited[MAXVEX];

typedef struct
{
    VertexType vex[MAXVEX];
    EdgeType arc[MAXVEX][MAXVEX];
    int numVertexs,numEdges;
}MGarph;

typedef struct 
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

Status DeQueue(Queue *Q, int *e)
{
    if(Q->front == Q->rear)
        return ERROR;
     *e = Q->data[Q->front];
     Q->front = (Q->front+1)%MAXSIZE;

     return OK;
}

//创建表图
void CreateGarph(MGarph *G)
{
    int i,j;

    G->numVertexs = 9;
    G->numEdges = 15;
    
    G->vex[0] = 'A';
    G->vex[1] = 'B';
    G->vex[2] = 'C';
    G->vex[3] = 'D';
    G->vex[4] = 'E';
    G->vex[5] = 'F';
    G->vex[6] = 'G';
    G->vex[7] = 'H';
    G->vex[8] = 'I';

    for(i=0; i<G->numVertexs ;i++)
        for(j=0; j<G->numVertexs; j++)
        {
            G->arc[i][j] = 0;
        }

    //标记该顶点有连接
    G->arc[0][1] = 1;
    G->arc[0][5] = 1;

    G->arc[1][2] = 1;
    G->arc[1][8] = 1;
    G->arc[1][6] = 1;

    G->arc[2][3] = 1;
    G->arc[2][8] = 1;

    G->arc[3][4] = 1;
    G->arc[3][7] = 1;
    G->arc[3][6] = 1;
    G->arc[3][8] = 1;

    G->arc[4][5] = 1;
    G->arc[4][7] = 1;

    G->arc[5][6] = 1;
    G->arc[6][7] = 1;

    for(i=0; i<G->numVertexs; i++)
        for(j=0; j<G->numVertexs; j++)
        {
            G->arc[j][i] = G->arc[i][j];      //无向图相邻相等
        }

}

void DFS(MGarph G, int i)
{
    int j;
    visited[i] = TRUE;          //对改顶点进行访问标记
    printf("%c ",G.vex[i]);     //打印当前顶点
    for(j=0;j<G.numVertexs;j++)
    {
        if(!visited[j] && G.arc[i][j] == 1)     //该节点没访问过，且有连接
            DFS(G,j);           //递归调用
    }
}

//深度遍历，相当于树的前序遍历
void DFSTraverse(MGarph G)
{
    int i;
    for(i=0 ;i<G.numVertexs;i++)        //初始化访问顶点
    {
        visited[i] = FALSE;
    }
    for(i=0; i<G.numVertexs;i++)
    {
        if(!visited[i])
            DFS(G,i);
    }
}

//广度遍历，相当于树的层序遍历
void BFCTraverse(MGarph G)
{
    int i,j;
    Queue Q;
    for(i=0; i<G.numVertexs; i++)
    {
        visited[i] = FALSE;
    }
    InitQueue(&Q);          //初始化辅助队列

    for(i=0; i<G.numVertexs; i++)       //对每个节点进行遍历
    {
        if(!visited[i])                 //若某顶点为访问，访问该顶点
        {
            visited[i] = TRUE;          //给该顶点设置访问标识，避免重复访问
            printf("%c ",G.vex[i]);     //打印该节点
            EnQueue(&Q,i);              //将该节点进入队列
            while(!QueueEmpty(Q))       //如果队列不为空
            {
                DeQueue(&Q,&i);            //将该元素出列，赋值给i
                for(j=0;j<G.numVertexs;j++)     //访问该顶点的连接的边
                {
                    if(!visited[j] && G.arc[i][j] == 1)     //如果该顶点i还有边未访问，且该边有连接
                    {
                        visited[j] = TRUE;              //给该顶点设置访问标识，避免重复访问
                        printf("%c ",G.vex[j]);            //打印该顶点
                        EnQueue(&Q,j);                  //将改顶点进入队列，方便后续访问
                    }
                }
            }

        }
    }
}

int main()
{
    MGarph G;
    CreateGarph(&G);
    printf("深度遍历:\n");
    DFSTraverse(G);
    printf("\n广度遍历:\n");
    BFCTraverse(G);
    return 0;
}