#include<stdio.h>
#include <stdlib.h>

#define ok 1
#define error 0
#define overflow -2
#define MAXSIZE 100



//顺序队列
typedef int elem;
typedef struct
{
    elem *base;
    int front;
    int rear;
}Queue;

int InitQueue(Queue &Q)
{
    Q.base=new elem[MAXSIZE];
    if(!Q.base)
    {
        exit (overflow);
    }
    Q.front=Q.rear=0;
    return ok;
}

int Queue_length(Queue Q)
{
    return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

int EnQueue(Queue &Q,elem e)
{
    if((Q.rear+1)%MAXSIZE==Q.front)//队满
    {
        return error;
    }
    else
    {
        Q.base[Q.rear]=e;
        Q.rear=(Q.rear+1)%MAXSIZE;//
        return ok;
    }
}

int DeQueue(Queue &Q,elem &e)
{
    if(Q.front==Q.rear)
    {
        return error;
    }
    e=Q.base[Q.front];
    Q.front=(Q.front+1)%MAXSIZE;//
    return ok;
}

elem Get_Head(Queue Q)
{
    if(Q.front!=Q.rear)
    {
        return Q.base[Q.front];
    }
}



//链队列
typedef struct Qnode
{
    elem data;
    struct Qnode* next;
}Qnode;
typedef struct
{
    Qnode* front;
    Qnode* rear;
}LinkQueue;//链队列需要指向Qnode型节点的头、尾指针,这里不需要*LinkQueue

int InitQueue_(LinkQueue &Q)
{
    Q.front=Q.rear=new Qnode;//开辟头结点
    Q.front->next=NULL;//头结点置空
    return ok;
}

int EnQueue_(LinkQueue &Q,elem e)
{
    Qnode* p=new Qnode;
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
        Qnode* p;//需要声明一个新结点p，
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

elem Get_Head_(LinkQueue Q)
{
    if(Q.front!=Q.rear)
    {
        return Q.front->next->data;
    }
}

typedef struct
{
    elem *base;
    int front;
    int rear;
    int tag;//当front=rear时，令tag=0队列为空，tag=1队列队列为满
}NewQueue;  //依然是循环队列

void InitQueue_New(NewQueue &Q)
{
    Q.base=new elem[MAXSIZE];
    Q.front=Q.rear=0;
    Q.tag=0;
}

void EnQueue_New(NewQueue &Q,elem e)
{
    if(Q.front==Q.rear && Q.tag==1)//*****************
    {
        printf("队列已满");
        exit(0);
    }
    else
    {
        Q.rear=(Q.rear+1)%MAXSIZE;//*******************
        Q.base[Q.rear]=e;//************
        Q.tag=1;//***************
    }
}

void DeQueue_New(NewQueue &Q,elem &e)
{
    if(Q.front==Q.rear && Q.tag==0)//*********
    {
        printf("队列为空");
        exit(0);
    }
    else
    {
        e=Q.base[Q.front];//***********
        Q.front=(Q.front+1)%MAXSIZE;//********************
        if(Q.front==Q.rear)
        {
            Q.tag=0;//***************
        }
    }
}

int main()
{
    Queue Q1;
    LinkQueue Q2;

    /*InitQueue(Q1);
    EnQueue(Q1,0);
    printf("%d\n", Get_Head(Q1));
    EnQueue(Q1,1);
    printf("%d\n", Get_Head(Q1));
    int a,b;
    DeQueue(Q1,a);
    printf("%d\n", Get_Head(Q1));
    DeQueue(Q1,b);
    printf("%d %d\n",a,b);*/

    InitQueue_(Q2);
    EnQueue_(Q2,0);
    printf("%d\n", Get_Head_(Q2));
    EnQueue_(Q2,1);
    printf("%d\n", Get_Head_(Q2));
    int c,d;
    DeQueue_(Q2,c);
    printf("%d\n", Get_Head_(Q2));
    DeQueue_(Q2,d);
    printf("%d %d",c,d);

    return 0;
}
