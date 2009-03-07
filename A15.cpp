#define force_only_algorithm                        // PROTOTYP
#ifdef force_only_algorithm
#define only_algorithm
#endif
#ifdef only_algorithm
#define use_stl_for_list
#endif

#define make_command(x) x(#x)

#ifndef force_only_algorithm
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
    choke me
};
#else
#include <list>
using namespace std;
#endif

#include <cstdio>
#include <cstring>
#include <stdint.h>

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
                putchar(in[i++]);
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

    void dump()
    {
        putchar('\"');
        name.print();
        printf("\":\n");
        entry.front().print();
        for(list<hash>::iterator i=++entry.begin(),e=entry.end();i!=e;++i)
        {
            printf("<-");
            i->print();
        }
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

        for(int i=0;i<n;++i)
        {
            scanf("%s ",in);
            hash    command(in);
            using namespace Command;

            if(command==NEW)
            {
                scanf("%s %s\n",in,tmp);
                train   t(in,tmp);
                set.push_back(t);
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
                train                   nt(in,t->entry.front());
                set.push_back(nt);
                t->entry.pop_front();
                if(t->entry.empty())
                    set.erase(t);
            }
            else if(command==DELBACK)
            {
                scanf("%s %s\n",in,tmp);
                list<train>::iterator   t=find(in);
                train                   nt(tmp,t->entry.back());
                set.push_back(nt);
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
