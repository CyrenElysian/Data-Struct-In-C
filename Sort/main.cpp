#include<stdio.h>

#define MAXSIZE 20

typedef int KeyType;

typedef struct
{
    KeyType key;//关键字，一般是整型

    //此处还可以定义其他数据项

}Redtype;//包括关键字即其对应信息的结构体

typedef struct
{
    Redtype r[MAXSIZE+1];//r[0]闲置或用作哨兵单元
    int length;//这里的长度指需要排序的数的个数，即最后一个数在数组中的下标
}Sqlist;





//直接插入排序
void InsertSort(Sqlist &l)
{
    for(int i=2;i<=l.length;i++)
    {
        if(l.r[i].key<l.r[i-1].key)
        {
            l.r[0]=l.r[i];//将待插入的的记录暂存到监视哨中
                          //前i-1是有序数列，查找第i项在这个有序数列中的位置
            int j;
            for(j=i-1;l.r[0].key<l.r[j].key;j--)
            {
                l.r[j+1]=l.r[j];//每比较一次，若条件满足，第 j 项向后移动 1 位
            }
            l.r[j+1]=l.r[0];//此时第i项大于第j项，故第i应当置于第j+1项的位置
        }
    }
}

//折半插入排序
void BInsertSort(Sqlist &l)//由于前i-1项是有序数列，所以在前i-1项找第i项相应位置是可以采用折半查找法
{
    for(int i=2;i<=l.length;i++)
    {
        l.r[0]=l.r[i];
        int low=1;
        int high=i-1;
        while(low<=high)//直至 low>high 结束循环，此时 l.r[high+1] 即是应插入的位置（可举例子证明）
        {
            int mid=(low+high)/2;
            if(l.r[0].key<l.r[mid].key)
            {
                high=mid-1;
            }
            else
            {
                low=mid+1;
            }
        }
        for(int j=i-1;j>=high+1;j--)//第 high+1 位到第 i-1 位向后移动一位
        {
            l.r[j+1]=l.r[j];
        }
        l.r[high+1]=l.r[0];
    }
}

//希尔排序
void ShellInsert(Sqlist &l,int distance)
{
    for(int i=distance+1;i<=l.length;i++)
    {
        if(l.r[i].key<l.r[i-distance].key)//每相邻两组元素的在 距离=distant 情况下，对应元素进行直接插入排序
        {
            l.r[0]=l.r[i];
            int j;
            for(j=i-distance;j>0&&l.r[0].key<l.r[j].key;j=j-distance)//这里由于比较的跨度（distance）较大，可能直接跨过哨兵
                                                                     //故要设置检查 j>0
            {
                l.r[j+distance]=l.r[j];//每比较一次，若条件满足，则第 j 项要向后移动 distance
            }
            l.r[j+distance]=l.r[0];
        }
    }
}

void ShellSort(Sqlist &l,int distance[],int t)//distance[]中每一项是每一个距离 distance ,t表示数组元素数量，即distance的数量
                                              //distance[]中的元素互质，依次递减，且最后一个元素等于1
                                              //当distance=1时，实际上做的是直接插入排序
{
    for(int k=0;k<t;k++)
    {
        ShellInsert(l,distance[k]);
    }
}

//冒泡排序
void BubbleSort(Sqlist &l)
{
    int flag=1;//用来标记某一趟排序元素是否发生交换，若为0则表示排序已完成，可以终止循环

    int len=l.length;

    while(l.length>1 && flag==1)
    {
        flag=0;//先把flag置为0，若以下排序元素间发生交换，flag再变为1
        for(int i=1;i<=len-1;i++)//注意条件是 等于 ,这是因为元素是从序号1开始存储的，一直到序号len，不会存在越界问题
        {
            if (l.r[i].key > l.r[i + 1].key)
            {
                flag = 1;
                Redtype temp;
                temp = l.r[i];
                l.r[i] = l.r[i + 1];
                l.r[i + 1] = temp;
            }
        }
        len--;//每次 for循环结束 后(每经历一趟冒泡排序)都会使得本次循环中最大的值下沉到底部，即正确的位置
              //以后其他的元素就不用和这些“最大值”比较了(注意这句 len-- 的位置是在整个for循环后)
    }
}

//快速排序
int Partition(Sqlist &l,int low,int high)//Partition 分区,该函数返回的枢轴的正确位置
                                          //初始时low=1，high=l.length
{
    l.r[0]=l.r[low];//将顺序表的第一个记录l.r[1]作为数轴记录
    KeyType pivotkey=l.r[low].key;//pivot 支点
    while(low<high)
    {
        while(low<high && l.r[high].key>=pivotkey)//这里的 low<high 不能省略，
                                                  //因为一旦low=high说明本趟排序已完成，本趟排序不要再进行任何操作
                                                  //第一个while（）里的low<high是作为一趟排序里出现交换操作后，
                                                  //进行low和high大小的检查，判断是否要继续改趟排序
        {
            high--;//从表的高端找起，遇到关键字大于等于枢轴的，不交换，使high数值减一
        }
        l.r[low]=l.r[high];//直至找到关键字比枢轴小的，交换位置
        while(low<high && l.r[low].key<=pivotkey)
        {
            low++;//从表的低端找起，遇到关键字小于等于枢轴的，不交换，使low数值加一
        }
        l.r[high]=l.r[low];//直至找到关键字比枢轴大的，交换位置
                           //此时high所指的是上一个关键字比枢轴小的关键字的位置
    }
    l.r[low]=l.r[0];//此时high=low，二者所指位置即是枢轴记录所应在的位置，它左边的值均小于它，右边的值均大于它
    return low;//此时high=low，返回枢轴位置
}

void QSort(Sqlist &l,int low,int high)//初始时low=1，high=l.length
{
    if(low<high) //表长大于1
    {
        int pivot_location = Partition(l, low, high);
        QSort(l, low, pivot_location - 1);//左子表递归排序
        QSort(l, pivot_location + 1, high);//右子表递归排序
    }
}

void QuickSort(Sqlist &l)//给快速排序提供一个更简单的接口，不需要在知名low和high的值
{
    QSort(l,1,l.length);
}

//选择排序
void SelectSort(Sqlist &l)
{
    for(int i=1;i<l.length;i++)
    {
        int min=i;//引入最小值的序号，这样每次外循环一次后只要交换一次
        for(int j=i+1;j<=l.length;j++)
        {
            if(l.r[min].key>l.r[j].key)
            {
                min=j;
            }
        }
        if(i!=min)
        {
            Redtype temp;
            temp=l.r[i];
            l.r[i]=l.r[min];
            l.r[min]=temp;
        }
    }
}

//堆排序
//堆实质上是满足如下性质的完全二叉树：树中所有非终端结点的值均不大于（不小于）其左右孩子结点的值
//堆顶元素（或完全二叉树的根）为序列中n个元素的最大值或最小值，分别称之为大根堆和小根堆

//堆排序步骤
//1.输出根，并以最后一个元素代替
//2.比较新的根与左右孩子key的大小，并与其中较大者交换，再与左右孩子中key较大的交换，直到进行到叶子结点

void HeapAdjust(Sqlist &l,int s,int m)//调整堆
//对于完全二叉树，若序号为i的结点有左孩子，其左孩子序号为2i,若其还有右孩子，则右孩子序号为2i+1
//假设r[s+1……m]已经成堆，即r[s+1]>=r[2(s+1)],r[s+1]>=r[2(s+1)+1](或者均<=）
//该算法将r[s……m]调整为以r[s]为根的大根堆
{
    Redtype rc=l.r[s];
    for(int j=2*s;j<=m;j=j*2)//此处循环实际上在执行堆排序第二步
    {
        if(j<m && l.r[j].key<l.r[j+1].key)//找到r[2s]和r[2s+1]中key的较大值
        {
            j++;
        }
        if(rc.key>=l.r[j].key)//如果r[s].key已经大于两者中最大值，说明r[s……m]已成堆，不必再做任何操作
        {
            break;
        }
        l.r[s]=l.r[j];
        s=j;//依次让r[s]为左右孩子中key值较大的结点
    }
    l.r[s]=rc;//r[s]已到叶子结点，给叶子结点赋予原根结点r[s]的数据
}

void Create(Sqlist &l)//建初堆(大根堆）
//显然，只有一个结点的树必是堆
//在完全二叉树中，所有序号大于n/2（向下取整）的结点均为叶子结点，因此以这些结点为根的子树已是堆
//故只需要将序号小于n/2(向下取整）的结点为根的子树都调整为堆即可
{
    int n=l.length;//变量n记录表的长度，即数据总量（因为不包括l.r[0])
    for(int i=n/2;i>0;i--)
    {
        HeapAdjust(l,i,n);//从后往前调整，直到整个成堆
    }
}

void HeapSort(Sqlist &l)//堆排序
{
    Create(l);
    for(int i=l.length;i>1;i--)
    {
        Redtype temp=l.r[1];//交换根与最后一个结点
        l.r[1]=l.r[i];
        l.r[i]=temp;

        HeapAdjust(l,1,i-1);//m的值减一，相当于把原根结点输出了
    }
}

//归并排序
//假设初始序列含有n个记录，则可将其看成n个有序的子序列，每个子序列长度为1，
//然后两两归并，得到n/2（向上取整）个长度为2或1的子序列，
//再两两归并，直到得到一个长度为n的有序序列
void Merge(Redtype R[],Redtype T[],int low,int middle,int high)//将相邻有序表R[low……middle]和R[middle+1……high]归并成T[low……high]
{
    int i=low;
    int j=middle+1;
    int k=low;//T[]中起始位置
    while(i<=middle&&j<=high)
    {
        if(R[i].key<=R[j].key)
        {
            T[k++]=R[i++];
        }
        else
        {
            T[k++]=R[j++];
        }
    }
    while(i<=middle)//若第二个有序表数据已转移完成
    {
        T[k++]=R[i++];
    }
    while(j<=high)//若第一个有序表数据已转移完成
    {
        T[k++]=R[j++];
    }
}

void Msort(Redtype R[],Redtype T[],int low,int high)
{
    Redtype S[MAXSIZE];//过渡数组
    if(low==high)//序列长度为1时
    {
        T[low]=S[low];
    }
    else
    {
        int middle=(low+high)/2;//将当前序列一分为二
        Msort(R,S,low,middle);
        Msort(R,S,middle+1,high);
        Merge(S,T,low,middle,high);
    }
}

void MergeSort(Sqlist &l)
{
    Msort(l.r,l.r,1,l.length);
}


//基数排序(使用静态链表)
#define MaxNum_Key 8 //关键字项数最大值（即最多有多少关键字）
#define RADIX 10 //基数，一般比较的是十进制数，故定义为10
#define Max_Space 10000

typedef struct
{
    KeyType data;

    KeyType keys[MaxNum_Key];//关键字数组

    //这里还可以定义其他数据项

    int next;//next变量用来存储指向静态链表下一个“结点”的索引，可以视作为“指针”

    //基数排序算法采用静态链表
    //静态链表使用数组来表示链表中的元素，即通过数组索引来模拟指针，不需要为每个结点分配额外的内存来存储指针
}SLCell;

typedef struct
{
    SLCell r[Max_Space];//静态链表的可用空间，设置r[0]为头结点
                        //对于每一个 r[i]（其中 i 的范围是从 0 到 Max_Space-1），节点里包含以下内容:
                        //1:data:数据值
                        //2:keys[MaxNum_Key]：一个数组，用于存储数据data的关键字。每个 SLCell 结点可以存储最多 MaxNum_Key（在这个代码中是8）个关键字
                        //3:next：一个整型变量，用于存储指向静态链表中下一个节点的索引

    int key_num;//记录的当前数据的关键字个数
                //例如：data=209(三位数），关键字为2,0,9，key_num=3
                //注：因为采用的是最低位优先，所以keys[0]=9,key[1]=0,keys[2]=2

    int recnum;//静态链表当前长度 record number
               //这个变量用于记录静态链表当前的长度，即已使用的结点数量。在静态链表的实现中，recnum表示目前已经分配和使用的SLCell结构体的数量
}SLList;

typedef int ArrType[RADIX];//定义一个整型数组类型，大小为基数（RADIX=10）



void Distribute(SLCell *r,int i,ArrType &front,ArrType &rear)//分配
//i表示第i个关键字
//front[k]表示基数为k的队列的头指针，rear[k]则是尾指针
//本算法按第i个关键字key[i]建立RADIX（10）个子表(队列),使每个子表中记录的key[i]相同
{
    int j;
    for(j=0;j<RADIX;j++)
    {
        front[j]=0;//初始化每个队列为空（front[j]=0代表队列为空)
    }
    for(int p=r[0].next;p;p=r[p].next)
    {
        j=r[p].keys[i];//把r[p]的第i个关键字映射给j
        if(!front[j])//如果front[j]=0,即队列为空
        {
            front[j]=p;//把当前元素的索引p,传给front[j]
        }
        else
        {
            r[rear[j]].next=p;//如果队列为非空，那么说明rear[j]已有一个值，该值在数值上等于上一个进入该队列的元素（设为pre）在数组r[]中的索引
                              //通过索引找的pre，并把pre的next更改为当前要进入队列的元素在原数组r[]中的索引
        }
        rear[j]=p;//无论队列是否为空，都将队列尾指针记为当前进入队列元素在原数组r[]中的索引
    }
}

void Collect(SLCell* r,int i,ArrType front,ArrType rear)//收集
//本算法按keys[i]将各个队列连接成一个队列
{
    int j;
    for(j=0;!front[j];j++)//当！front[j]=0，即front[j]!=0,找到第一个非空队列
    {
        r[0].next=front[j];
    }
    int end=rear[j];//end存储该队列队尾元素在数组r[]中的索引
    while(j<RADIX)
    {
        for(++j;j<RADIX;j++)
        {
            if(front[j])
            {
                r[end].next=front[j];//连接两个两个队列
                end=rear[j];//更新end，即更新新队列的队尾索引
            }
        }
    }
    r[end].next=0;//连接完所有队列后，end指向最后一个非空队列的队尾索引，将其修改为0
}

void RadixSort(SLList &l)//排序
//对静态链表l进行基数排序，使得l成为按照关键自小到大的有序静态链表
{
    ArrType front,rear;
    for(int i=0;i<l.key_num;i++)//按 最低位优先 依次对各关键字进行分配和收集
    {
        Distribute(l.r,i,front,rear);
        Collect(l.r,i,front,rear);
    }
}

void CreateList(SLList &l)
{
    int data;
    int i=1,j;
    printf("请输入数据的关键字位数:");//注：key_num为关键字位数最多的，其余位数不够的会用0进行替代
    scanf("%d",&l.key_num);
    printf("请输入数据：");
    scanf("%d",&data);

    while(data!=0)
    {
        l.r[i].data=data;
        for(j=0;j<l.key_num;j++)
        {
            l.r[i].keys[j]=data%10;
            data=data/10;
        }
        i++;
        scanf("%d",&data);
    }
    l.recnum=i-1;//静态链表的长度(不包括头结点）

    for(int k=0;k<l.recnum;k++)
    {
        l.r[k].next=k+1;//对l.r[k].next先进行赋值，1<=k<=l.recnum-1,recnum为表长（不包括头结点的长度）
    }
    l.r[l.recnum].next=0;//结尾置为0
}

void PrintfList(SLList l)
{
    for(int p=l.r[0].next;p;p=l.r[p].next)
    {
        printf("%d ",l.r[p].data);
    }
}

//基数排序(使用动态链表)
//结点
typedef struct Node
{
    int data;
    struct Node* next;
}Node;
//队列
typedef struct Queue
{
    Node* front;
    Node* rear;
}Queue;

//队列数组，存放10个队列，因为比较的一般是十进制数(关键字为0~9)，queue[k]中的元素关键字即为k
Queue queue[10];
//除数  用于获取数据元素某位的关键字，因为是从低位到高位比较关键字，故初始值设为1
int divisior = 1;

void initQueue(Queue &Q)
{
    Q.front=Q.rear=new Node ;
    Q.front->next=NULL;
}


void push(Queue &Q, int e)
{
    Node* p = new Node;
    if (p != NULL)
    {
        p->data = e;
        p->next = NULL;
        Q.rear->next = p;
        Q.rear = p;
    }
}


void clear(Queue &Q)
{
    Q.front->next = NULL;
    Q.rear = Q.front;//由于没有开辟新空间，不需要delete
}


int maxBit(Queue &Q)
{
    Node* p = Q.front->next;
    int maxData = p->data;
    while(p != NULL)//寻找序列中最大的元素
    {
        if (maxData < p->data)
        {
            maxData = p->data;
        }
        p = p->next;
    }
    int b = 0;
    while (maxData > 0)//计算最大元素的位数
    {
        maxData /= 10;
        b++;
    }
    return b;
}


int getKey(Node* q)//用于从个位至最高位依次获取关键字
{
    int k = 0;
    k = (q->data / divisior) % 10;
    return k;
}


void distributeRadix(Queue &Q)
{
    //初始化十个带头结点的队列
    for (int i = 0; i < 10; i++)
    {
        initQueue(queue[i]);
    }

    Node* p = Q.front->next;
    while (p != NULL)
    {
        int k = getKey(p);
        queue[k].rear->next = p;
        queue[k].rear = p;
        p = p->next;
        queue[k].rear->next = NULL;
    }
    clear(Q);//每次把总队列中的元素重新分配到各个子队列后，总队列重置
}


void collectRadix(Queue &Q)
{
    //寻找非空队列并添加到queue链队中
    for (int index=0; index < 10; index++)
    {
        Node* q = queue[index].front->next;
        while (q != NULL)
        {
            Q.rear->next = q;
            Q.rear = q;
            q = q->next;
            Q.rear->next = NULL;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        clear(queue[i]);//每次将子队列中的元素依次按队列所代表的关键字大小依次存入总队列后，子队列重置
    }

    divisior *= 10;//除数乘10，用于获取下一个关键字
}


void radix(Queue &Q)
{
    int b = maxBit(Q);//b是链队列中最大元素的位数，
    for (int i = 1; i <= b; i++)//从低位到高位，按关键分配，再归入总队列，以此重复，位数不够的元素，缺少的位数可视作0(如：007,017,177)
    {
        distributeRadix(Q);
        collectRadix(Q);
    }
}


void print(Queue Q)
{
    Node* p = Q.front->next;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}


void Create_Queue(Queue &Q,int arr[],int length)
{
    initQueue(Q);
    for (int i = 0; i < length; i++)
    {
        push(Q, arr[i]);
    }
}


#include <time.h>
#include <cstdlib>
int main()
{

    Queue Q;

    int arr[10] ;

    srand((unsigned) time (NULL));//确保每次生成不同的随机数
    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % 100;
    }

    Create_Queue(Q,arr,sizeof (arr) /sizeof (int));

    printf("排序前序列：\n");
    print(Q);

    radix(Q);

    printf("排序后序列：\n");
    print(Q);


    return 0;
}