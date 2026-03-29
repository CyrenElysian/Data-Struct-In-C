#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next ;
}Node,*LinkList;

void InitList(LinkList &L)
{
    L=new Node;
    L->next=NULL;
}

void CreatList_h(LinkList &L,int n)
{
    L=new Node;
    L->next=NULL;
    printf("请输入%d个值：",n);
    for(int i=0;i<n;i++)
    {
        Node* p=new Node;
        scanf("%d",&p->data);
        p->next=L->next;
        L->next=p;
    }
}

void CreatList_r(LinkList &L,int n)
{
    L=new Node;
    L->next=NULL;
    Node* r;//尾结点
    r=L;
    printf("请输入%d个值：",n);
    for(int i=0;i<n;i++)
    {
        Node* p=new Node;
        scanf("%d",&p->data);
        p->next=NULL;
        r->next=p;//尾结点指向p
        r=p;//尾结点重置位置
    }
}

void Traverse(LinkList L)
{
    Node* p;
    p=L->next;
    printf("链表中的元素依次为：");
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

int Locate(LinkList L,int e)//链表中第一个与e相同的元素的位置
{
    Node* p;
    p=L->next;
    int i=1;//单链表查找元素只能顺着表找
    while(p&&p->data!=e)//循环结束条件：1.顺着表找完但没找到 或 2.找到了
    {
        p=p->next;//指针位置后置一位
        i++;//计数器加一
    }
    if(p)
    {
        return i;//找到，返回序号i
    }
    else
    {
        return 0;//未找到
    }
}

int GetElem(LinkList L,int i,int &e)//取第i个元素的值
{
    Node *p;
    p = L->next;
    if (i <= 0)
    {
        return 0;
    }
    int j = 1;//从首元结点开始计数
    while (p && j < i)//循环至p指向第i个结点或p指向空结点
    {
        p = p->next;
        j++;
    }
    if (p)
    {
        return e=p->data;
    }
    else
    {
        return 0;
    }
}

int ListInsert(LinkList &L,int i,int e)//在单链表的第i个位置插入值为e的新结点，头结点不算，首元结点为第一个位置
{
    Node* p;
    p=L;//从头结点开始找，p=L->next错误，此时l已指向首元结点
    if(i<=0)
    {
        return 0;
    }
    int j=0;//由于可以插入在首元结点之前，故从首元结点前一个位置开始计数
    while(p&&j<i-1)//循环至p指向第i个结点前一个的位置（即所需要插入的位置）或指向空结点
    {
        p=p->next;
        j++;
    }
    if(p)
    {
        Node *s = new Node;
        s->data = e;
        s->next = p->next;
        p->next = s;
        return 1;
    }
    else
    {
        return 0;
    }
}


int ListDelete(LinkList &L,int i)
{
    Node* p;
    p=L;//从头结点开始找，p=L->next错误，此时l已指向首元结点
    if(i<=0)
    {
        return 0;
    }
    int j=0;
    while(p&&j<i-1)//先用p找到第i-1个结点，再用q指向第i个结点，让p指向第i+1个结点后，删除q即删除了第i个结点
    {
     p=p->next;
     j++;
    }
    if(p)
    {
        Node* q;
        q=p->next;
        p->next=q->next;
        delete q;
        return 1;
    }
    else
    {
        return 0;
    }
}

//链式有序表的合并
void MergeList_linklist(LinkList &LA,LinkList &LB,LinkList &LC) {
    Node *pa = LA->next;
    Node *pb = LB->next;

    //以下两行代码不能交换位置
    LC = LA;//当两个指针变量之间进行赋值操作时，你实际上是在复制指针的值，即它们所指向的内存地址。这意味着两个指针变量将指向同一块内存地址。
    Node *pc = LC;
    //需要先更新 LC 指向 LA 的头结点，即初始化 LC 的头结点,然后 pc 指针才能指向正确的位置

    while (pa && pb)//直至一表为空
    {
        if (pa->data <= pb->data) {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }//穿针引线，在不开辟新内存的情况下，改变LA,LB两表的连接
    }
    if (pa)//将非空链表的剩余节点一次性插入到pc指结点之后
    {
        pc->next = pa;
    }
    else//如果la表已空，lb表还剩元素
    {
        pc->next=pb;
    }
    delete LB;//删除LB的头结点
}

void Mix(LinkList &la,LinkList &lb)//求交集,最终归并到la表，删除lb表
{
    Node* pa=la->next;
    Node* pb=lb->next;
    Node* pc=la;//******************************
    while(pa && pb)
    {
        if(pa->data==pb->data)
        {
            pc->next=pa;
            pa=pa->next;
            pc=pc->next;
            Node* temp=pb;
            pb=pb->next;
            delete temp;
        }
        else if(pa->data<pb->data)
        {
            Node* temp=pa;
            pa=pa->next;
            delete temp;
        }
        else
        {
            Node* temp=pb;
            pb=pb->next;
            delete temp;
        }
    }
    while(pa)//*****************
    {
        Node* temp=pa;
        pa=pa->next;
        delete temp;
    }
    while(pb)//******************
    {
        Node* temp=pb;
        pb=pb->next;
        delete temp;
    }
    delete lb;//**********************************
    pc->next=NULL;//*********************************
}

void Difference(LinkList &la,LinkList &lb,int &count)//求差集
{
    count =0;
    Node* pa=la->next;
    Node* pb=lb->next;
    Node* pre=la;//记录la表头，指向pa指针所指结点的前一结点
    //****************************
    while(pa && pb)
    {
        if (pa->data == pb->data)
        {
            pre->next = pa->next;//遇到两链表中相等的则舍去，修改pre指针，接上pa指针所指结点的下一结点
            //***************************
            Node *temp = pa;
            pa = pa->next;
            delete temp;
        }
        else if (pa->data > pb->data)
        {
            pb = pb->next;
        }
        else
        {
            pre = pa;//******************************
            pa = pa->next;
            count++;
        }
    }
    while(pa)//预防出现lb以遍历完，la表还剩元素的情况
    {
        count++;
        pa=pa->next;
    }
}

void inverse(LinkList &L)//************************************
{
    Node *p = L->next;
    L->next = NULL;
    while (p)
    {
        Node* q=p->next;//用于记录*p的后继结点，避免链表地址丢失
        //***********************
        p->next=L->next;
        L->next=p;
        p=q;
    }
}


















int main()
{
    LinkList l1,l2;

    CreatList_r(l1,5);
    CreatList_r(l2,5);
    Traverse(l1);
    Traverse(l2);

    LinkList l3 ;
    MergeList_linklist(l1,l2,l3);
    Traverse(l3);

    return 0;
}


