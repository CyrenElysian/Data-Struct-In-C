#include<stdio.h>

#define ok 1
#define error 0
#define true 1
#define false 0

//图的邻接矩阵存储形式
#define max_int 32767
#define max 20
typedef int vertex;
typedef int arc;

//图的邻接矩阵表示
typedef struct
{
    vertex vertex[max];//存储顶点
                       //为方便理解，我们规定vertex[0]不使用
    arc arc[max][max];//邻接矩阵用二维数组表示
                      //同样矩阵的第0行和第0列不予适用
    int vertex_num;
    int arc_num;
}AMGraph;

int LocateVertex(AMGraph G,int v)
{
    for(int i=1;i<=G.vertex_num;i++)
    {
        if(G.vertex[i]==v)
        {
            return i;
        }
    }
    return -1;
}

//邻接矩阵创建无向网
void Create_IndirectNet(AMGraph &G)
{
    printf("请输入顶点数：");
    scanf("%d",&G.vertex_num);
    printf("请输入边数：");
    scanf("%d",&G.arc_num);
    for(int i=0;i<=G.vertex_num;i++)
    {
        G.vertex[i]=i;
    }
    for(int i=0;i<=G.vertex_num;i++)
    {
        for(int j=0;j<=G.vertex_num;j++)
        {
            G.arc[i][j]=max_int;//初始边权值为无限大
        }
    }
    for(int k=1;k<=G.arc_num;k++)
    {
        int row,column;
        int weight;
        int v1,v2;//一条边依附的两个顶点
        printf("请输入第%d条边的v1数据：",k);
        scanf("%d",&v1);
        printf("请输入第%d条边的v2数据：",k);
        scanf("%d",&v2);
        printf("请输如权值：");
        scanf("%d",&weight);
        printf("\n");
        row= LocateVertex(G,v1);
        column= LocateVertex(G,v2);
        G.arc[row][column]=G.arc[column][row]=weight;
    }
}

//邻接矩阵创建有向网

//图的邻接表表示
typedef struct ArcNode
{
    int adj_vertex;//边的头顶点
    struct ArcNode* next;//指向下一条边的指针
    int weight;
}ArcNode;

typedef struct VertexNode
{
    vertex data;//代表顶点序号
    ArcNode* first_arc;//指向第一个以该顶点为尾的边的头
}VertexNode,AdjList[max];//定义一个新类型 AdjList,是一个包含 max 个 VertexNode 结构体的数组类型

typedef struct
{
    AdjList vertex;//一个数组，存储图中所有顶点的邻接表
                   //为方便理解，这里我们规定vertex[0]不使用
    int vertex_num;
    int arc_num;
}ALGraph;

int LocateVertex_(ALGraph G,int v)
{
    //遍历所有顶点，找到与v相等的顶点的索引
    for (int i = 1; i <= G.vertex_num; i++)
    {
        if (G.vertex[i].data == v)
        {
            return i; //返回顶点v的索引
        }
    }
    return -1; //如果没有找到，返回-1
}

//采用邻接表创建无向图（无向图无权值）
void Create_IndirectGraph(ALGraph &G)
{
    printf("请输入顶点数：");
    scanf("%d",&G.vertex_num);
    printf("请输入边数：");
    scanf("%d",&G.arc_num);
    for(int i=1;i<=G.vertex_num;i++)
    {
        G.vertex[i].data=i;
        G.vertex[i].first_arc=NULL;//初始化表头结点的指针为空
    }
    for(int k=1;k<=G.arc_num;k++)
    {
        int i,j;
        int v1,v2;//一条边依附的两个顶点
        printf("请输入第%d条边的v1数据：",k);
        scanf("%d",&v1);
        printf("请输入第%d条边的v2数据：",k);
        scanf("%d",&v2);
        printf("\n");
        i= LocateVertex_(G,v1);
        j= LocateVertex_(G,v2);

        //头插
        ArcNode* p1=new ArcNode ;
        p1->adj_vertex=j;//将 p1 的 adj_vertex 设置为 j，表示这条边连接到顶点 vertex[j]
                         //具体来说，p1这个边结点代表从顶点vertex[i]出发指向顶点vertex[j]的连接
                         //因此我们将p1插入顶点vertex[i]的边链表
        p1->next=G.vertex[i].first_arc;
        G.vertex[i].first_arc=p1;
        //生成对称的边结点*p2
        ArcNode* p2=new ArcNode ;
        p2->adj_vertex=i;//将 p1 的 adj_vertex 设置为 i，表示这条边连接到顶点 vertxt[j]
        p2->next=G.vertex[j].first_arc;
        G.vertex[j].first_arc=p2;

    }
}

//邻接表创建有向网
void Create_DirectNet(ALGraph &G)
{
    printf("请输入顶点数");
    scanf("%d",&G.vertex_num);
    printf("请输入边数：");
    scanf("%d",&G.arc_num);
    for(int i=1;i<=G.vertex_num;i++)
    {
        G.vertex[i].data=i;
        G.vertex[i].first_arc=NULL;//初始化表头结点的指针为空
    }
    for(int k=1;k<=G.arc_num;k++)
    {
        int i, j;
        int weight;
        int v1, v2;//一条边依附的两个顶点
        printf("请输入第%d边的始顶点v1数据：",k);
        scanf("%d", &v1);
        printf("请输入第%d边的终顶点v2数据：",k);
        scanf("%d", &v2);
        i = LocateVertex_(G, v1);
        j = LocateVertex_(G, v2);
        printf("请输如入权值：");
        scanf("%d", &weight);
        ArcNode *p1 = new ArcNode;
        p1->weight = weight;
        p1->adj_vertex = j;//将 p1 的 adj_vertex 设置为 j，表示这条边连接到顶点 vertex[j]
        //具体来说，p1这个边结点代表从顶点vertex[i]出发指向顶点vertex[j]的连接
        //因此我们将p1插入顶点vertex[i]的边链表
        p1->next = G.vertex[i].first_arc;
        G.vertex[i].first_arc = p1;
    }
}

//深度优先搜索 Depth First Search
int visited[max]={false};//访问标志数组，其初值为 false，一旦某个顶点被访问，则其相应的分量置为 true

void DFS_AL(ALGraph G,int v)//采用邻接表表示图的深度优先搜索遍历 v是遍历的初始顶点
{
    printf("%d ",G.vertex[v].data);
    visited[v]= true;
    ArcNode* p=G.vertex[v].first_arc;
    while(p)
    {
        int w=p->adj_vertex;
        if(!visited[w])
        {
            DFS_AL(G,w);
        }
        p=p->next;
    }
}

//广度优先搜索 Breadth First Search

//链队列
typedef int elem;

typedef struct QNode
{
    elem data;
    struct QNode* next;
}QNode;

typedef struct
{
    QNode* front;
    QNode* rear;
}LinkQueue;//链队列需要指向qnode型节点的头、尾指针,这里不需要*LinkQueue

int InitQueue_(LinkQueue &Q)
{
    Q.front=Q.rear=new QNode;//开辟头结点
    Q.front->next=NULL;//头结点置空
    return ok;
}

int EnQueue_(LinkQueue &Q,elem e)
{
    QNode* p=new QNode;
    p->data=e;
    p->next=NULL;
    Q.rear->next=p;//将p插入表中
    Q.rear=p;//尾节点指向p
    return ok;
}

int DeQueue_(LinkQueue &Q,elem &e)
{
    if(Q.front==Q.rear)
    {
        return error;
    }
    else
    {
        QNode* p;//需要声明一个新结点p，
        p=Q.front->next;
        e=p->data;
        Q.front->next=p->next;//Q.front->next=Q.front->next->next是否可以?;
        if(Q.rear==p)
        {
            Q.rear=Q.front;//如果p指向的是链表中最后一个结点，队尾指针应更改指向头结点
        }
        delete p;
        return ok;
    }
}

void BFS_AL(ALGraph G,int v)
{
    printf("%d", G.vertex[v].data);
    visited[v] = true;

    LinkQueue Q;
    InitQueue_(Q);
    EnQueue_(Q, v);
    int u;
    while (Q.front != Q.rear)//队列非空
    {
        DeQueue_(Q, u);
        ArcNode *p = G.vertex[u].first_arc;
        while (p) {
            int w = p->adj_vertex;
            if (!visited[w]) {
                printf(" %d", w);
                visited[w] = true;
                EnQueue_(Q, w);
            }
            p = p->next;
        }
    }
}

//构造最小生成树
//Prim算法
//构造辅助数组，用来记录顶点集 U(已纳入最小生成树的顶点集）到 V-U(V为所有顶点的集和，两者差集为还未纳入最小生成树的顶点的集合)的权值最小的边
typedef struct
{
    vertex adj_vertex;//最小边在U中的顶点
    arc lowcost;//最小边的权值
}low_arc;

int Min(low_arc low_arc[], int vertex_num)
{
    int min_index;
    arc min_weight = max_int;
    for (int i = 1; i <= vertex_num; i++)
    {
        if (low_arc[i].lowcost < min_weight && low_arc[i].lowcost>0)
        {
            min_index = i;
            min_weight = low_arc[i].lowcost;
        }
    }
    return min_index;
}

void MiniSpanTree_Prim(AMGraph G,vertex u)
{
    low_arc low_arc[max];//同样规定，low_arc[0]不使用

    int k= LocateVertex(G,u);//k为顶点u的下标
    low_arc[k].lowcost=0;//u到自己的权值记为0，也因为u到自己的权值最小，也就相当于把u放进了集合U
    for(int j=1;j<=G.vertex_num;j++)//对V-{u}的每一个顶点初始化
    {
        if(j!=k)
        {
            low_arc[j]={u,G.arc[k][j]};//初始化数组
        }
    }

    int sum=0;//求权值之和

    for(int i=1;i<G.vertex_num;i++)
    {
        k=Min(low_arc,G.vertex_num);//i=1时，k为u到V-{u}权值最小的顶点的下标
        int u1=low_arc[k].adj_vertex;//i=1时，low_[k].adj_vertex全等于u
        int v1=G.vertex[k];
        printf("最小生成树的边为：\n");
        printf("(%d,%d）,权值：%d\n",u1,v1,low_arc[k].lowcost);

        sum=sum+low_arc[k].lowcost;

        low_arc[k].lowcost=0;//将新的顶点放入集合U

        for (int j = 1; j <= G.vertex_num; j++)
        {
            if(G.arc[k][j]<low_arc[j].lowcost)//对low.arc[].lowcost进行重置，在加入下标为k的新顶点后，
                                              //如果顶点下标为k和j之间的权值arc[k][j] 小于 之前集合U中的顶点到下标为j的顶点的权值low_arc[j].lowcost
                                              //更新
            {
                low_arc[j]={G.vertex[k],G.arc[k][j]};
            }
        }
    }
    printf("最小生成树的权值之和为：%d",sum);
}

//Kruskal算法
typedef struct
{
    vertex head;
    vertex tail;
    arc lowcost;
}Edge;

int vertex_set[max];//顶点组
                    //规定vertex_set[0]不予使用

void sort(Edge edge[],int arc_num)
{
    for(int i=0;i<arc_num-1;i++)
    {
        int min=i;//引入最小值的序号，这样每次外循环一次后只要交换一次
        for(int j=i+1;j<=arc_num-1;j++)
        {
            if(edge[min].lowcost>edge[j].lowcost)
            {
                min=j;
            }
        }
        if(i!=min)
        {
            Edge temp;
            temp=edge[i];
            edge[i]=edge[min];
            edge[min]=temp;
        }
    }
}

void MiniSpanTree_Kruskal(AMGraph G)
{
    int k=0;
    Edge Edge[G.arc_num];
    for(int i=1;i<=G.vertex_num;i++)
    {
        for(int j=i+1;j<=G.vertex_num;j++)
        {
            if (G.arc[i][j]<max_int)
            {
                Edge[k].head=i;
                Edge[k].tail=j;
                Edge[k].lowcost=G.arc[i][j];
                k++;
            }
        }
    }
    for(int i=1;i<=G.vertex_num;i++)
    {
        vertex_set[i]=i;//初始每个顶点自成一个连通分量
    }
    int sum=0;
    printf("最小生成树的边为：\n");
    for(int i=0;i<G.arc_num;i++)
    {
        int v1= LocateVertex(G,Edge[i].head);
        int v2= LocateVertex(G,Edge[i].tail);//获取边的头和尾
        int vs1=vertex_set[v1];
        int vs2=vertex_set[v2];//获取边的头和尾所在的连通分量
        if(vs1!=vs2)
        {
            printf("(%d,%d),权值：%d\n",Edge[i].head,Edge[i].tail,Edge[i].lowcost);
            sum=sum+Edge[i].lowcost;
            for(int j=1;j<=G.vertex_num;j++)
            {
                if(vertex_set[j]==vs2)
                {
                    vertex_set[j]=vs1;
                }
            }
        }
    }
    printf("最小生成树权值之和为：%d\n",sum);
}

//最短路径
//迪杰斯特拉算法，求解某个源点到其余各顶点的最短路径
void ShortestPath_Dijkstra(AMGraph G,int v0)
{
    int S[G.vertex_num+1];//用于记录源点V0到Vi是否已被确定为最短路径长度
                        //true表示确定，false表示尚未确定
    int Path[G.vertex_num+1];//用于记录源点V0到Vi的当前最短路径上，Vi的直接前驱结点序号
                           //其初值为，如果V0到Vi有边，则Path[i]置为V0，否则置为-1
    int D[G.vertex_num+1];//用于记录源点到Vi的当前最短路径长度
                        //其初值为，如果从V0到Vi有边，则D[i]为该边的权值，否则记为无穷大
    //为理解方便，规定以上数组0号位置空置
    int v;
    for(v=1;v<=G.vertex_num;v++)
    {
        S[v]= false;
        D[v]=G.arc[v0][v];
        if(D[v]<max_int)//如果如果V0到Vi有边，则Path[i]置为V0，否则置为-1
        {
            Path[v]=v0;
        }
        else
        {
            Path[v]=-1;
        }
    }
    S[v0]=true;//将V0点纳入集合S(集合S是已已被确定为最短路径长度的顶点的集合)
    D[v0]=0;//初始化完成

    for(int i=1;i<G.vertex_num;i++)
    {
        for(int j=1;j<G.vertex_num;j++)
        {
            int min=max_int;
            if(!S[j] && D[j]<min)
            {
                v=j;
                min=D[j];
            }
        }
        //本循环是找出一个最短路径还未被确认的点，要求该点对应数组D[]中最小的值

        S[v]= true;//将该点(记为v点)加入集合S
                   //v点为中转点，每次大循环的中转点都会更新

        for(int k=1;k<=G.vertex_num;k++)
        {
            if(!S[k] && (D[v]+G.arc[v][k]<D[k]))//如果Vk尚不在集合S中，且借由v点中转后，V0到Vk的距离缩短，更新
            {
                D[k]=D[v]+G.arc[v][k];//更新距离
                Path[k]=v;//更新前驱结点
                //跟新数组Path[]的原因：在回溯过程中重建具体的最短路径，没有它，只能从数组D[]获取最短路径长度，无法中直接得到路径信息
            }
        }
    }
}

//弗洛伊德算法，求解每一对顶点之间的最短距离
void ShortesrPath_Floyd(AMGraph G)
{
    int Path[G.vertex_num+1][G.vertex_num+1];//Path[i][j],用于记录点Vi到点Vj的路径中，Vj前一顶点的序号
    int D[G.vertex_num+1][G.vertex_num+1];//D[i][j]，用于记录点Vi和Vj之间的最短路径长度

    for(int i=1;i<=G.vertex_num;i++)
    {
        for(int j=1;j<=G.vertex_num;j++)
        {
            D[i][j]=G.arc[i][j];//初始化
            if(D[i][j]<max_int && i!=j)//这里试试看能不能把i!=j去掉?????????????????????????????????????????????????/
            {
                Path[i][j]=i;//如果i和j之间有边，则将j的前驱值置为i
            }
            else
            {
                Path[i][j]=-1;
            }
        }
    }
    for(int k=1;k<=G.vertex_num;k++)
    {
        for(int i=1;i<=G.vertex_num;i++)
        {
            for(int j=1;j<=G.vertex_num;j++)
            {
                if(D[i][k]+D[k][j]<D[i][j])//依次
                //在Vi和Vj之间加入中转点Vk1,得到(Vi,Vk1),(Vk1,Vj)后，
                //比较D[i][k1]+D[k1][j]与D[i][j],取较小值作为新的D[i][j]

                //在Vi和Vj之间加入中转点Vk2,得到(Vi,Vk1,Vk2),(Vk2,Vk1,Vj)
                //比较D[i][k2]+D[k2][j]与D[i][j](此时D[i][j]已为上次比较后更新的值),取较小值作为新的D[i][j]
                //以此类推
                {
                    D[i][j]=D[i][k]+D[k][j];
                    Path[i][j]=Path[k][j];//将j的前驱更新为k
                }
            }
        }
    }
}

//拓扑排序
//AOV-网(Activity On Vertex Network)：用顶点表示活动，用弧表示活动间的优先关系的有向图
//拓扑排序：将AOV-网中所有顶点排成一个线性序列，该序列满足：若在AOV-网中从顶点Vi到Vj有一条路径，则在线性序列中的顶点Vi必定在顶点Vj之前
//拓扑排序的步骤：
//1.在有向图中选一个无前驱的顶点输出它
//2.在图中删除该顶点和所有以他以它为尾的弧
//3.重复1和2
//4.若最后输出的顶点小于有向图中的顶点数，则说明有向图中存在环，否则输出的顶点序列即位一个拓扑序列

//拓扑排序算法
void FindIndegree(ALGraph G,int indegree[])//数组indegree[]用来存放各顶点的入度，没有前驱的顶点就是入度为0的顶点
                                           //同样规顶数组第0为不使用
{
    for(int i=1;i<=G.vertex_num;i++)
    {
        ArcNode* p=G.vertex[i].first_arc;
        while(p && p->weight<max_int)
        {
            indegree[p->adj_vertex]++;
            p=p->next;
        }
    }
}

//链栈
typedef struct StackNode
{
    int data;
    struct StackNode* next;
}StackNode,*LinkStack;

int Create_stack_(LinkStack &S)
{
    S= NULL;//链栈不设置头结点
    return ok;
}

int Push_(LinkStack &S,int e)
{
    StackNode* p;
    p=new StackNode;
    p->data=e;
    p->next=S;//p结点入栈
    S=p;//将p结点设为栈顶
    return ok;
}

int Pop_(LinkStack &S,int &e)
{
    if(S==NULL)
    {
        return error;
    }
    else
    {
        e=S->data;//s即为栈顶结点
        StackNode* p=new StackNode ;//开辟新结点p存储栈顶元素的信息，以备释放
        p=S;
        S=S->next;
        delete p;
        return ok;
    }
}

int TopologicalSort(ALGraph G,int topo[])//数组topo[]用来记录拓扑排序的顶点序号
{
    int indegree[max];
    FindIndegree(G,indegree);
    LinkStack S;
    Create_stack_(S);
    int i;
    for(i=1;i<G.vertex_num;i++)
    {
        if(indegree[i]==0)//入度为0的顶点进栈
        {
            Push_(S,i);
        }
    }
    int m=0;
    while(S)//如果栈非空
    {
        Pop_(S,i);
        topo[m]=i;//出栈后按顺序存放在数组topo[]中
        m++;
        ArcNode* p=G.vertex[i].first_arc;
        while(p)//若结点不为空
        {
            indegree[p->adj_vertex]--;//所有以Vi为尾的顶点入度减1
            if(indegree[p->adj_vertex]==0)//如果减为0，入栈
            {
                Push_(S,p->adj_vertex);
            }
            p=p->next;//指针p指向p的下一个结点
        }
    }
    if(m<G.vertex_num)
    {
        return error;//顶点没有全部输出
    }
    else
    {
        return ok;
    }
}

//关键路径
//AOE-网(Activity On Edge Network)：即用边表示活动的网，通常AOE-网用来估算工程的完成时间
//AOE-网是带权的有向无环图，其中顶点表示实践，弧表示活动，弧的权表示活动持续时间
//网中只有一个入度为0的点，称作源点；只有一个出度为0的点，称作汇点
//在AOE-网中，一条路径各弧上的权值之和称为各路径的带权路径长度，若要估算整项工程完成的最短时间，
//就是要找到一条从源点到汇点的带权路径长度 最长 的路径，称为关键路径(理解：一个工程完成的最短时间，取决于其中需要花费时间最长的一个事件分支)

//定义4个描述量：
//1.ve(i)：事件vi最早的发生时间
//进入vi的每一个活动都结束，vi才可以发生，故ve(i)是从源点到vi的最长路径长度
//显然顶点事件v1的最早发生时间为0，如果vk和vi之间有弧，则ve(i)=max{ve(k)+w(k,i)}，w为权值,2<=i<=n

//2.vl(i)：事件vi最迟发生时间
//vi的发生不得延误vi后继事件的最迟发生时间，即不得迟于其后继世界vk的最迟发生时间减去w(i,k)
//求出ve(i)后，可根据逆拓扑顺序从汇点开始向源点递推，求出vl(i)
//显然汇点事件的最迟发生时间vl(n)=ve(n)，如果vi和vk之间有边，则vl(i)=min{vl(k)-w(i,k)}，1<=i<=n-1
//(理解：汇点事件n的最早发生时间为ve(n),即关键活动全部完成需要ve(n),此时刚刚卡线完成工程，故汇点事件最迟不能超过ve(n))

//3.e(i)：活动ai=<vj,vk>的最早开始时间
//只有事件vj发生了，活动ai才能开始，故e(i)=ve(j)

//4.l(i)：活动ai=<vj,vk>的最晚开始时间
//活动ai的开始时间需要保证不延误事件vk的最迟发生时间，故l(i)=vl(k)-w(j,k)

//关键路径的求解过程
//1.对图中顶点进行排序，在排序过程中按拓扑排序序列求出每个事件的最早发生时间ve()
//2.按逆拓扑序列求出每个事件的最迟发生时间vl()
//3.求出每个活动ai的最早开始时间e(i)
//4.求出每个活动ai的最晚开始时间l(i)
//5.找出e(i)=l(i)的活动ai，即关键活动。由关键活动形成的从源点到汇点的每一条路径就是关键路径，关键路径可能不止一条

//关键路径算法
int CriticalPath(ALGraph G)
{
    int ve[max];//规顶第0位不使用
    int vl[max];//规顶第0位不使用
    int topo[max];
    if(TopologicalSort(G,topo)==error)//如果无法拓扑排序，则网中存在环，直接返回
    {
        return error;
    }

    for(int i=1;i<=G.vertex_num;i++)//最早发生时间从前往后推
    {
        ve[i]=0;//初始化所有事件的最早发生时间为0
    }
    for(int i=0;i<=G.vertex_num;i++)
    {
        int k=topo[i];//按照拓扑排序获取顶点序号
        ArcNode* p=G.vertex[k].first_arc;
        while(p)
        {
            if(ve[p->adj_vertex]<ve[k]+p->weight)//对于以Vk为尾的弧，假设头是Vj，如果它的头的最早发生时间小于尾+活动权值：ve[k]+weight(k,j),更新ve[j]
            {
                ve[p->adj_vertex] = ve[k] + p->weight;
            }
            p=p->next;
        }
    }

    for(int i=1;i<=G.vertex_num;i++)
    {
        vl[i]=ve[G.vertex_num];//初始所有事件的最迟发生时间为ve(n)
    }
    for(int i=G.vertex_num;i>=1;i--)//最迟发生时间从后往前推
    {
        int k=topo[i];//按照 逆 拓扑排序获取顶点序号
        ArcNode* p=G.vertex[k].first_arc;
        while(p)
        {
            if(vl[k]>vl[p->adj_vertex]-p->weight)//对于以Vk为尾的弧，假设头是Vj，如果它的尾的最迟发生时间大于头-活动权值：vl[j]-weight(k,j)，更新vl[j]
            {
                vl[k]=vl[p->adj_vertex]-p->weight;
            }
            p=p->next;
        }
    }

    for(int i=1;i<=G.vertex_num;i++)
    {
        ArcNode* p=G.vertex[i].first_arc;
        while(p)
        {
            int earlist=ve[i];//活动的最早开始时间
            int latest=vl[p->adj_vertex]-p->weight;//活动的最迟开始时间
            if(earlist==latest)//相等时相当于活动“不可怠慢”
            {
                printf("<%d,%d> ",G.vertex[i].data,G.vertex[p->adj_vertex].data);
            }
            p=p->next;
        }
    }
    return ok;
}


int main()
{

    return 0;
}









