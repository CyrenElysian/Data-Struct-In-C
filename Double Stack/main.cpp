#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int top[2],bot[2];//栈顶和栈底指针
    int *V;//栈数组
    int m;//栈最大可容纳的元素个数
}DoubleStack;
//将两个栈存放在一个数组空间V[m]中，栈底分别处于数组的两端，
//当0号栈的栈顶指针top[0]=-1时该栈为空，当1号栈的栈顶指针top[1]=m时该栈为空。
//两个栈均从两向中间填充

void Initialize(DoubleStack &S)//初始化栈为空
{
    S.top[0]=-1;
    S.top[1]=S.m;
}

void Push(DoubleStack &S,int i,int e)//i为栈号(0或1)
{
    if(i<0 || i>1)
    {
        printf("栈号输入错误\n");
        exit(0);
    }
    if(S.top[1]-S.top[0]==1)//******************
    {
        printf("栈已满\n");
        exit(0);
    }
    if(i==0)
    {
        S.top[0]++;//****************
        S.V[S.top[0]]=e;//*************
        return;//**************
    }
    else if(i==1)
    {
        S.top[1]--;//*********
        S.V[S.top[1]]=e;//**********
        return;//*********
    }
}

void Pop(DoubleStack &S,int i)
{
    if(i<0 || i>1)
    {
        printf("栈号输入错误\n");
        exit(0);
    }
    if(i==0)
    {
        if(S.top[0]==-1)//0号栈空//****************
        {
            printf("%d号栈空\n",i);
            return;
        }
        else
        {
            printf("%d\n",S.V[S.top[0]]);
            S.top[0]--;//***********
        }
    }
    else if(i==1)
    {
        if(S.top[1]==S.m)//1号栈空//****************
        {
            printf("%d号栈空\n",i);
            return;
        }
        else
        {
            printf("%d\n",S.V[S.top[1]]);
            S.top[1]++;//**********
        }
    }
}

int isEmpty(DoubleStack S)
{
    if(S.top[0]==-1 && S.top[1]==S.m)
    {
        printf("栈空\n");
        return 1;
    }
    else
    {
        printf("栈非空\n");
        return 0;
    }
}

















