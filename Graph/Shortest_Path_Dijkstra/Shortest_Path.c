/*最短路径迪杰斯特拉（Dijkstra）算法*/

#include <stdio.h>

#define MAXVEX 20
#define MAXEDGE 20
#define GRAPH_INFINITY 65535

typedef int VertexType;
typedef int EdgeType;

typedef int ShortPathTable[MAXVEX]; //存储最短路径之和
typedef int Patharc[MAXVEX];    //存储最短路径节点的前驱

typedef struct 
{
    VertexType vexs[MAXVEX];
    EdgeType arc[MAXVEX][MAXVEX];
    int numVertexs,numEdges;
}MGarph;

void CreateMGarph(MGarph *G)
{
    int i,j;
    G->numVertexs = 9;
    G->numEdges = 16;

    //初始化顶点
    for(i=0; i<G->numVertexs;i++)
    {
        G->vexs[i] = i;
    }

    //初始化边的权值
    for(i=0; i<G->numVertexs; i++)
    {
        for(j=0; j<G->numVertexs; j++)
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

    for(i=0; i<G->numVertexs;i++)
    {
        for(j=0; j<G->numVertexs;j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

void ShortPathDikstra(MGarph G, int v0,ShortPathTable *D,Patharc *P)
{
    int i,j,k,min;
    int finall[MAXVEX];

    //初始化
    for(i=0; i<G.numVertexs; i++)
    {
        finall[i] = 0;          //开始都为零，及都没访问
        (*D)[i] = G.arc[v0][i];     //开始存储v0的边的权值
        (*P)[i] = -1;              //初始化前驱，-1默认无前驱
    }
    (*D)[v0] = 0;               //v0至v0默认为零
    finall[v0] = 1;               //v0之身不需要访问

    for(i=1; i<G.numVertexs; i++)
    {
        min = GRAPH_INFINITY;
        for(j=0; j<G.numVertexs;j++)        //寻找离v0最近的的顶点
        {
            if(!finall[j] && (*D)[j] < min)     
            {          
                k = j;
                min = (*D)[j];              //寻找最小值
            }
        }
        finall[k] = 1;
        for(j=0; j<G.numVertexs; j++)
        {
            //如果该顶点未被访问过，且该顶点的路径比之前的路径还有短
            if(!finall[j] && (min+G.arc[k][j])<(*D)[j])
            {
                (*D)[j] = min+G.arc[k][j];      //修改当前的路径长度
                (*P)[j] = k;                    //该顶点j的前驱是k
            }
        }
    }
}

int main()
{
    int i,j;
    MGarph G;
    Patharc P;
    ShortPathTable D;
    
    int v0=0;
    
    CreateMGarph(&G);

    ShortPathDikstra(G,v0,&D,&P);

    printf("最短路径的倒叙如下:\n");
    for(i=1; i<G.numVertexs; i++)
    {
        printf("v%d - v%d ",v0,i);
        j = i;
        while(P[j] != -1)         //当某顶点未到末尾
        {
            printf("v%d ",P[j]);     //打印该顶点前驱
            j = P[j];               //寻找顶点j的前驱
        }
        printf("\n");
    }

    printf("\n源点到各顶点的最短路径长度为:\n");
    for(i=1; i<G.numVertexs; i++)
    {
        printf("v%d - v%d : %d \n",G.vexs[0],G.vexs[i],D[i]);
    }
    
    return 0;
}