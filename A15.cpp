#define only_algorithm                        // PROTOTYP
#ifdef force_only_algorithm
#define only_algorithm
#define use_stl_for_list
#endif
#ifdef only_algorithm
#define use_list_for_slist
#endif

#include <cstdio>
#include <cstring>
#include <stdint.h>

#define make_command(x) x(#x)

#ifndef use_list_for_slist
template<class T>
class slist
{
    choke me
};
#else
#define slist list
#endif

#ifndef use_stl_for_list
template<class T>
class list
{
    #define prev wsk[M]
    #define next wsk[(1+M)&1]
    #define beg ptr[M]
    #define en ptr[(1+M)&1]
    
    struct key
    {
        T           obj;
        key         *wsk[2];

        key(const T &oo) : obj(oo) {}
    };
    int             M;
    key             *ptr[2];

    public:

        struct iterator
        {
            key     *ptr;
            int     *M;

            public:

                iterator(key *pp,int *MM) : ptr(pp),M(MM) {}

                iterator & operator=(const iterator &o)
                {
                    ptr=o.ptr;
                    M=o.M;
                }

                T & operator*()
                {
                    return ptr->obj;
                }

                iterator & operator++()
                {
                    ptr=ptr->wsk[(1+(*M))&1];
                    return *this;
                }

                T * operator->()
                {
                    return &(ptr->obj);
                }

                bool operator!=(const iterator &o) const
                {
                    return ptr!=o.ptr;
                }

                bool operator==(const iterator &o) const
                {
                    return ptr==o.ptr;
                }
        };

        list() : M(0)
        {
            beg=en=0;
        }


        explicit list(size_t n,const T& value = T()) : M(0)
        {
            beg=en=0;
            while(n--)
                push_back(value);
        }

        ~list()
        {
            clear();
        }

        void set()
        {
            M=0;
            beg=en=0;
        }

        T & front()
        {
            return beg->obj;
        }

        T & back()
        {
            return en->obj;
        }

        iterator begin()
        {
            return iterator(beg,&M);
        }

        iterator end()
        {
            return iterator(en,&M);
        }

        void clear()
        {
            while(beg)
                pop_front();
        }

        bool empty()
        {
            return beg==0;
        }

        void push_back(const T co)
        {
            if(en==0)
            {
                beg=en=new key(co);
                beg->prev=en->next=0;
            }
            else
            {
                en->next=new key(co);
                en->next->prev=en;
                en=en->next;
                en->next=0;
            }
        }

        void push_front(const T co)
        {
            if(beg==0)
            {
                beg=en=new key(co);
                beg->prev=en->next=0;
            }
            else
            {
                beg->prev=new key(co);
                beg->prev->next=beg;
                beg=beg->prev;
                beg->prev=0;
            }
        }

        void reverse()
        {
            M=(1+M)&1;
        }

        void splice(iterator position,list<T> &x)
        {
            #warning To jest prymitywna wersja funkcji splice w związku z brakiem pełnego rozwiązania strażnika (najlepiej na iteratorach).
            en->next=x.beg;
            x.beg=0;
            en=x.en;
        }

        void erase(iterator position)
        {
            #warning To jest prymitywna wersja funkcji erase w związku z niepełnym wsparciem dla iteratorów.
            key     *p=position.ptr;
            if(p->prev)
                p->prev->next=p->next;
            else
                beg=p->next;
            if(p->next)
                p->next->prev=p->prev;
            else
                en=p->prev;
            delete p;
        }

        void pop_front()
        {
            if(beg==en)
            {
                delete beg;
                beg=en=0;
            }
            else
            {
                beg=beg->next;
                delete beg->prev;
                beg->prev=0;
            }
        }

        void pop_back()
        {
            if(beg==en)
            {
                delete en;
                beg=en=0;
            }
            else
            {
                en=en->prev;
                delete en->next;
                en->next=0;
            }
        }

        #undef prev
        #undef next
        #undef beg
        #undef en
};
#else
#include <list>
using namespace std;
#endif

struct hash
{
    union
    {
        char        in[8];
        uint64_t    out;
    };

    public:
        hash() {}
        hash(const char *ptr)
        {
            strncpy(in,ptr,8);
        }
        hash(const hash & o) : out(o.out) {}

        hash & operator=(const hash & o)
        {
            out=o.out;
            return *this;
        }
        hash & operator=(const char *ptr)
        {
            strncpy(in,ptr,8);
            return *this;
        }

        bool operator==(const hash & o)
        {
            return out==o.out;
        }

        uint64_t getInt()
        {
            return out;
        }

        void print()
        {
            int i=0;
            while(i<8 && in[i]!=0)
            {
                putchar(in[i++]);
                fflush(stdout);
            }
        }
};

namespace Command
{
    hash            make_command(NEW),
                    make_command(BACK),
                    make_command(FRONT),
                    make_command(PRINT),
                    make_command(REVERSE),
                    make_command(UNION),
                    make_command(DELFRONT),
                    make_command(DELBACK);
}

struct train
{
    hash            name;
    list<hash>      entry;

    train(const char *nn,const char *obj) : name(nn),entry(1,obj) {}
    train(const char *nn,hash &obj) : name(nn),entry(1,obj) {}
    train() {}

    void dump()
    {
        putchar('\"');
        name.print();
        printf("\":\n");
        for(list<hash>::iterator i=entry.begin(),e=entry.end();i!=e;++i)
        {
            i->print();
            printf("<-");
        }
        entry.back().print();
        putchar('\n');
    }
};

slist<train>        set;

inline slist<train>::iterator find(const char *n)
{
    hash            name(n);
    for(slist<train>::iterator i=set.begin(),e=set.end();i!=e;++i)
    {
        if(i->name==name)
            return i;
    }
    return set.end();
}

int main()
{
    int             z;
    int             n;
    char            in[9];
    scanf("%d\n",&z);
    while(z--)
    {
        scanf("%d\n",&n);
        hash        arg1();
        hash        arg2();
        char        tmp[9];

        set.clear();

        for(int i=0;i<n;++i)
        {
            scanf("%s ",in);
            hash    command(in);
            using namespace Command;

            if(command==NEW)
            {
                scanf("%s %s\n",in,tmp);
                train   t;
                set.push_back(t);
                set.back().name=in;
                set.back().entry.set();
                set.back().entry.push_back(tmp);
                //puts("NEW");
            }
            else if(command==BACK)
            {
                scanf("%s %s\n",in,tmp);
                find(in)->entry.push_back(tmp);
                //puts("BACK");
            }
            else if(command==FRONT)
            {
                scanf("%s %s\n",in,tmp);
                find(in)->entry.push_front(tmp);
                //puts("FRONT");
            }
            else if(command==PRINT)
            {
                scanf("%s\n",in);
                find(in)->dump();
                //puts("PRINT");
            }
            else if(command==REVERSE)
            {
                scanf("%s\n",in);
                find(in)->entry.reverse();
                //puts("REVERSE");
            }
            else if(command==UNION)
            {
                scanf("%s %s\n",in,tmp);
                list<train>::iterator   i=find(in),
                                        t=find(tmp);
                i->entry.splice(i->entry.end(),t->entry);
                set.erase(t);
                //puts("UNION");
            }
            else if(command==DELFRONT)
            {
                scanf("%s %s\n",in,tmp);
                list<train>::iterator   t=find(tmp);
                train                   nt;
                set.push_back(nt);
                set.back().name=in;
                set.back().entry.set();
                set.back().entry.push_back(t->entry.front());
                
                t->entry.pop_front();
                if(t->entry.empty())
                    set.erase(t);
            }
            else if(command==DELBACK)
            {
                scanf("%s %s\n",in,tmp);
                list<train>::iterator   t=find(in);
                train                   nt;
                set.push_back(nt);
                set.back().name=tmp;
                set.back().entry.set();
                set.back().entry.push_back(t->entry.back());

                t->entry.pop_back();
                if(t->entry.empty())
                    set.erase(t);
            }
            else
                throw 123;

            /*puts("DUMP");
            for(list<train>::iterator i=set.begin(),e=set.end();i!=e;++i)
            {
                i->dump();
            }
            puts("\\Dump");*/
        }
    }
    return 0;
}
