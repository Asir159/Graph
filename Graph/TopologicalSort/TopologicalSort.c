#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAXVEX 14
#define MAXEDGE 20

#define GRAPH_INFINITY 65536

typedef int Status;

typedef int VextexType;
typedef int EdgeType;

typedef struct
{
    VextexType vexs[MAXVEX];
    EdgeType arc[MAXVEX][MAXVEX];
    int numVextes,numEdges;
}MGraph;

typedef struct EdgeNode
{
    int adjvex;
    int weight;
    struct EdgeNode* next;
    
}EdgeNode;

typedef struct VextexNode
{
    int in;
    VextexType data;
    EdgeNode *fristedge;
}AjdList[MAXVEX],VextexNode;

typedef struct 
{
    AjdList adjList;
    int numVextexs,numEdges;
}graphAdjList,*GraphADjList;


void CreateMGraph(MGraph *G)
{
    int i,j;
    G->numVextes = MAXVEX;
    G->numEdges = MAXEDGE;

    for(i=0; i<G->numVextes; i++)
    {
        G->vexs[i] = i;
        for(j=0; j<G->numVextes; j++)
        {
            G->arc[i][j] = 0;
        }
    }

    G->arc[0][4]=1;
	G->arc[0][5]=1; 
	G->arc[0][11]=1; 
	G->arc[1][2]=1; 
	G->arc[1][4]=1; 
	G->arc[1][8]=1; 
	G->arc[2][5]=1; 
	G->arc[2][6]=1;
	G->arc[2][9]=1;
	G->arc[3][2]=1; 
	G->arc[3][13]=1;
	G->arc[4][7]=1;
	G->arc[5][8]=1;
	G->arc[5][12]=1; 
	G->arc[6][5]=1; 
	G->arc[8][7]=1;
	G->arc[9][10]=1;
	G->arc[9][11]=1;
	G->arc[10][13]=1;
	G->arc[12][9]=1;
}

void CreateALGraph(MGraph G, GraphADjList *GL)
{
    int i,j;
    EdgeNode *e;

    *GL = (GraphADjList)malloc(sizeof(graphAdjList));
    (*GL)->numEdges = G.numEdges;
    (*GL)->numVextexs = G.numVextes;

    for(i=0; i<G.numVextes;i++)     //初始化各表格
    {
        (*GL)->adjList[i].data = G.vexs[i];
        (*GL)->adjList[i].in = 0;
        (*GL)->adjList[i].fristedge = NULL;
    }

    for(i=0; i<G.numVextes;i++)
    {
        for(j=0;j<G.numVextes;j++)
        {
            if(G.arc[i][j] == 1)
            {
                e = (EdgeNode*)malloc(sizeof(EdgeNode));        //创建一个新节点
                e->adjvex = j;                  //邻接号为j
                e->next = (*GL)->adjList[i].fristedge;      //第一次指向空，头插法
                (*GL)->adjList[i].fristedge = e;
                (*GL)->adjList[j].in++;                //该邻接顶点入度加1
            }
        }
    }
}

//拓扑排序，若G无回路返回1，则为0
Status TopologicalSort(GraphADjList GL)
{
    EdgeNode *e;
    int i,k,gettop;
    int count = 0;
    int top = 0;
    int *stack;

    stack =(int *)malloc(sizeof(int)*GL->numVextexs);
    for(i=0; i<GL->numVextexs; i++)
    {
        if(GL->adjList[i].in == 0)          //如有入度为0，则进栈
        {
            stack[++top] = i;               //需要优先++，如果后续++，在while中top--则会出界
        }
    }

    while(top != 0)         //如果栈未清空，则说明还未完成
    {
        gettop = stack[top--];    //获取出栈顶点      
        printf("%d -> ",GL->adjList[gettop].data);      //打印出栈顶点的数据
        count++;            //计数器+1
        for(e = GL->adjList[gettop].fristedge; e ; e=e->next)       //找到该顶点的邻接顶点
        {
            k = e->adjvex;              //获取改邻接顶点的信息
            if( !(--GL->adjList[k].in))             //由于连接的顶点已完成，所以入度相应减一，当该顶点的入度减一为0时
                stack[++top] = k;                   //将该顶点入栈
        }        
    }
    printf("\n");   
    if(count <GL->numVextexs)           //结束统计是否走完所有顶点，查看是否有回路
            return FALSE;
        else
            return TRUE;
}

int main()
{
    int result;
    MGraph G;
    GraphADjList GL;
    CreateMGraph(&G);
    CreateALGraph(G,&GL);

    result = TopologicalSort(GL);
    printf("result:%d",result);
    return 0;
}