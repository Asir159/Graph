#include <stdio.h>

#define MAXVEX 20
#define MAXEDGE 20
#define GRAPH_INFINITY 65535

typedef int VextexType;
typedef int VextexEdge;

typedef int Patharc[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];

typedef struct 
{
    VextexType vexs[MAXVEX];
    VextexEdge arc[MAXVEX][MAXVEX];
    int numVextexs,numEdges;
}MGraph;

void CreateMGraph(MGraph *G)
{
    int i,j;
    G->numVextexs = 9;
    G->numEdges = 15;

    for(i=0; i<G->numVextexs; i++)      //初始化图
    {
        G->vexs[i] = i;         //初始顶点
        for(j=0; j<G->numVextexs; j++)
        {
            if(i == j)
             G->arc[i][j] = 0;
            else
             G->arc[i][j] = GRAPH_INFINITY;
        }
    }

    G->arc[0][1]=1;
	G->arc[0][2]=5; 
	G->arc[1][2]=3; 
	G->arc[1][3]=7; 
	G->arc[1][4]=5; 

	G->arc[2][4]=1; 
	G->arc[2][5]=7; 
	G->arc[3][4]=2; 
	G->arc[3][6]=3; 
	G->arc[4][5]=3;

	G->arc[4][6]=6;
	G->arc[4][7]=9; 
	G->arc[5][7]=5; 
	G->arc[6][7]=2; 
	G->arc[6][8]=7;

	G->arc[7][8]=4;

    for(i=0; i<G->numVextexs; i++)
    {
        for(j=0; j<G->numVextexs; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }

}

void Shortest_Path_Floyd(MGraph G,ShortPathTable *D, Patharc *P)
{
    int v,w,k;                    //v:Vextex   w:weight权值

    for(v=0; v<G.numVextexs; v++)
    {
        for(w=0; w<G.numVextexs; w++)               //初始化前驱，各顶点的最小权值
        {
            (*D)[v][w] = G.arc[v][w];               //保存各边权值
            (*P)[v][w] = w;                         //保存某顶点的前驱
        }
    }

    printf("各顶点的最短路径如下\n:");
    for(k=0; k<G.numVextexs; k++)
    {
        for(v=0; v<G.numVextexs; v++)
        {
            for(w=0; w<G.numVextexs; w++)
            {
                if((*D)[v][w] >((*D)[v][k] + (*D)[k][w]))       //如果经过下标为k的顶点比原来两点还要短
                {
                    (*D)[v][w] = (*D)[v][k] + (*D)[k][w];       //则该顶点最短路径为最新的最短路径
                    (*P)[v][w] = (*P)[v][k];                    //将路径设置为经过下标为k的顶点
                }
            }
        }
    }
}

int main()
{
    int v,w,k;
    MGraph G;
    ShortPathTable D;
    Patharc P;
    CreateMGraph(&G);

    Shortest_Path_Floyd(G,&D,&P);

    for(v=0; v<G.numVextexs;v++)
    {
        for(w=0; w<G.numVextexs; w++)
        {
            printf("v%d-v%d weight:%d",v,w,D[v][w]);       //打印各应顶点的权值
            k = P[v][w];        //获取当前顶点的前驱顶点

            while(k != w)           //如果该顶点w跟前驱不相等，则该顶点有前驱
            {
                printf("-> %d",k);      //打印前驱顶点
                k = P[k][w];            //继续调用该顶点的前驱顶点
            }
            printf("-> %d\n",w);       //最后打印该顶点
        }
        printf("\n");
    }

    return 0;
}