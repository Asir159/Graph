//创建邻接表
#include <stdio.h>
#include <stdlib.h>

#define MAXVEX 100          //顶点个数
#define OK 1
#define ERROR 0
#define TRUE 1
#define FASLE 0
#define GRAPH_INFINITY 65535        //边的权值，默认65536，既无链接

typedef int Status;
typedef char VertexType;
typedef int EdgeType;

typedef struct EdgeNode
{
   int adjvex;              //存储邻接顶点值，对于顶点下标
   EdgeType info;           //存储表边权值，非网图可以不需要
   struct EdgeNode *next;      //链接下一个邻接点
}EdgeNode;

typedef struct VertexNode
{
    VertexType data;
    int in;
    EdgeNode *fristedge;
}VertexNode,AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int numNodes,numEdges;
}GraphAdjList;

void CreateALGraph(GraphAdjList *G)
{
    int i,j,k;
    EdgeNode *e;
    printf("请入顶点数与边数");
    scanf("%d,%d",&G->numNodes,&G->numEdges);
    for(i=0;i<G->numNodes;i++)      //读入顶点信息，建立顶点表
    {
        scanf(&G->adjList[i].data);         //输入顶点信息
        G->adjList[i].fristedge = NULL;     //表边初始化为空
    }

    for(k=0;k<G->numEdges;i++)
    {
        printf("输入边(vi,vj)上的顶点序列号");
        scanf("%d,%d",&i,&j);
        e = (EdgeNode *)malloc(sizeof(EdgeNode));    //内存申请空间
        e->adjvex = j;                               //邻接序号为j
        e->next = G->adjList[i].fristedge;           //将e的指针指向当前，i序号的第一条边，第一次为空
        G->adjList[i].fristedge = e;                //将当前i顶点指针指向e

        e =(EdgeNode *)malloc(sizeof(EdgeNode));    //因为无向图两条邻接为相同
        e->adjvex = i;                              //邻接序号为i
        e->next = G->adjList[j].fristedge;          //将e的指针指向当前j的第一天边
        G->adjList[j].fristedge = e;                //将当前顶点的e
                                    //跟链表头插法基本类似
    }
}

int main()
{
    GraphAdjList G;
    CreateALGraph(&G);
    return 0;
}