#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 0

#define MAXVEX 10
#define MAXEDGE 13

#define GRAPH_INFINITY 65535

typedef int Status;

typedef int VertexType;
typedef int EdgeType;

int *etv,*ltv; //事件开始最早事件和最迟发生事件
int *stack2;      //用于存储弹出的栈
int top2;          //用于stack2栈的计数器


typedef struct
{
    VertexType vexs[MAXVEX];
    EdgeType arc[MAXVEX][MAXVEX];
    int numVextexs,numEdges;
}MGraph;

typedef struct EdgeNode
{
    int adjvex;
    int weight;
    struct EdgeNode* next;
}EdgeNode;

typedef struct VexNode
{
    int in;
    int data;
    EdgeNode *fristedge;
}VexNode,AdjList[MAXVEX];

typedef struct 
{
    AdjList adjList;
    int numVextes,numEdges;
}graphadjlist,*GraphAdjlist;

void CreateMGraph(MGraph *G)
{
    int i,j;
    G->numVextexs = MAXVEX;
    G->numEdges = MAXEDGE;
    for(i=0; i<G->numVextexs; i++)
    {
        G->vexs[i] = i;
        for(j=0; j<G->numVextexs; j++)
        {
            if(i == j)
                 G->arc[i][j] = 0;
            else
                G->arc[i][j] = GRAPH_INFINITY;
        
        }
    }

    G->arc[0][1]=3;
	G->arc[0][2]=4; 
	G->arc[1][3]=5; 
	G->arc[1][4]=6; 
	G->arc[2][3]=8; 
	G->arc[2][5]=7; 
	G->arc[3][4]=3;
	G->arc[4][6]=9; 
	G->arc[4][7]=4;
	G->arc[5][7]=6; 
	G->arc[6][9]=2;
	G->arc[7][8]=5;
	G->arc[8][9]=3;
}

void CreateALGraph(MGraph G, GraphAdjlist *GL)
{
    int i,j;
    EdgeNode *e;

    //创建初始表
    *GL =(GraphAdjlist)malloc(sizeof(graphadjlist));

    (*GL)->numVextes = G.numVextexs;
    (*GL)->numEdges = G.numEdges;
    
    for(i=0; i<G.numVextexs;i++)        //读取信息，建立邻接顶点表
    {
        (*GL)->adjList[i].data = G.vexs[i];
        (*GL)->adjList[i].in = 0;
        (*GL)->adjList[i].fristedge = NULL;
    }

    for(i=0;i<G.numVextexs;i++)
    {
        for(j=0;j<G.numVextexs;j++)
        {
            if(G.arc[i][j] != 0 && G.arc[i][j] <GRAPH_INFINITY)
            {
                e = (EdgeNode *)malloc(sizeof(EdgeNode));       //创建邻接节点
                e->adjvex = j;              //j为邻接节点号
                e->weight = G.arc[i][j];        //权值赋值
                e->next = (*GL)->adjList[i].fristedge;      //顶点第一条邻边给e，第一次为NULL
                (*GL)->adjList[i].fristedge = e;            //e加入邻接第一条边
                (*GL)->adjList[j].in++;                     //该邻接节点的入度+1
            }
        }
    }
}

Status TopologicalSort(GraphAdjlist GL)
{
    EdgeNode *e;
    int i,k,gettop;
    int *stack;
    int top = 0;
    int count = 0;

    stack = (int *)malloc(sizeof(int)*GL->numVextes);   //创建栈节点
    for(i=0; i<GL->numVextes; i++)      //将入度为0的顶点入栈
        if(GL->adjList[i].in == 0)
            stack[++top] = i;
    top2 = 0;
    etv = (int *)malloc(sizeof(int) * GL->numVextes);
    for(i=0; i<GL->numVextes; i++)      //最早事件开始时间初始化
        etv[i] = 0;
    stack2 = (int *)malloc(sizeof(int) * GL->numVextes);        //初始化拓扑排序列栈

    while(top != 0)
    {
        gettop = stack[top--];          //出栈，并打印该顶点值
        printf("%d -> ",GL->adjList[gettop].data);
        count++;

        stack2[++top2] = gettop;        //将弹出的顶点序号压入拓扑序列的栈

        for(e = GL->adjList[gettop].fristedge;e; e = e->next)    //寻找该顶点的邻边顶点
        {
            k = e->adjvex;      //将邻接顶点号赋值给k
            if(!(--GL->adjList[k].in))      //由于已出栈一个顶点，相应每个邻接顶点入度-1
                stack[++top] = k;               //如果入度为0，该顶点入栈，等待弹出

            if((etv[gettop]+ e->weight) >etv[k])        //求该顶点最早发生事件etv值，因为各事件条件需要全部条件达成才会发生，所以取最大值，
                etv[k] = etv[gettop] + e->weight;       //如果一个顶点需要两个条件达成，一个最早是3，一个最早是5，则最早都有5达成才能发生，所以取最大值
        }
    }
    printf("\n");
    if(count < GL->numVextes)
        return FALSE;
    else 
        return TRUE;
}

void CriticalPath(GraphAdjlist GL)
{
    EdgeNode *e;
    int i,k,gettop;
    int ete,lte;
    TopologicalSort(GL);
    ltv = (int *)malloc(sizeof(int) * GL->numVextes);
    for(i=0; i<GL->numVextes; i++)
        ltv[i] = etv[GL->numVextes-1];  //初始化，默认为源点到汇点的时间值，及最大值

    printf("etv:\t");           //打印事件发生最早事件
    for(i=0;i<GL->numVextes; i++)
    {
        printf("%d ->",etv[i]);
    }
    printf("\n");

    while(top2 != 0)
    {
        gettop = stack2[top2--];                //计算最晚发生事件ltv值
        for(e = GL->adjList[gettop].fristedge; e; e=e->next)        //找到弹出顶点的邻接顶点
        {
            k = e->adjvex;              //将邻接顶点号赋值给k
            if(ltv[k] - e->weight < ltv[gettop])        //弹出顶点的邻接顶点  -  权值【weight(k,j)就是该邻接顶点的边的权值】，最后比小。
                ltv[gettop] = ltv[k] - e->weight;       //则这是该事件的最晚发生时间,
        }
    }

    printf("ltv:\t");           //打印时间最晚发生时间
    for(i=0; i<GL->numVextes; i++)
    {
        printf("%d ->",ltv[i]);
    }
    printf("\n");

    for(i=0; i<GL->numVextes; i++)
    {
        for(e=GL->adjList[i].fristedge; e; e = e->next)
        {
            k = e->adjvex;
            ete = etv[i];           //最早活动发生时间即是时间发生最早时间，ete = etv
            lte = ltv[k] - e->weight;       //最迟活动发生时间，为ltv[i]-weight(k,j),如果工作时间最晚完成时间为10点，工作时间为2小时，最晚时间则为八点
                                            //公式为：l(i) = vl(j) - Weight(k,j)
            if(ete = lte)
            {
                printf("<v%d - v%d> length: %d \n",GL->adjList[i].data,GL->adjList[k].data,e->weight);
            }
        }
    }
}

int main()
{
    MGraph G;
    GraphAdjlist GL;
    CreateMGraph(&G);
    CreateALGraph(G,&GL);
    CriticalPath(GL);
    return 0;
}