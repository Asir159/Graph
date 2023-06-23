#include <stdio.h>

#define MAXVEX 20
#define MAXEDGE 20
#define GRAPH_INFINITY 65535

typedef struct MGraph
{
    int arc[MAXVEX][MAXVEX];
    int numVertexs,numEdges;
}MGraph;

void CreateMGraph(MGraph *G)
{
    int i,j;
    G->numEdges = 15;
    G->numVertexs = 9;

    for(i=0;i<G->numVertexs;i++)
    {
        for(j=0;j<G->numVertexs;j++)
        {
            if(i==j)
                G->arc[i][j] = 0;
            else
                G->arc[i][j] = GRAPH_INFINITY;
        }
    }

    G->arc[0][1]=10;
	G->arc[0][5]=11; 
	G->arc[1][2]=18; 
	G->arc[1][8]=12; 
	G->arc[1][6]=16; 
	G->arc[2][8]=8; 
	G->arc[2][3]=22; 
	G->arc[3][8]=21; 
	G->arc[3][6]=24; 
	G->arc[3][7]=16;
	G->arc[3][4]=20;
	G->arc[4][7]=7; 
	G->arc[4][5]=26; 
	G->arc[5][6]=17; 
	G->arc[6][7]=19; 

    for(i=0; i<G->numVertexs; i++)
    {
        for(j=0; j<G->numVertexs; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

void MiniSpanTree_Prim(MGraph G)
{
    int min,i,j,k;
    int adjvex[MAXVEX];         //存放相关顶点的下标
    int lowcost[MAXVEX];        //存放最小权值

    adjvex[0] = 0;
    lowcost[0] = 0;

    for(i=1; i<G.numVertexs; i++)
    {
        lowcost[i] = G.arc[0][i];       //初始化权值，最小为v0边的权值
        adjvex[i] = 0;
    }

    //找出最小权值
    for(i=1; i<G.numVertexs; i++)
    {
        min = GRAPH_INFINITY;           //初始化最小权值，默认无限大

        for(j=1; j<G.numVertexs; j++)       //循环全部顶点
        {
            if(lowcost[j] != 0 && lowcost[j] < min)    
            {   //如果该顶点权值不为0，且为最小权值
                min = lowcost[j];       //则让当前权值为最小值，继续进行循环，直到循环结束
                k = j;           //将当最小权值的下标赋值给k
            }
        }

        printf("(%d, %d)\n",adjvex[k],k);       //打印顶点边中权值最小的边
        lowcost[k] = 0;     //将当前顶点的权值设置为0，说明已经完成/访问过了
        for(j=1; j<G.numVertexs;j++)
        {
            if(lowcost[j] != 0 && G.arc[k][j]<lowcost[j])
            {   //如果k顶点的各边权值小于此前顶点，说明没有加入生成树，此时加入生成树
                lowcost[j] = G.arc[k][j];       //将较小的权值，加入相应位置
                adjvex[j] = k;              //将下标为k的顶点存入邻接顶点数组中
            }
        }
    }

}

int main()
{
    MGraph G;
    CreateMGraph(&G);
    MiniSpanTree_Prim(G);

    return 0;
}