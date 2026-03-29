#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include<string.h>

#define MAXSIZE 100
#define ok 1
#define error 0
#define overflow (-2)

//二叉树顺序存储
typedef int elem;
typedef elem SqBiTree[MAXSIZE];//定义了一个新类型 SqBiTree，它是一个具有 MAXSIZE 个 elem 类型元素的数组
SqBiTree bt;                   //声明变量，bt为SqbiTree类型，即一个具有MAXSIZE个elem类型元素的数组
                               //对于一般二叉树，应将其每个结点与完全二叉树上的结点相对照，按顺序填入数组中，不存在的结点以“0”表示

//二叉树的二叉链表表示
//此定义在头文件"stack.h"中亦有记载
/*typedef struct BiTnode
{
    elem data;
    struct BiTnode* lchild;
    struct BiTnode* rchild;
}BiTnode,*BiTree;*/

//先序创建二叉树       （如何层序创建二叉树）？？？？？？？？？？？？？？
void CreateBiTree(BiTree &T)
{
    int index;
    scanf("%d",&index);
    if(index == -1)//在先序输入值（index）时，空指针所指向的结点需要输入值-1
    {
        T=NULL;
    }
    else
    {
        T=new BiTnode;
        T->data=index;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

//二叉树的中序遍历算法
void InOrderTraverse(BiTree T)
{
    if(T)
    {
        InOrderTraverse(T->lchild);
        printf("%d ",T->data);
        InOrderTraverse(T->rchild);
    }
}

//二叉树的先序遍历算法
void PreOrderTraverse(BiTree T)
{
    if(T)
    {
        printf("%d ",T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

//二叉树的后序遍历算法
void PostOrderTraverse(BiTree T)
{
    if (T)
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%d ", T->data);
    }
}

//二叉树的中序遍历（非递归算法）   ？？？？？？
void InOrderTraverse_(BiTree T)
{
    LinkStack S;
    Create_stack_(S);
    BiTnode *p=T;
    BiTnode* Q=new BiTnode ;
    while(p||S)
    {
        if(p)//依次遍历左子树，直至叶子结点
        {
            Push_(S,p);
            p=p->lchild;
        }
        else
        {
            Pop_(S,Q);
            printf("%d",Q->data);
            p=Q->rchild;
        }
    }
}

//二叉树的层序遍历算法
//链队列
typedef struct QNode
{
    BiTnode* data;
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

int EnQueue_(LinkQueue &Q,BiTnode* e)
{
    QNode* p=new QNode;
    p->data=e;
    p->next=NULL;
    Q.rear->next=p;//将p插入表中
    Q.rear=p;//尾节点指向p
    return ok;
}

int DeQueue_(LinkQueue &Q,BiTnode* &e)
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
        Q.front->next=p->next;
        if(Q.rear==p)
        {
            Q.rear=Q.front;//如果p指向的是链表中最后一个结点，队尾指针应更改指向头结点
        }
        delete p;
        return ok;
    }
}

void FloorTraverse(BiTree T)
//3 9 0 0 20 15 0 0 7 0 0
//1 2 4 0 0 5 6 0 0 7 0 0 3 0 8 9 0 0 0
//7 6 4 8 0 3 0 0 0 0 5 2 0 0 1 0 9 0 0
{
    LinkQueue Q;
    InitQueue_(Q);
    if (T)
    {
        EnQueue_(Q, T);
    }
    BiTnode* e;//用于记录每次出队的结点，方便输出结点的值
    while (Q.front->next)//若队列非空（队列有头结点）
    {
        int level=0;
        for(QNode* temp=Q.front->next;temp;temp=temp->next)
        {
            level++;//记录当前队列有多少结点
        }
        for(int i=0;i<level;i++)
        {
            DeQueue_(Q, e);
            printf("%d ", e->data);
            if (e->lchild)
            {
                EnQueue_(Q, e->lchild);
            }
            if (e->rchild)
            {
                EnQueue_(Q, e->rchild);
            }
        }
        printf("\n");//把上一层的结点全部出队后，换行
    }
}

//计算二叉树深度
int Depth(BiTree T)
{
    int m,n;//分别用于计左、右子树的深度
    if(T==NULL)
    {
        return 0;
    }
    else
    {
        m= Depth(T->lchild);//每有一个结点不为空，m的值加1
        n= Depth(T->rchild);//二叉树深度=MAX{左子树，右子树}+1
        if(m>n)
        {
            return m+1;
        }
        else
        {
            return n+1;
        }
    }
}

//统计二叉树中结点的个数
int NodeCount(BiTree T)
{
    if(T==NULL)
    {
        return 0;
    }
    else
    {
        return NodeCount(T->lchild)+ NodeCount(T->rchild)+1;//加上根结点
    }
}

//以结点p为根的子树中序线索化
//二叉树的二叉线索存储表示
typedef struct BiThreadNode
{
    elem data;
    struct BiThreadNode* lchild;
    struct BiThreadNode* rchild;
    int LTag,RTag;//左标签和右标签，结点无左（右）子树时，置LTag(RTag)值为1,lchild（rchild)指向其前驱（后继）
}BiThreadNode,*BiThreadTree;

BiThreadNode* pre ;

void In_Thread(BiThreadTree p)
{
    pre->rchild=NULL;//初始化pre的右孩子为空
    if(p)
    {
        In_Thread(p->lchild);//线索化左子树
        if(!p->lchild)//p的左孩子为空
        {
            p->LTag=1;//标记为1，左孩子指针指向pre(前驱）
            p->lchild=pre;
        }
        else
        {
            p->LTag=0;
        }
        if(!pre->rchild)//pre为p前驱，pre的右孩子为空，指向后继p（初始化pre的右孩子为空的原因）
        {
            pre->RTag=1;
            pre->rchild=p;
        }
        else
        {
            pre->RTag = 0;
        }
        pre=p;//p现在作为前驱结点
        In_Thread(p->rchild);
    }
}

//构造哈夫曼树
typedef struct
{
    int weight;
    int parent,lchild,rchild;//双亲，孩子的下标
}HTnode,*HuffmanTree;

void Select(HuffmanTree HT, int n, int &s1,int &s2) //*s1,*s2表示权值最小的结点的序号，
                                                    //n表示目前需要考虑序号是1~n的权值,即前n个(0号单元不存储数据）
{
    int min1=INT_MAX;//用于存储最小权重值，INT_MAX是int型的最大值
                     //不能如此定义：int min1 = HT[1].weight 因为当HT[1].weight为某次循环的 min1或 min2 时，
                     //其parent被置为非0，后续不再参与比较大小
                     //用宏定义的INT_MAX可避免此种情况
    int min2=INT_MAX;//用于存储第二小权重值
                     //同理不能定义：int min2 = HT[1].weight;
    for(int i = 1; i <= n; i++)// 寻找两个未被选择的最小权重节点
    {
        if (HT[i].parent == 0)//未被选择的节点
        {
            if (HT[i].weight < min1)
            {
                min2 = min1;//如果发现比最小权重值还小的权值，用原最小权重值覆盖原第二小权重值 
                s2 = s1;//同样，覆盖序号
                min1 = HT[i].weight;
                s1 = i;
                continue;
            }
            else if (HT[i].weight < min2)
            {
                min2 = HT[i].weight;
                s2 = i;
            }
        }
    }
}

void Create_HuffmanTree(HuffmanTree &HT,int n)//n为叶子结点数量(即需要存储的数据数量，哈夫曼树中数据都存储在叶子结点中)
                                             //HT[i].weight,i=1~n,依次存储这些数据的权值
                                             //哈夫曼树没有度为1的结点，深度为n，因次总结点数m=2n-1
{
    if(n<=1)
    {
        return ;
    }
    int m=2*n-1;//m为哈夫曼树中总结点数
    HT=new HTnode[m+1];//0号单元不存数据，共有m个结点，故需分配m+1个单元，记HT[2n-1]为根节点
    for(int i=1;i<=m;i++)
    {
        HT[i].parent=0;//双亲域标记为0，表示该节点还未使用
        HT[i].lchild=0;//左右孩子标记为0，表示目前没有左右孩子
        HT[i].rchild=0;
    }
    for(int i=1;i<=n;i++)//输入给出的n个结点的权值
    {
        scanf("%d",&HT[i].weight);
    }
    for(int i=n+1;i<=2*n-1;i++)//从给出的n个数据开始选，每次选两个组合，并产生一个新结点
                               //所以每进行一次 Select() 会使结点总数增加1，
                               //哈夫曼树共2n-1个结点，故需要进行n-1次循环
    {
        int s1;
        int s2;
        Select(HT,i-1,s1,s2);//最开始只要考虑前n个序号的权值，
                                       //最后一步需要考虑前2n-2个结点，生成最后最后一个结点（即根结点），
                                       //到此哈夫曼树中共2n-1个结点，构建完成
        HT[s1].parent=i;//新结点记为n+1,n+2,……,2n-2,2n-1(根结点)，
        HT[s2].parent=i;//s1,s2的parent不再是0，表示已经使用，后不再考虑
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
}

//根据哈夫曼树求哈夫曼编码
typedef char **HuffmanCode; //这行代码的作用是为类型 char **（指向字符指针的指针）定义一个新的类型名 HuffmanCode。
                            //定义之后，可以使用 HuffmanCode 来声明变量，而不需要每次都写 char **。
                            //char * 表示一个指向字符的指针，可以理解为指向一个字符串。
                            //char ** 表示一个指向字符指针的指针，即指向一个字符串数组，每个元素都是一个 char * 类型，代表一个字符串。

//各字符的哈夫曼编码存储在由HuffmanCode定义的动态分配的数组HC中，
//为了实现方便，数组的0号单元不使用，从1号单元开始使用，所以数组HC的大小为n+1，即编码表HC包括n+1行。

//但因为每个受符编码的长度事先不能确定，所以不能预先为每个字符分配大小合适的存储空间。
//为不浪费存储空间，动态分配一个长度为n（字符编码长度一定小于n)的一维数组cd，用来临时放当前正在求解的第i(1≤i≤n）个字符的编码，
//当第i个字符的编码求解完毕后，根据数组cd的字符串长度分配HC[i]的空间，然后将数组cd中的编码复制到HC[i]中。

//因为求解编码时是从哈夫曼树的叶子出发，向上回溯至根结点，
//故将编码向数组cd存放的顺序也是从后向前的，即每个字符的第1个编码存放在cd[n-2]中（cd[n-1]存放字符串结束标志\0'），第2个编码存放在cd[n-3]中，以此类推



void Creat_HuffmanCode(HuffmanTree HT,HuffmanCode &HC,int n)//n个字符
{
    HC=new char*[n+1];//分配了一个大小为 n+1 的 char* 类型指针数组。
                      //这个数组的每个元素都是一个 char* 类型的指针，可以指向一个字符数组（字符串）。
    char* cd;
    cd=new char[n];//分配数组空间
    cd[n-1]='\0';//不用"\0",双引号表示字符串，单引号用于表示单个字符 '\0' 是转义字符
    for(int i=1;i<=n;i++)
    {
        int start=n-1;//初始位于cd[]的最后位置
        int c=i;//c 用于记录从叶子结点向上回溯至根结点所经过的结点下标
        int f=HT[i].parent;//因为构建哈夫曼树时，编号为1~n的结点为所给出的数据，故从1~n依次给他们编码
                           //f 用于记录结点c的双亲结点的序号
        while(f!=0)//从叶子结点开始回溯，直至根节点
                   //在哈夫曼树中，由于其余结点都被 Select() 调用过，故只有根结点的双亲的值依然是0
        {
            start--;
            if(HT[f].lchild==c)//如果序号为c的结点是双亲的左孩子，那么记编码为0，反之记为1
            {
                cd[start]='0';
            }
            else if(HT[f].rchild==c)
            {
                cd[start]='1';
            }
        }
        HC[i]=new char[n-start];//cd[]分配了n个char类型空间，但是cd[start]前面的空间均没用，前面有start个空的空间
                                //故给第i个字符的编码，即HC的第i个字符串数组分配n-start个char类型的空间
        strcpy(HC[i],&cd[start]);//取cd[start]对应值的地址，&cd[start] 是一个指针，指向 cd 数组中从 start 索引位置开始的子字符串。
                                             //strcpy(HC[i], &cd[start]) 将从 cd[start] 开始的字符串（包括结束的空字符 \0）复制到 HC[i] 指向的内存位置。
        //strcpy(char *ptr, const char *ptr),
        //const char *ptr;
        //定义一个指向字符常量的指针，这里，ptr是一个指向 char* 类型的常量，所以不能用ptr来修改所指向的内容，换句话说，*ptr的值为const，不能修改。
        //但是ptr的声明 并不意味着 它指向的值实际上就是一个常量，而只是意味着对ptr而言，这个值是常量。
        //可以直接通过str变量来修改str的值，但是确不能通过ptr指针来修改。
    }
    delete cd;//释放cd数组空间
}



int main()
{
    return 0;
}