#include<stdio.h>
#define max_int 32767

typedef int KeyType;

//线性表的查找
typedef struct
{
    KeyType key;

    //这里还可以定义其他数项
}ElemType;

typedef struct
{
    ElemType R[100];
    int length;
}List;//顺序表

void Create_List(List &l)
{
    int key;
    int i=1;
    l.length=0;
    printf("请输入待查找的序列：\n");
    while(scanf("%d", &key) && key >= 0)
    {
        l.R[i].key = key;
        i++;
        l.length++;
    }
}

int Search_Seq(List l,KeyType key)
{
    l.R[0].key=key;//设置"哨”
    int i;
    for(i=l.length;l.R[i].key!=key;i--);
    return i;//i为查找元素的序号，若i=0,未找到
}

void Search_Seq_Print(List l)
{
    int key;
    printf("请输入需要查找元素的关键字：");
    while(scanf("%d", &key) && key!=max_int)
    {
        if (Search_Seq(l, key) > 0)
        {
            printf("%d的位置：%d\n", key, Search_Seq(l, key));
        }
        else
        {
            printf("没有这个元素\n");
        }
        printf("请输入需要查找元素的关键字：");
    }
}

int Search_Bi(List l,KeyType key)//折半查找要求顺序表是有序的
{
    int low = 1;
    int high = l.length;
    while (low <= high) //注意条件
    {
        int mid = (low + high) / 2;
        if(key==l.R[mid].key)
        {
            return mid;
        }
        else if(key<l.R[mid].key)
        {
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }
    }
    return 0;//如经上述循环过程未找到，返回0
}

void Search_Bi_Print(List l)
{
    int key;
    printf("请输入需要查找元素的关键字：");
    while(scanf("%d", &key) && key!=max_int)
    {
        if (Search_Seq(l, key) > 0)
        {
            printf("%d的位置：%d\n", key, Search_Bi(l, key));
        }
        else
        {
            printf("没有这个元素\n");
        }
        printf("请输入需要查找元素的关键字：");
    }
}

int BinSearch(int r[],int low,int high,int key)//折半查找的递归算法
{
    int mid;
    if(low>high) return 0;
    else
    {
        mid=(low+high)/2;
        if(key<r[mid]) return BinSearch(r,low,mid-1,key);
        else if(key>r[mid]) return BinSearch(r,mid+1,high,key);
        else return mid;
    }
}


//二叉排序树
//二叉排序树的性质:
//1.若它的左子树不为空，则左子树上所有的结点均小于它的根节点值
//2.若它的右子树不为空，则右子树上所有的结点均大于它的根节点值
//3.它的左右子树均为二叉排序树
typedef struct BSTNode
{
    ElemType data;
    struct BSTNode* lchild;
    struct BSTNode* rchild;
}BSTNode,*BSTree;

BSTree SearchBST(BSTree T,KeyType key)//二叉排序树的查找
{
    if(!T || key==T->data.key)//递归结束条件：
                              //1.如果结点为空，返回空指针，查找失败
                              //2.查找成功
    {
        return T;
    }
    else if(key<T->data.key)
    {
        return SearchBST(T->lchild,key);
    }
    else
    {
        return SearchBST(T->rchild,key);
    }
}

void SearchBST_Print(BSTree T)
{
    int key;
    printf("请输入需要查找元素的关键字：");
    while(scanf("%d", &key) && key!=max_int)
    {
        if (SearchBST(T, key))
        {
            printf("%d的位置：%d\n", key, SearchBST(T, key)->data.key);
        }
        else
        {
            printf("没有这个元素\n");
        }
        printf("请输入需要查找元素的关键字：");
    }
}

void InsertBST(BSTree &T,ElemType e)//二叉排序树的插入
{
    if(!T)//如果树为空，直接插入，左右孩子置空即可
    {
        BSTNode* S=new BSTNode ;
        S->data=e;
        S->lchild=S->rchild= NULL;
        T=S;
    }
    else if(e.key<T->data.key)
    {
        InsertBST(T->lchild,e);
    }
    else if(e.key>T->data.key)
    {
        InsertBST(T->rchild,e);
    }
}

void CreateBST(BSTree &T)
{
    T=NULL;//初始化为空
    ElemType e;
    printf("亲输入待查找序列：\n");
    scanf("%d",&e.key);

    //这里还可以输入元素e的其他信息

    while(e.key!=32767)
    {
        InsertBST(T,e);
        scanf("%d",&e.key);
    }
}

void InOrderTraverse(BSTree T)//中序遍历
{
    if(T)
    {
        InOrderTraverse(T->lchild);
        printf("%d ",T->data.key);
        InOrderTraverse(T->rchild);
    }
}

void DeleteBST(BSTree &T,KeyType key)//二叉排序树的删除
{
    BSTNode* p=T;//初始指针p初始指向树根结点
    BSTNode* f=NULL;//指针f指向指针p所指向结点的双亲

    //删除的三种情况，假设*p是*f的左孩子(右孩子同理)
    //1.*p是叶子结点：只需要修改双亲结点的指针为空
    //2.*p只有左子树或只有右子树：此时只要让子树成为双亲结点的左子树即可
    //3.*p既有左子树，也有右子树：中序遍历二叉排序树，令*p的直接前驱为*s(*s结点的关键字为*p左子树中最大的，比*p右子树的所有关键字小)
    //用*s代替*p,然后删除原来的*s

    while(p)//本循环是为了定位删除的结点
            //如果结点不为空
    {
        if(p->data.key==key)//如果根结点就是要删除的结点，则退出循环
        {
            break;
        }
        f=p;//保存双亲结点，因为接下来p就要指向p的左孩子或右孩子了
        if(p->data.key>key)//如果结点的关键字大于要删除的关键字，则在左子树寻找
        {
            p=p->lchild;
        }
        else//反之，则在右子树寻找
        {
            p=p->rchild;
        }
    }
    if(!p)//若定位得到的结点为空，说明不存在要删除的结点，直接返回
    {
        return;
    }

    //此时指针p指向要删除的结点

    BSTNode* q=p;//初始化指针q，使其指向p
                 //在情况1,2中，指针q是用来记录*p的地址的
                 //在情况3中，*q是*s的双亲结点

    if(p->lchild && p->rchild)//如果要删除结点的左右子树均不为空
    {
        BSTNode* s=p->lchild;//*s是为了记录中序遍历后*p的直接前驱，故初始化为*p的左孩子
        while(s->rchild)//如果*s还有右孩子，也就是说*p左子树未遍历完
        {
            q=s;//记录，*q是*s的双亲结点
            s=s->rchild;//指针s指向s的右孩子，继续遍历，直到s成为*p的直接前驱
        }
        p->data=s->data;//用结点*s替换*p
        if(q!=p)//如果*p不是*q结点，也就是*p不是*s的双亲结点
        {
            q->rchild=s->lchild;//更新*q结点的右孩子，将原来*s结点的左孩子接上*q结点
        }
        else
        {
            q->lchild=s->lchild;//如果*p就是*s的双亲，因为*s等会要删除，所有将*s的左孩子接在双亲上
        }
        delete s;//删除s结点
        return;//情况3，删除完成，返回
    }

    else if(!p->rchild)//如果*p右子树为空，也就是左子树非空或叶子结点
    {
        p=p->lchild;//指针p指向用*p的左子树
    }
    else if(!p->lchild)//如果*p左子树为空，也就是右子树非空或叶子结点
    {
        p=p->rchild;//指针p指向*p的右子树
    }

    //现在p指向要删除结点的左孩子或右孩子

    if(!f)//如果*p的双亲为空，也就是说*p为根结点，二叉排序树只有两个结点
    {
        T=p;//将p的左子树或右子树作为根结点即可
    }
    else if(q==f->lchild)//如果要删除的结点是其双亲的左孩子
    {
        f->lchild=p;//将初始*p结点的孩子接上
    }
    else//如果要删除的结点是其双亲的右孩子
    {
        f->rchild=p;//将初始*p结点的孩子接上
    }
    delete q;//删除q结点，即删除初始的*p,即我们要删除的结点
}

int main()
{
    BSTree T;
    CreateBST(T);
    printf("二叉树中序遍历：");
    InOrderTraverse(T);
    printf("\n");
    SearchBST_Print(T);
    ElemType e1,e2,e3;
    e1.key=17;
    e2.key=7;
    e3.key=-1;
    InsertBST(T,e1);
    InsertBST(T,e2);
    InsertBST(T,e3);
    printf("二叉树中序遍历：");
    InOrderTraverse(T);
    printf("\n");
    DeleteBST(T,4);
    DeleteBST(T,9);
    printf("二叉树中序遍历：");
    InOrderTraverse(T);
    return 0;
}


















