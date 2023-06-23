//创建邻接矩阵表
#include <stdio.h>

#define MAXVEX 100          //顶点个数
#define OK 1
#define ERROR 0
#define TRUE 1
#define FASLE 0
#define GRAPH_INFINITY 65535        //边的权值，默认65536，既无链接

typedef int Status;
typedef char VertexType;
typedef int EdgeType;

typedef struct
{
    VertexType vex[MAXVEX];               //该顶点的值
    EdgeType arc[MAXVEX][MAXVEX];           //改顶点边的值
    int numNodes, numEdges;         //当前图中的顶点数与表边数
}MGraph;

void CreateMGraph(MGraph *G)
{
    int i,j,k,w;
    printf("请输入顶点数和边数\n");
    scanf("%d,%d",&G->numNodes,&G->numEdges);
    for(i=0;i<G->numNodes;i++)          //依据VertexType类型,输入顶点数据
        scanf(&G->vex[i]);
    for(i=0;i<G->numNodes;i++)
        for(j=0;i<G->numEdges;j++)            //初始化表边,默认无连接
            G->arc[i][j] = GRAPH_INFINITY;
    for(k=0;k<G->numEdges;k++)
    {
        printf("请输入(vi,vj)上的下标i,下标j,和权w");
        scanf("%d,%d,%d",&i,&j,&w);

        G->arc[i][j] = w;           //给表边附权值
        G->arc[j][i] = G->arc[i][j];        //无向图表边相同
    }
}

int main()
{
    MGraph G;
    CreateMGraph(&G);
    return 0;
}