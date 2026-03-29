#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAXSIZE 100
#define ok 1
#define error 0
#define overflow (-2)

typedef char elem;

//顺序栈
typedef struct
{
    elem* base;
    elem* top;
    int StackSize;
}Stack;

int Create_stack(Stack &S)
{
    S.base =new elem [MAXSIZE];
    if(!S.base)
    {
        exit (overflow);
    }
    S.top=S.base;
    S.StackSize=MAXSIZE;
    return ok;
}

int Push(Stack &S,elem e)
{
    if(S.top-S.base==S.StackSize)//栈满
    {
        return error;
    }
    else
    {
        *S.top=e;
        S.top++;
        return ok;
    }
}

int Pop(Stack &S,elem &e)
{
    if(S.top==S.base)//栈空
    {
        return error;
    }
    else
    {
       S.top--;
       e=*S.top;
       return ok;
    }
}

elem Get_top(Stack S)
{
    if(S.top!=S.base)
    {
        return *(S.top-1);
    }
}

int IsHuiwen(char str[])//顺序栈方法，只需让一半的字符入栈
{
    Stack S;
    Create_stack(S);
    int length=strlen(str);//****************************
    for(int i=0;i<length/2;i++)//************
    {
        Push(S, str[i]);
    }
    int i=length/2;//字符串长度如果是偶数，从str[]的 length/2 位置开始比较，(第一个字母位置记为0)直到数组最后一个字符
                   //如果是奇数，从length/2+1 位置开始比较
    if(length%2!=0)//***************
    {
        i++;
    }
    for(i;i<length;i++)
    {
        char temp ;
        Pop(S, temp);
        if (temp != str[i])
        {
            printf("%s不是回文字符串\n", str);
            return 0;//**************
        }
    }
    printf("%s是回文字符串\n",str);
    return 1;
}

//链栈
typedef struct StackNode
{
    elem data;
    struct StackNode* next;
}StackNode,*LinkStack;

int Create_stack_(LinkStack &S)
{
    S= NULL;//链栈不设置头结点
    return ok;
}

int Push_(LinkStack &S,elem e)
{
    StackNode* p;
    p=new StackNode;
    p->data=e;
    p->next=S;//p结点入栈
    S=p;//将p结点设为栈顶
    return ok;
}

int Pop_(LinkStack &S,elem &e)
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

int Get_top_(LinkStack S)
{
    if(S)
    {
        return S->data;
    }
}

int IsHuiwen_(char str[])//链栈方法，由于链栈没有记录栈长度的变量，只能全部入栈
{
    LinkStack S;

    for(int i=0;str[i]!='\0';i++)
    {
        Push_(S, str[i]);
    }

    int flag=1;
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i] == Get_top_(S))
        {
            elem temp=Pop_(S,temp);
        }
        else
        {
            flag=0;
            break;
        }
    }

    if(flag==1)
    {
        printf("%s是回文字符串\n",str);
        return 1;
    }
    else
    {
        printf("%s不是回文字符串\n",str);
        return 0;
    }
}

int isPalindrome(char *str,int start,int end)//回文字符串递归方法
{
    if(start>=end)
    {
        return 1;
    }
    if(str[start]!=str[end])
    {
        return 0;
    }
    return isPalindrome(str,++start,--end);
}

int main()
{
    char str[MAXSIZE]={0};
    printf("请输入字符:");
    scanf("%s",str);
    IsHuiwen(str);
    return 0;
}