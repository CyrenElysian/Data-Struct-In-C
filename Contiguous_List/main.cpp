#include <stdlib.h>
#include <stdio.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW (-2)

typedef struct
{
    int *elem;
    int length;
}Sqlist;

int Createlist(Sqlist &l)
{
    l.elem=new int[MAXSIZE];
    if(!l.elem)
    {
        exit(OVERFLOW);
    }
    printf("请输入表的长度：");
    scanf("%d",&l.length);
    printf("输入%d个数：",l.length);
    for(int i=0;i<l.length;i++)
    {
        scanf("%d",&l.elem[i]);
    }
    return OK;
}

void Traverse(Sqlist l)
{
    printf("表中数据为：");
    for(int i=0;i<l.length;i++)
    {
        printf("%d ",l.elem[i]);
    }
    printf("\n");
}

int GetElem(Sqlist l,int i,int &e)//对e数值进行更改，用&
{
    if(i<1||i>l.length)
    {
        return ERROR;
    }
        e=l.elem[i-1];
        return OK;
}

int LocateElem(Sqlist l,int e)
{
    for(int i=0;i<l.length;i++)
    {
        if(l.elem[i]==e)
        {
            return i+1;
        }
    }
    return 0;
}

int ListInsert(Sqlist &l,int i,int e)
{
    if(i<1||i>l.length+1)//l.length+1表示在最后一个元素后，顺序表不允许两个元素之间有空
    {
        return ERROR;
    }
    if(l.length==MAXSIZE)
    {
        return ERROR;
    }
    for(int j=l.length-1;j>=i-1;j--)
    {
        l.elem[j+1]=l.elem[j];
    }
    l.elem[i-1]=e;
    l.length++;
    return OK;
}

int ListDelete(Sqlist &l,int i)
{
    if(i<1||i>l.length)
    {
        return ERROR;
    }
    for(int j=i;j<=l.length-1;j++)
    {
        l.elem[j-1]=l.elem[j];
    }
    l.length--;
    return OK;
}

//顺序有序表的合并
void Merge_Sqlist(Sqlist LA,Sqlist LB,Sqlist &LC)
{
    LC.length=LA.length+LB.length;
    LC.elem=new int[LC.length];
    int* pa=LA.elem;
    int* pb=LB.elem;
    int* pc=LC.elem;
    int* pa_last=LA.elem+LA.length-1;
    int* pb_last=LA.elem+LB.length-1;
    while(pa<=pa_last&&pb<=pb_last)//其中一个顺序表到达表尾停止
    {
        if(*pa<=*pb)
        {
            *pc=*pa;
            pa++;
            pc++;
        }
        else
        {
            *pc=*pb;
            pb++;
            pc++;
        }
    }
    while(pa<=pa_last)//如果表LB到达表尾
    {
        *pc=*pa;
        pa++;
        pc++;
    }
    while(pb<=pb_last)//如果表LA到达表尾
    {
        *pc=*pb;
        pb++;
        pc++;
    }
}

int main()
{
    Sqlist L;

    Createlist(L);
    Traverse(L);

    //printf("元素的位置：%d",LocateElem(L,3));
    //printf("\n");

    ListInsert(L,1,0);
    Traverse(L);

    ListDelete(L,1);
    Traverse(L);
    return 0;
}

