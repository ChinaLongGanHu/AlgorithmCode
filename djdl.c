/*
多级反馈队列调度算法：
1.设置多个就绪队列，并给队列赋予不同的优先级数，第一个最高，依次递减。
2.赋予各个队列中进程执行时间片的大小，优先级越高的队列，时间片越少。
3.当一个新进程进入内存后，首先将其放入一个对队列末尾，如果在一个时间片结束时尚未完成，将其转入第二队列末尾。
4.当一个进程从一个队列移至第N个队列后，便在第nge队列中采用时间片轮转执行完。
5.仅当时间片空闲时，才调度第二个队列中的进程。
(1~i-1)空闲时，才调度i，如果处理机正在第i队列中运行，又有新进程进入优先权较高
队列，则新进程抢占处理机，将正在运行的进程放入第i队列队尾，将处理机分给新进程。
*/
/*
一、目的和要求
进程调度是处理机管理的核心内容。本实验要求用高级语言编写模拟进程调度程序，以便加深理解有关进程控制快、进程队列等概念，并体会和了解优先数算法和时间片轮转算法的具体实施办法。
二、实验内容
1.设计进程控制块PCB的结构，通常应包括如下信息：
进程名、进程优先数（或轮转时间片数）、进程已占用的CPU时间、进程到完成还需要的时间、进程的状态、当前队列指针等。
  2.编写两种调度算法程序：
优先数调度算法程序
循环轮转调度算法程序
3.按要求输出结果。
三、提示和说明
分别用两种调度算法对伍个进程进行调度。每个进程可有三种状态；执行状态（RUN）、就绪状态（READY,包括等待状态）和完成状态（FINISH），并假定初始状态为就绪状态。
（一）进程控制块结构如下：
      NAME——进程标示符
      PRIO/ROUND——进程优先数/进程每次轮转的时间片数（设为常数2）
      CPUTIME——进程累计占用CPU的时间片数
      NEEDTIME——进程到完成还需要的时间片数
      STATE——进程状态
      NEXT——链指针
注：
    1.为了便于处理，程序中进程的的运行时间以时间片为单位进行计算；
    2.各进程的优先数或轮转时间片数，以及进程运行时间片数的初值，均由用户在程序运行时给定。
（二）进程的就绪态和等待态均为链表结构，共有四个指针如下：
      RUN——当前运行进程指针
      READY——就需队列头指针
      TAIL——就需队列尾指针
      FINISH——完成队列头指针
（三）程序说明
    1. 在优先数算法中，进程优先数的初值设为：
      50-NEEDTIME
每执行一次，优先数减1，CPU时间片数加1，进程还需要的时间片数减1。
在轮转法中，采用固定时间片单位（两个时间片为一个单位），进程每轮转一次，CPU时间片数加2，进程还需要的时间片数减2，并退出CPU，排到就绪队列尾，等待下一次调度。
    2. 程序的模块结构提示如下：
整个程序可由主程序和如下7个过程组成：
（1）INSERT1——在优先数算法中，将尚未完成的PCB按优先数顺序插入到就绪队列中；
（2）INSERT2——在轮转法中，将执行了一个时间片单位（为2），但尚未完成的进程的PCB，插到就绪队列的队尾；
（3）FIRSTIN——调度就绪队列的第一个进程投入运行；
（4）PRINT——显示每执行一次后所有进程的状态及有关信息。
（5）CREATE——创建新进程，并将它的PCB插入就绪队列；
（6）PRISCH——按优先数算法调度进程；
（7）ROUNDSCH——按时间片轮转法调度进程。
主程序定义PCB结构和其他有关变量。
（四）运行和显示
程序开始运行后，首先提示：请用户选择算法，输入进程名和相应的NEEDTIME值。
每次显示结果均为如下5个字段：
      name   cputime   needtime   priority   state
注：
    1．在state字段中，"R"代表执行态，"W"代表就绪（等待）态，"F"代表完成态。
2．应先显示"R"态的，再显示"W"态的，再显示"F"态的。
  3．在"W"态中，以优先数高低或轮转顺序排队；在"F"态中，以完成先后顺序排队。
*/

#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
typedef struct node   /*进程节点信息*/  
{  
char name[20];   /*进程的名字*/  
int prio;    /*进程的优先级*/  
int round;    /*分配CPU的时间片*/  
int cputime;   /*CPU执行时间*/  
int needtime;   /*进程执行所需要的时间*/  
char state;    /*进程的状态，W——就绪态，R——执行态，F——完成态*/  
int count;    /*记录执行的次数*/  
struct node *next;  /*链表指针*/  
}PCB;  
typedef struct Queue  /*多级就绪队列节点信息*/  
{  
PCB *LinkPCB;   /*就绪队列中的进程队列指针*/  
int prio;    /*本就绪队列的优先级*/  
int round;    /*本就绪队列所分配的时间片*/  
struct Queue *next;  /*指向下一个就绪队列的链表指针*/  
}ReadyQueue;  
PCB *run=NULL,*finish=NULL; /*定义三个队列，就绪队列，执行队列和完成队列*/  
ReadyQueue *Head = NULL; /*定义第一个就绪队列*/  
int num;     /*进程个数*/  
int ReadyNum;    /*就绪队列个数*/  
void Output();          /*进程信息输出函数*/  
void InsertFinish(PCB *in);       /*将进程插入到完成队列尾部*/  
void InsertPrio(ReadyQueue *in);     /*创建就绪队列，规定优先数越小，优先级越低*/  
void PrioCreate();         /*创建就绪队列输入函数*/  
void GetFirst(ReadyQueue *queue);     /*取得某一个就绪队列中的队头进程*/  
void InsertLast(PCB *in,ReadyQueue *queue);   /*将进程插入到就绪队列尾部*/  
void ProcessCreate();        /*进程创建函数*/  
void RoundRun(ReadyQueue *timechip);    /*时间片轮转调度算法*/  
void MultiDispatch();        /*多级调度算法，每次执行一个时间片*/  
  
int main(void)  
{  
PrioCreate(); /*创建就绪队列*/  
ProcessCreate();/*创建就绪进程队列*/  
MultiDispatch();/*算法开始*/  
Output();  /*输出最终的调度序列*/  
return 0;  
}  
void Output()  /*进程信息输出函数*/  
{  
ReadyQueue *print = Head;  
PCB *p;  
printf("进程名/t优先级/t轮数/tcpu时间/t需要时间/t进程状态/t计数器/n");  
while(print)  
{  
  if(print ->LinkPCB != NULL)  
  {  
   p=print ->LinkPCB;  
   while(p)  
   {  
    printf("%s/t%d/t%d/t%d/t%d/t/t%c/t/t%d/n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);     
    p = p->next;  
   }  
  }  
  print = print->next;  
}  
p = finish;  
while(p!=NULL)  
{  
  printf("%s/t%d/t%d/t%d/t%d/t/t%c/t/t%d/n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);  
  p = p->next;  
}  
p = run;  
while(p!=NULL)  
{  
  printf("%s/t%d/t%d/t%d/t%d/t/t%c/t/t%d/n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);  
  p = p->next;  
}  
  
  
}  
void InsertFinish(PCB *in)  /*将进程插入到完成队列尾部*/  
{  
PCB *fst;  
fst = finish;  
  
if(finish == NULL)  
{  
  in->next = finish;  
  finish = in;  
}  
else  
{  
  while(fst->next != NULL)  
  {  
   fst = fst->next;  
  }  
  in ->next = fst ->next;  
  fst ->next = in;  
}  
}  
void InsertPrio(ReadyQueue *in)  /*创建就绪队列，规定优先数越小，优先级越低*/  
{  
ReadyQueue *fst,*nxt;  
fst = nxt = Head;  
  
if(Head == NULL)    /*如果没有队列，则为第一个元素*/  
{  
  in->next = Head;  
  Head = in;  
}  
else       /*查到合适的位置进行插入*/  
{  
  if(in ->prio >= fst ->prio)  /*比第一个还要大，则插入到队头*/  
  {  
   in->next = Head;  
   Head = in;  
  }  
  else  
  {  
   while(fst->next != NULL)  /*移动指针查找第一个别它小的元素的位置进行插入*/  
   {  
    nxt = fst;  
    fst = fst->next;  
   }  
     
   if(fst ->next == NULL)  /*已经搜索到队尾，则其优先级数最小，将其插入到队尾即可*/  
   {  
    in ->next = fst ->next;  
    fst ->next = in;  
   }  
   else     /*插入到队列中*/  
   {  
    nxt = in;  
    in ->next = fst;  
   }  
  }  
}  
}  
void PrioCreate() /*创建就绪队列输入函数*/  
{  
ReadyQueue *tmp;  
int i;  
  
printf("输入就绪队列的个数：/n");  
scanf("%d",&ReadyNum);  
  
printf("输入每个就绪队列的CPU时间片：/n");  
for(i = 0;i < ReadyNum; i++)  
{  
  if((tmp = (ReadyQueue *)malloc(sizeof(ReadyQueue)))==NULL)  
  {  
   perror("malloc");  
   exit(1);  
  }  
  scanf("%d",&(tmp->round));  /*输入此就绪队列中给每个进程所分配的CPU时间片*/  
  tmp ->prio = 50 - tmp->round;  /*设置其优先级，时间片越高，其优先级越低*/  
  tmp ->LinkPCB = NULL;    /*初始化其连接的进程队列为空*/  
  tmp ->next = NULL;  
  InsertPrio(tmp);     /*按照优先级从高到低，建立多个就绪队列*/  
}  
}  
void GetFirst(ReadyQueue *queue)     /*取得某一个就绪队列中的队头进程*/  
{  
run = queue ->LinkPCB;  
  
if(queue ->LinkPCB != NULL)  
{  
  run ->state = 'R';  
  queue ->LinkPCB = queue ->LinkPCB ->next;  
  run ->next = NULL;  
}  
}  
void InsertLast(PCB *in,ReadyQueue *queue)  /*将进程插入到就绪队列尾部*/  
{  
PCB *fst;  
fst = queue->LinkPCB;  
  
if( queue->LinkPCB == NULL)  
{  
  in->next =  queue->LinkPCB;  
  queue->LinkPCB = in;  
}  
else  
{  
  while(fst->next != NULL)  
  {  
   fst = fst->next;  
  }  
  in ->next = fst ->next;  
  fst ->next = in;  
}  
}  
void ProcessCreate() /*进程创建函数*/  
{  
PCB *tmp;  
int i;  
  
printf("输入进程的个数：/n");  
scanf("%d",&num);  
printf("输入进程名字和进程所需时间：/n");  
for(i = 0;i < num; i++)  
{  
  if((tmp = (PCB *)malloc(sizeof(PCB)))==NULL)  
  {  
   perror("malloc");  
   exit(1);  
  }  
  scanf("%s",tmp->name);  
  getchar();        /*吸收回车符号*/  
  scanf("%d",&(tmp->needtime));  
  tmp ->cputime = 0;  
  tmp ->state ='W';  
  tmp ->prio = 50 - tmp->needtime;  /*设置其优先级，需要的时间越多，优先级越低*/  
  tmp ->round = Head ->round;  
  tmp ->count = 0;  
  InsertLast(tmp,Head);      /*按照优先级从高到低，插入到就绪队列*/  
}  
}  
void RoundRun(ReadyQueue *timechip)    /*时间片轮转调度算法*/  
{  
  
int flag = 1;  
  
GetFirst(timechip);  
while(run != NULL)  
{  
  while(flag)  
  {  
   run->count++;  
   run->cputime++;  
   run->needtime--;  
   if(run->needtime == 0) /*进程执行完毕*/  
   {  
    run ->state = 'F';  
    InsertFinish(run);  
    flag = 0;  
   }  
   else if(run->count == timechip ->round)/*时间片用完*/  
   {  
    run->state = 'W';  
    run->count = 0;   /*计数器清零，为下次做准备*/  
    InsertLast(run,timechip);  
    flag = 0;  
   }  
  }  
  flag = 1;  
  GetFirst(timechip);  
}  
}  
void MultiDispatch()   /*多级调度算法，每次执行一个时间片*/  
{  
int flag = 1;  
int k = 0;  
  
ReadyQueue *point;  
point = Head;  
  
GetFirst(point);  
while(run != NULL)  
{  
  Output();  
  if(Head ->LinkPCB!=NULL)  
   point = Head;  
  while(flag)  
  {  
   run->count++;  
   run->cputime++;  
   run->needtime--;  
   if(run->needtime == 0) /*进程执行完毕*/  
   {  
    run ->state = 'F';  
    InsertFinish(run);  
    flag = 0;  
   }  
   else if(run->count == run->round)/*时间片用完*/  
   {  
    run->state = 'W';  
    run->count = 0;   /*计数器清零，为下次做准备*/  
    if(point ->next!=NULL)  
    {  
     run ->round = point->next ->round;/*设置其时间片是下一个就绪队列的时间片*/  
     InsertLast(run,point->next);  /*将进程插入到下一个就绪队列中*/  
     flag = 0;  
    }  
    else  
    {  
     RoundRun(point);   /*如果为最后一个就绪队列就调用时间片轮转算法*/  
     break;  
    }  
   }  
   ++k;  
   if(k == 3)  
   {  
    ProcessCreate();  
   }  
  }  
  flag = 1;  
  if(point ->LinkPCB == NULL)/*就绪队列指针下移*/  
   point =point->next;  
  if(point ->next ==NULL)  
  {  
   RoundRun(point);  
   break;  
  }  
  GetFirst(point);  
}  
}   








