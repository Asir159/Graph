#include <stdio.h>

#define MAXVEX 20
#define MAXEDGE 20
#define GRAPH_INFINITY 65535

typedef struct 
{
    int arc[MAXVEX][MAXVEX];
    int numVextexs,numEdges;
}MGraph;

typedef struct Edge
{
    int begin;
    int end;
    int weight;
}Edge;


void CreateMGraph(MGraph *G)
{
    int i, j;
    G->numVextexs = 9;
    G->numEdges = 15;

    for(i=0; i<G->numVextexs; i++)
    {
        for(j=0; j<G->numVextexs; j++)
        {
            if(i == j)
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

    for(i=0; i<G->numVextexs; i++)
    {
        for(j=0; j<G->numVextexs; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

//交换，头、尾及权值
void Swap(Edge *edges,int i, int j)
{
    int tmp;
    tmp = edges[i].begin;         
    edges[i].begin = edges[j].begin;
    edges[j].begin = tmp;

    tmp = edges[i].end;
    edges[i].end = edges[j].end;
    edges[j].end = tmp;

    tmp = edges[i].weight;
    edges[i].weight = edges[j].weight;
    edges[j].weight = tmp;
}

//冒泡排序
void Bubble_sort(Edge *edges, MGraph G)
{
    int i,j,flag;
    for(i=0; i<G.numEdges-1; i++)
    {
        flag = 1;
        for(j=0; j<G.numEdges-1-i; j++)
        {
            if(edges[j].weight > edges[j+1].weight)         // 根据权值的大小进行排序
            {
                Swap(edges,j,j+1);
                flag = 0;
            }
        }
        if(flag)
         break;
    }

    printf("权值排序之后为:\n");
    for(i=0; i<G.numEdges; i++)
    {
        printf("(%d,%d) %d\n",edges[i].begin, edges[i].end, edges[i].weight);
    }
}

//查找连接顶点的尾部下标
int Find(int *parent, int f)
{
    while(parent[f] > 0)
    {
        f = parent[f];
    }
    return f;
}

void MiniSpanTree_Kruskal(MGraph G)
{
    int i,j,n,m;
    int k = 0;
    int parent[MAXVEX];
    Edge edges[MAXEDGE];

    //构建边集数组,并且进行排序
    for(i=0; i<G.numVextexs-1; i++)         //生成树的边数为n-1条
    {
        for(j=i+1; j<G.numVextexs; j++)         //j从i+1开始，对于无向图，(vi,vj)具有相同的权重，
        {                                       //j=i+1是为了只考虑矩阵的上半部分，避免了重复。
            if(G.arc[i][j] <GRAPH_INFINITY)
            {
                edges[k].begin = i;                 
                edges[k].end = j;
                edges[k].weight = G.arc[i][j];
                k++;
            }
        }
    }
    Bubble_sort(edges,G);   

    for(i=0 ;i <G.numVextexs; i++)          //初始化数组
    {
        parent[i] = 0;
    }

    printf("打印最小生成树:\n");
    for(i=0; i<G.numEdges; i++)                 
    {
        n = Find(parent,edges[i].begin);
        m = Find(parent,edges[i].end);
        if(n != m)
        {
            parent[n] = m;

            printf("(%d,%d) %d\n",edges[i].begin, edges[i].end, edges[i].weight);
        }

    }

}

int main()
{
    MGraph G;
    CreateMGraph(&G);
    MiniSpanTree_Kruskal(G);
    return 0;
}