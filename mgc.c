/*
实验环境：C/C++
一、目的和要求
分区管理是应用较广泛的一种存储管理技术。本实验要求用一种结构化高级语言构造分区描述器，
编制动态分区分配算法和回收算法模拟程序，并讨论不同分配算法的特点。
二、实验内容
1、编写：First Fit Algorithm
2、编写：Best Fit Algorithm
3、编写：空闲区回收算法
三、提示和说明
（一）主程序 
1、定义分区描述器node，包括 3个元素：
（1）adr--分区首地址
（2）size--分区大小
（3）next--指向下一个分区的指针
2、定义 3个指向node结构的指针变量：
（1）head1--空闲区队列首指针
（2）back1--指向释放区node结构的指针
（3）assign--指向申请的内存分区node结构的指针
3、定义 1个整形变量：
free--用户申请存储区的大小（由用户键入）
（二）过程
1、定义check过程，用于检查指定的释放块（由用户键入）的合法性
2、定义assignment1过程，实现First Fit Algorithm
3、定义assignment2过程，实现Best Fit Algorithm
4、定义acceptment1过程，实现First Fit Algorithm的回收算法
5、定义acceptment2过程，实现Best Fit Algorithm的回收算法
6、定义print过程，打印空闲区队列
（三）执行
程序首先申请一整块空闲区，其首址为0，大小为32767；然后，提示用户使用哪种分配算法，
再提示是分配还是回收；分配时要求输入申请区的大小，回收时要求输入释放区的首址和大小。
（四）输出    
要求每执行一次，输出一次空闲区队列情况，内容包括：
编号  首址  终址  大小
注：输出空闲区队列的排序，应符合所用分配算法的要求。
*/
#include <stdio.h>    
#include <stdlib.h>    
#include <string.h>    
/* ==========宏定义部分========== */    
#define FootLoc(p) (p+p->size-1)// 指向p所指结点的底部    
#define MINSIZE 10  // 空闲区域最小的底限     
#define INITSIZE 500  // 初始化存储空间的大小    
#define Status int  // 返回状态    
#define OK 1   // 正确返回值    
#define ERROR 0   // 错误返回    
#define NUM 20   // 内存最大个数    
/* ==========结构定义部分========== */    
typedef struct WORD  //  内存字类型    
{    
    union   //  head和foot分别是结点的第一个字和最后一个字    
    {    
        WORD *link; //  头部域，指向前趋结点    
        WORD *uplink; //  底部域，指向本结点头部    
    };    
    int tag;  //  块标志，0：空闲，1：占用，头部和尾部均有    
    int size;  //  头部域，块大小    
    WORD *rlink;  // 头部域，指向后继结点    
    // char flag[10];    
}WORD,head,foot,*Space;  // *Space：可利用空间指针类型    
typedef struct ProcInf  // 分配的进程信息    
{    
    Space Sp_Head;  // 进程分配到的内存地址    
    char name[15];  // 进程描述标识    
    struct ProcInf *next; // 链表指针    
}ProcInf;    
/* =============函数声明部分============ */    
Space InitMem( int n );    
Space AllocBoundTag( WORD *pav, int n );    
Status RecycleAlg(Space p,Space pav);    
Space DuSort( WORD *pav );    
void Insert(WORD *pav,WORD *p);    
Space DelNode(ProcInf *h,char id[15]);    
Status InsertProInf(ProcInf *h, Space inser, char id[15]);    
int main(int argc, char* argv[])    
{    
    WORD *p,*Ret_Proc_Add,*Rec; // p存放申请内存地址的头指针    
    ProcInf *pi_h = NULL; // 运行进程链表头指针    
    int i;    
    int Num;    
    int size;    
    int n = INITSIZE;    
    char id[15];  // 存放进程标识    
    pi_h= (ProcInf *)malloc(sizeof(ProcInf)); // 初始化运行进程链表头结点    
    pi_h ->next =NULL;    
    p = InitMem(n);  // 初始化申请的内存空间，刚开始为一整块空白内存大小为n    
    if(!p)   // 判断是否申请成功，失败结束运行    
    {    
        printf("内存初始化失败!/n");    
        exit(1);    
    }    
    //测试用例    
    // 输入要创建进程的个数    
    printf("要申请的空间个数及其每一个空间所需要的存储空间：/n");    
    scanf("%d",&Num);    
    for( i = 0; i < Num; i++ )    
    {    
L:  printf("第%d个空间的存储空间和空间的ID：",i+1);    
        scanf("%d%s",&size,id);    
        getchar(); // 吸收回车符号    
        Ret_Proc_Add = AllocBoundTag( p, size );// 内存分配大小为size    
        if(!Ret_Proc_Add) // 判断内存是否分配成功    
        {    
            printf("内存可能不足，分配失败，重新输入./n");    
            goto L;    
        }    
        InsertProInf(pi_h,Ret_Proc_Add,id); // 插入到已经分配的内存链表当中    
        printf("分配内存标识：%s,首地址：0x%x,大小：%d/n",id,Ret_Proc_Add,Ret_Proc_Add ->size);    
    }    
    for( i = 0; i < Num; i++ )    
    {    
        printf("输入要回收结点的名字：");    
        scanf("%s",id);    
        getchar();    
        Rec = DelNode(pi_h,id);    
        if(!Rec)    
        {    
            printf("输入结点无效,请重新输入./n");    
            --i;    
        }    
        else    
            RecycleAlg(Rec,p);    
    }    
    getchar();    
    return 0;    
}    
Space DelNode(ProcInf *h,char id[15])    
{    
    ProcInf *t,*p;    
    p = h ->next;    
    t = h;    
    if( !p )    
    {    
        printf("此空间不存在!/n");    
        return NULL;    
    }    
    while(p ->next!=NULL && strcmp(id,p->name))    
    {    
        t = p;    
        p = p->next;    
    }    
    if( p ->next!=NULL )    
    {       
        t ->next = p->next;    
        return p ->Sp_Head;    
    }    
    else if(!strcmp(id,p->name))    
    {    
        t ->next = p ->next;    
        return p->Sp_Head;    
    }    
    else    
    {    
        printf("此空间不存在!/n");    
        return NULL;    
    }    
}    
Status InsertProInf(ProcInf *h,Space inser,char id[15])    
{    
    ProcInf *t,*p;    
    p = h->next;    
    if( h->next == NULL )    
    {    
        if(!(t = (ProcInf *)malloc(sizeof(ProcInf))))    
            return ERROR;    
        t ->Sp_Head = inser;    
        strcpy( t ->name,id);    
        t ->next = NULL;    
        p = t;    
        h ->next = p;    
        return OK;    
    }    
    else    
    {    
        if(!(t = (ProcInf *)malloc(sizeof(ProcInf))))    
            return ERROR;    
        t ->Sp_Head = inser;    
        strcpy( t ->name,id);    
        t ->next = NULL;    
        while(p->next)    
            p = p->next;    
        p ->next = t;    
        return OK;    
    }    
}    
Space InitMem( int n )  // 初始化分配可利用内存的大小    
{    
    Space p;    
    p = (Space)malloc(n*sizeof(WORD));    
    if( p )     
    {    
        p ->tag = 0; // 设置使用标志为：未使用    
        p ->size = n; // 设置大小    
        p ->rlink = p ->link = p;// 初始化指针    
        p ->uplink = p; //指向本身    
        return p;    
    }    
    else    
        return ERROR; // 分配失败    
}    
Space AllocBoundTag( WORD *pav, int n ) // 若有不小于n的空闲块，则分配相应的存    
{     // 储块，并返回其首地址；否则返回空，若    
    Space p,f;   // 分配后可利用空间表不空，则pav指向表中刚分配过的结点的后继结点。      
    // 查找不小于n的空闲块    
    for( p = pav; p && p->size < n && p->rlink != pav; p = p->rlink );    
    if( !p || p->size < n )    
        return NULL;  // 查找失败返回空指针    
    else    // p指向找到的空闲块    
    {    
        f = FootLoc(p);  // f指向此空闲块的底部    
        pav = p->rlink;  // pav指向*p结点的后继结点    
        if( p->size-n <= MINSIZE ) // 整块分配，不保留<=MINSIZE的剩余量    
        {    
            if( pav == p ) // 如果可利用空间表变为空表，则置pav为空    
                pav=NULL;    
            else    
            {  // 在表中删除分配的结点    
                pav->link = p->link;     
                p->link->rlink=pav;    
            }    
            p->tag = f->tag = 1;// 修改分配节点的头部和底部的标志    
        }    
        else   // 分配该块的后n个字    
        {    
            f->tag = 1; // 修改分配块的底部标志    
            p->size -= n; // 置剩余块的大小    
            f = FootLoc(p); // 指向剩余块的底部    
            f->tag = 0;f->uplink = p;//设置剩余块的底部    
            p = f + 1; // 指向分配块的头部    
            p->tag = 1; // 设置分配块头部    
            p->size = n; // 设置分配块的大小    
        }    
        return p;  // 返回分配块首地址    
    }    
}    
Status RecycleAlg(Space p,Space pav)   // 回收算法    
{    
    Space f,q,ql,t,s;    
    int n;    
    if( (p-1)->tag != 0 && (p+p->size)->tag != 0 )    
    {    
        // 释放块的左右邻区均为占用块    
        printf("释放块的左右邻区均为占用块./n");    
        p -> tag = 0;    
        FootLoc(p) ->uplink = p;    
        FootLoc(p) ->tag = 0;    
        if( !pav )    
            pav = p ->link = p ->rlink = p;    
        else    
        {    
            q = pav ->link;    
            p ->rlink = pav;    
            p ->link = q;    
            q ->rlink = pav ->link = p;    
            pav = p; // 令刚释放的结点为下次分配时的最先查询结点    
        }    
    }    
    if((p-1)->tag == 0 && (p+p->size)->tag != 0)    
    {    
        // 释放块左邻区为空闲块    
        printf("释放块左邻区为空闲块./n");    
        n = p ->size; // 释放块的大小    
        s = (p-1)->uplink; // 左空闲块的的头部地址    
        s ->size += n;  // 设置新的空闲块的大小    
        f = p + n - 1;  // 设置新的空闲块的底部    
        f ->uplink = s;    
        f ->tag = 0;    
    }    
    if( (p+p->size)->tag==0 && (p-1)->tag != 0 )    
    {    
        //释放块的右邻区为空闲块    
        printf("释放块的右邻区为空闲块./n");    
        t = p + p ->size; // 右邻空闲块的头部地址    
        p ->tag = 0;  // p为合并后的结点头部地址    
        q =t ->link;    
        p ->link = q;    
        q ->rlink = p;    
        ql = t ->rlink;    
        p ->rlink = ql;    
        ql ->link = p;    
        p ->size += t->size;    
        FootLoc(t) -> uplink = p;    
    }    
    if((p-1)->tag == 0 && (p+p->size)->tag == 0)    
    {    
        // 释放块的左右邻块均为空闲块    
        printf("释放块的左右邻块均为空闲块./n");    
        n = p->size;    
        s = (p-1)->uplink;    
        t = p+p->size;    
        s ->size += n + t ->size;    
        q = t ->link;    
        ql = t ->rlink;    
        q ->rlink = ql;    
        ql ->link = q;    
        FootLoc(t) ->uplink = s;    
    }    
    return 0;    
}    
Space DuSort( WORD *pav ) // 双链表排序    
{    
    Space p,q;    
    p = NULL;    
    q = pav ->rlink;    
    if(!pav) return NULL; // 如果为空链表，则返回空    
    while(q -> rlink != q->link) //     
    {    
        pav->link->rlink = pav->rlink;    
        pav->rlink->link = pav->link;    
        Insert(p,pav);    
        pav = q;    
        q = q->rlink;    
    }    
    Insert(p,q);  // 将最后一个结点插入    
    return p;    
}    
void Insert(WORD *pav,WORD *p) // 插入排序，按照可用大小从小到大    
{    
    WORD *t;    
    t = pav;    
    if(!pav)    
    {    
        pav = p;    
        pav ->rlink = pav ->link;    
    }    
    else    
    {    
        while(t->size<p->size)    
        {    
            t = t->rlink;    
        }    
        p ->rlink =t;    
        p ->link = t->link;    
        t ->link->rlink = p;    
        t ->link = p;    
    }    
}  