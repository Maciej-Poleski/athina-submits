#include <cstdio>
#include <cstring>

template <class T>
void swap(T &a,T &b)
{
    T t=a;
    a=b;
    b=t;
}

struct train
{
    char            *name;
    train           *ptr[2];

    train(const char *ww)
    {
        name=new char[9];
        memcpy(name,ww,9);
    }

    ~train()
    {
        delete [] name;
    }
};

struct slist
{
    char            *name;
    slist           *next;
    train           *begin;
    train           *end;

    slist(const char *ww)
    {
        name=new char[9];
        memcpy(name,ww,9);
    }

    ~slist()
    {
        clear();
        delete [] name;
    }

    bool empty()
    {
        return begin==0;
    };

    void clear()
    {
        train   *old;
        while(begin!=0)
        {
            old=begin;
            begin=begin->ptr[begin->ptr[1]!=0];
            delete old;
            if(begin)
            begin->ptr[begin->ptr[1]==old]=0;
        }
    }

    /*void dump0()
    {
        train   *pt=begin;
        train   *old=0;
        train   *o2=0;
        printf("%s: ",name);
        while(pt!=end)
        {
            printf("%x ",pt);
            fflush(stdout);
            printf("%x %x ",pt->ptr[0],pt->ptr[1]);
            fflush(stdout);
            printf("%s ",pt->name);
            fflush(stdout);
            o2=pt;
            pt=pt->ptr[pt->ptr[1]!=pt && pt->ptr[1]!=old];
            old=o2;
        }
        printf("%s\n",pt->name);
    }*/
}*head;

int main()
{
    int             z;
    char            in[9];
    char            t1[9];
    scanf("%d\n",&z);
    while(z--)
    {
        int         n;
        scanf("%d\n",&n);
        head=0;
        while(n--)
        {
            scanf("%s ",in);
            if(*in=='N')
            {
                scanf("%s %s\n",in,t1);
                slist   *pt=new slist(in);
                pt->next=head;
                head=pt;
                head->begin=head->end=new train(t1);
                head->begin->ptr[0]=head->begin->ptr[1]=0;

                //head->dump0();
            }
            else if(*in=='B')
            {
                scanf("%s %s\n",in,t1);
                slist   *lpt=head;
                while(strcmp(lpt->name,in))
                    lpt=lpt->next;
                train   *tpt=lpt->end->ptr[lpt->end->ptr[1]==0]=new train(t1);
                tpt->ptr[0]=lpt->end;
                tpt->ptr[1]=0;
                lpt->end=tpt;

                //lpt->dump0();
            }
            else if(*in=='F')
            {
                scanf("%s %s\n",in,t1);
                slist   *lpt=head;
                while(strcmp(lpt->name,in))
                    lpt=lpt->next;
                train   *tpt=lpt->begin->ptr[lpt->begin->ptr[1]==0]=new train(t1);
                tpt->ptr[0]=lpt->begin;
                tpt->ptr[1]=0;
                lpt->begin=tpt;

                //lpt->dump0();
            }
            else if(*in=='P')
            {
                scanf("%s\n",in);
                slist   *lpt=head;
                train   *old=0;
                train   *o2=0;
                while(strcmp(lpt->name,in))
                    lpt=lpt->next;
                train   *tpt=lpt->begin;
                printf("\"%s\":\n",lpt->name);
                while(tpt!=lpt->end)
                {
                    printf("%s<-",tpt->name);
                    fflush(stdout);
                    o2=tpt;
                    tpt=tpt->ptr[tpt->ptr[1]!=tpt && tpt->ptr[1]!=old];
                    old=o2;
                }
                printf("%s\n",lpt->end->name);
            }
            else if(*in=='R')
            {
                scanf("%s\n",in);
                slist   *lpt=head;
                while(strcmp(lpt->name,in))
                    lpt=lpt->next;
                swap(lpt->begin,lpt->end);

                //lpt->dump0();
            }
            else if(*in=='U')
            {
                scanf("%s %s\n",in,t1);
                slist       *lpt1=head;
                slist       **lpt2=&head;
                slist       *old;
                while(strcmp(lpt1->name,in))
                    lpt1=lpt1->next;
                while(strcmp((*lpt2)->name,t1))
                    lpt2=&((*lpt2)->next);
                old=*lpt2;

                *lpt2=(*lpt2)->next;

                lpt1->end->ptr[lpt1->end->ptr[1]==0]=old->begin;
                old->begin->ptr[old->begin->ptr[1]==0]=lpt1->end;
                lpt1->end=old->end;

                old->begin=old->end=0;

                delete old;

                //lpt1->dump0();
            }
            else if(*in=='D')
            {
                if(in[3]=='F')
                {
                    scanf("%s %s\n",in,t1);
                    slist   *lpt1=head;
                    while(strcmp(lpt1->name,t1))
                        lpt1=lpt1->next;
                    if(lpt1->begin==lpt1->end)
                    {
                        memcpy(lpt1->name,in,9);
                    }
                    else
                    {
                        train   *tpt=new train(lpt1->begin->name);
                        slist   *nht=new slist(in);
                        nht->next=head;
                        nht->begin=nht->end=tpt;
                        tpt=lpt1->begin;
                        lpt1->begin=lpt1->begin->ptr[lpt1->begin->ptr[1]!=0];
                        delete tpt;
                        head=nht;
                        lpt1->begin->ptr[lpt1->begin->ptr[1]==tpt]=0;
                        head->begin->ptr[0]=head->begin->ptr[1]=0;
                    }
                }
                else if(in[3]=='B')
                {
                    scanf("%s %s\n",t1,in);
                    slist   *lpt1=head;
                        while(strcmp(lpt1->name,t1))
                    lpt1=lpt1->next;
                    if(lpt1->begin==lpt1->end)
                    {
                        memcpy(lpt1->name,in,9);
                    }
                    else
                    {
                        train   *tpt=new train(lpt1->end->name);
                        slist   *nht=new slist(in);
                        nht->next=head;
                        nht->begin=nht->end=tpt;
                        tpt=lpt1->end;
                        lpt1->end=lpt1->end->ptr[lpt1->end->ptr[1]!=0];
                        delete tpt;
                        head=nht;
                        lpt1->end->ptr[lpt1->end->ptr[1]==tpt]=0;
                        head->begin->ptr[0]=head->begin->ptr[1]=0;
                    }
                }
                else
                    throw 123;
            }
            else
                throw 123;
            
        }
        while(head)
        {
            slist   *th=head->next;
            head->clear();
            delete head;
            head=th;
        }
    }
    return 0;
}
