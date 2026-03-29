#ifndef BITREE_STACK_H
#define BITREE_STACK_H
#define ok 1
#define error 0

typedef int elem;

typedef struct BiTnode
{
    elem data;
    struct BiTnode* lchild;
    struct BiTnode* rchild;
}BiTnode,*BiTree;

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


int Push_(LinkStack &S, BiTnode* e)
{
    StackNode* p;
    p=new StackNode;
    p->data=e->data;
    p->next=S;//p结点入栈
    S=p;//将p结点设为栈顶
    return ok;
}

int Pop_(LinkStack &S,BiTnode* e)
{
    if(S==NULL)
    {
        return error;
    }
    else
    {
        e->data=S->data;//s即为栈顶结点
        StackNode* p=new StackNode ;//开辟新结点p存储栈顶元素的信息，以备释放
        p=S;
        S=S->next;
        delete p;
        return ok;
    }
}

int Get_top_(LinkStack S)
{
    if(S)
    {
        return S->data;
    }
}



#endif //BITREE_STACK_H
