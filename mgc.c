/*
ʵ�黷����C/C++
һ��Ŀ�ĺ�Ҫ��
����������Ӧ�ýϹ㷺��һ�ִ洢����������ʵ��Ҫ����һ�ֽṹ���߼����Թ��������������
���ƶ�̬���������㷨�ͻ����㷨ģ����򣬲����۲�ͬ�����㷨���ص㡣
����ʵ������
1����д��First Fit Algorithm
2����д��Best Fit Algorithm
3����д�������������㷨
������ʾ��˵��
��һ�������� 
1���������������node������ 3��Ԫ�أ�
��1��adr--�����׵�ַ
��2��size--������С
��3��next--ָ����һ��������ָ��
2������ 3��ָ��node�ṹ��ָ�������
��1��head1--������������ָ��
��2��back1--ָ���ͷ���node�ṹ��ָ��
��3��assign--ָ��������ڴ����node�ṹ��ָ��
3������ 1�����α�����
free--�û�����洢���Ĵ�С�����û����룩
����������
1������check���̣����ڼ��ָ�����ͷſ飨���û����룩�ĺϷ���
2������assignment1���̣�ʵ��First Fit Algorithm
3������assignment2���̣�ʵ��Best Fit Algorithm
4������acceptment1���̣�ʵ��First Fit Algorithm�Ļ����㷨
5������acceptment2���̣�ʵ��Best Fit Algorithm�Ļ����㷨
6������print���̣���ӡ����������
������ִ��
������������һ���������������ַΪ0����СΪ32767��Ȼ����ʾ�û�ʹ�����ַ����㷨��
����ʾ�Ƿ��仹�ǻ��գ�����ʱҪ�������������Ĵ�С������ʱҪ�������ͷ�������ַ�ʹ�С��
���ģ����    
Ҫ��ÿִ��һ�Σ����һ�ο�����������������ݰ�����
���  ��ַ  ��ַ  ��С
ע��������������е�����Ӧ�������÷����㷨��Ҫ��
*/
#include <stdio.h>    
#include <stdlib.h>    
#include <string.h>    
/* ==========�궨�岿��========== */    
#define FootLoc(p) (p+p->size-1)// ָ��p��ָ���ĵײ�    
#define MINSIZE 10  // ����������С�ĵ���     
#define INITSIZE 500  // ��ʼ���洢�ռ�Ĵ�С    
#define Status int  // ����״̬    
#define OK 1   // ��ȷ����ֵ    
#define ERROR 0   // ���󷵻�    
#define NUM 20   // �ڴ�������    
/* ==========�ṹ���岿��========== */    
typedef struct WORD  //  �ڴ�������    
{    
    union   //  head��foot�ֱ��ǽ��ĵ�һ���ֺ����һ����    
    {    
        WORD *link; //  ͷ����ָ��ǰ�����    
        WORD *uplink; //  �ײ���ָ�򱾽��ͷ��    
    };    
    int tag;  //  ���־��0�����У�1��ռ�ã�ͷ����β������    
    int size;  //  ͷ���򣬿��С    
    WORD *rlink;  // ͷ����ָ���̽��    
    // char flag[10];    
}WORD,head,foot,*Space;  // *Space�������ÿռ�ָ������    
typedef struct ProcInf  // ����Ľ�����Ϣ    
{    
    Space Sp_Head;  // ���̷��䵽���ڴ��ַ    
    char name[15];  // ����������ʶ    
    struct ProcInf *next; // ����ָ��    
}ProcInf;    
/* =============������������============ */    
Space InitMem( int n );    
Space AllocBoundTag( WORD *pav, int n );    
Status RecycleAlg(Space p,Space pav);    
Space DuSort( WORD *pav );    
void Insert(WORD *pav,WORD *p);    
Space DelNode(ProcInf *h,char id[15]);    
Status InsertProInf(ProcInf *h, Space inser, char id[15]);    
int main(int argc, char* argv[])    
{    
    WORD *p,*Ret_Proc_Add,*Rec; // p��������ڴ��ַ��ͷָ��    
    ProcInf *pi_h = NULL; // ���н�������ͷָ��    
    int i;    
    int Num;    
    int size;    
    int n = INITSIZE;    
    char id[15];  // ��Ž��̱�ʶ    
    pi_h= (ProcInf *)malloc(sizeof(ProcInf)); // ��ʼ�����н�������ͷ���    
    pi_h ->next =NULL;    
    p = InitMem(n);  // ��ʼ��������ڴ�ռ䣬�տ�ʼΪһ����հ��ڴ��СΪn    
    if(!p)   // �ж��Ƿ�����ɹ���ʧ�ܽ�������    
    {    
        printf("�ڴ��ʼ��ʧ��!/n");    
        exit(1);    
    }    
    //��������    
    // ����Ҫ�������̵ĸ���    
    printf("Ҫ����Ŀռ��������ÿһ���ռ�����Ҫ�Ĵ洢�ռ䣺/n");    
    scanf("%d",&Num);    
    for( i = 0; i < Num; i++ )    
    {    
L:  printf("��%d���ռ�Ĵ洢�ռ�Ϳռ��ID��",i+1);    
        scanf("%d%s",&size,id);    
        getchar(); // ���ջس�����    
        Ret_Proc_Add = AllocBoundTag( p, size );// �ڴ�����СΪsize    
        if(!Ret_Proc_Add) // �ж��ڴ��Ƿ����ɹ�    
        {    
            printf("�ڴ���ܲ��㣬����ʧ�ܣ���������./n");    
            goto L;    
        }    
        InsertProInf(pi_h,Ret_Proc_Add,id); // ���뵽�Ѿ�������ڴ�������    
        printf("�����ڴ��ʶ��%s,�׵�ַ��0x%x,��С��%d/n",id,Ret_Proc_Add,Ret_Proc_Add ->size);    
    }    
    for( i = 0; i < Num; i++ )    
    {    
        printf("����Ҫ���ս������֣�");    
        scanf("%s",id);    
        getchar();    
        Rec = DelNode(pi_h,id);    
        if(!Rec)    
        {    
            printf("��������Ч,����������./n");    
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
        printf("�˿ռ䲻����!/n");    
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
        printf("�˿ռ䲻����!/n");    
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
Space InitMem( int n )  // ��ʼ������������ڴ�Ĵ�С    
{    
    Space p;    
    p = (Space)malloc(n*sizeof(WORD));    
    if( p )     
    {    
        p ->tag = 0; // ����ʹ�ñ�־Ϊ��δʹ��    
        p ->size = n; // ���ô�С    
        p ->rlink = p ->link = p;// ��ʼ��ָ��    
        p ->uplink = p; //ָ����    
        return p;    
    }    
    else    
        return ERROR; // ����ʧ��    
}    
Space AllocBoundTag( WORD *pav, int n ) // ���в�С��n�Ŀ��п飬�������Ӧ�Ĵ�    
{     // ���飬���������׵�ַ�����򷵻ؿգ���    
    Space p,f;   // ���������ÿռ���գ���pavָ����иշ�����Ľ��ĺ�̽�㡣      
    // ���Ҳ�С��n�Ŀ��п�    
    for( p = pav; p && p->size < n && p->rlink != pav; p = p->rlink );    
    if( !p || p->size < n )    
        return NULL;  // ����ʧ�ܷ��ؿ�ָ��    
    else    // pָ���ҵ��Ŀ��п�    
    {    
        f = FootLoc(p);  // fָ��˿��п�ĵײ�    
        pav = p->rlink;  // pavָ��*p���ĺ�̽��    
        if( p->size-n <= MINSIZE ) // ������䣬������<=MINSIZE��ʣ����    
        {    
            if( pav == p ) // ��������ÿռ���Ϊ�ձ�����pavΪ��    
                pav=NULL;    
            else    
            {  // �ڱ���ɾ������Ľ��    
                pav->link = p->link;     
                p->link->rlink=pav;    
            }    
            p->tag = f->tag = 1;// �޸ķ���ڵ��ͷ���͵ײ��ı�־    
        }    
        else   // ����ÿ�ĺ�n����    
        {    
            f->tag = 1; // �޸ķ����ĵײ���־    
            p->size -= n; // ��ʣ���Ĵ�С    
            f = FootLoc(p); // ָ��ʣ���ĵײ�    
            f->tag = 0;f->uplink = p;//����ʣ���ĵײ�    
            p = f + 1; // ָ�������ͷ��    
            p->tag = 1; // ���÷����ͷ��    
            p->size = n; // ���÷����Ĵ�С    
        }    
        return p;  // ���ط�����׵�ַ    
    }    
}    
Status RecycleAlg(Space p,Space pav)   // �����㷨    
{    
    Space f,q,ql,t,s;    
    int n;    
    if( (p-1)->tag != 0 && (p+p->size)->tag != 0 )    
    {    
        // �ͷſ������������Ϊռ�ÿ�    
        printf("�ͷſ������������Ϊռ�ÿ�./n");    
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
            pav = p; // ����ͷŵĽ��Ϊ�´η���ʱ�����Ȳ�ѯ���    
        }    
    }    
    if((p-1)->tag == 0 && (p+p->size)->tag != 0)    
    {    
        // �ͷſ�������Ϊ���п�    
        printf("�ͷſ�������Ϊ���п�./n");    
        n = p ->size; // �ͷſ�Ĵ�С    
        s = (p-1)->uplink; // ����п�ĵ�ͷ����ַ    
        s ->size += n;  // �����µĿ��п�Ĵ�С    
        f = p + n - 1;  // �����µĿ��п�ĵײ�    
        f ->uplink = s;    
        f ->tag = 0;    
    }    
    if( (p+p->size)->tag==0 && (p-1)->tag != 0 )    
    {    
        //�ͷſ��������Ϊ���п�    
        printf("�ͷſ��������Ϊ���п�./n");    
        t = p + p ->size; // ���ڿ��п��ͷ����ַ    
        p ->tag = 0;  // pΪ�ϲ���Ľ��ͷ����ַ    
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
        // �ͷſ�������ڿ��Ϊ���п�    
        printf("�ͷſ�������ڿ��Ϊ���п�./n");    
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
Space DuSort( WORD *pav ) // ˫��������    
{    
    Space p,q;    
    p = NULL;    
    q = pav ->rlink;    
    if(!pav) return NULL; // ���Ϊ�������򷵻ؿ�    
    while(q -> rlink != q->link) //     
    {    
        pav->link->rlink = pav->rlink;    
        pav->rlink->link = pav->link;    
        Insert(p,pav);    
        pav = q;    
        q = q->rlink;    
    }    
    Insert(p,q);  // �����һ��������    
    return p;    
}    
void Insert(WORD *pav,WORD *p) // �������򣬰��տ��ô�С��С����    
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