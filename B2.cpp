#include <cstdio>

template <class T>
class queue
{
        struct key
        {
            key *next;
            T obj;
            
            key() : next(0) {}
        };
        
        key *begin,*end;
        
    public:
        queue() : begin(0),end(0) {}
        ~queue()
        {
            while(!empty())
            {
                pop();
            }
        }
        
        void push(T obj)
        {
            if(end)
            {
                key *wsk=new key;
                end->next=wsk;
                end=wsk;
                
                wsk->obj=obj;
            }
            else
            {
                begin=end=new key;
                end->obj=obj;
            }
        }
        bool empty()
        {
            return (begin==0?true:false);
        }
        
        void pop()
        {
            if(begin)
            {
                key *tmp=begin;
                begin=begin->next;
                delete tmp;
            }
            if(!begin)
            {
                //puts("Kolejka oczyszczona");
                end=begin;
            }
        }
    
        T front()
        {
            return begin->obj;
        }
        
        void clear()
        {
            this->~queue();
        }
};

struct person
{
    queue<unsigned int> out;
    unsigned int in;
    
    person() : in(0),out() {}
    ~person()
    {
        out.~queue<unsigned int>();
    }
};

int main()
{/*
#ifdef queue_test
    queue<int> kolejka;
    unsigned int z,q;
    int tmp;
    scanf("%u",&z);
    q=z;
    while(z--)
    {
        scanf("%d",&tmp);
        kolejka.push(tmp);
    }
    while(!kolejka.empty())
    {
        printf("%d ",kolejka.front());
        kolejka.pop();
    }
    putchar('\n');
    z=q;
    while(z--)
    {
        scanf("%d",&tmp);
        kolejka.push(tmp);
    }
    while(!kolejka.empty())
    {
        printf("%d ",kolejka.front());
        kolejka.pop();
    }
    putchar('\n');
#endif*/
    unsigned int z,n,m,x,y;
    scanf("%u",&z);
    while(z--)
    {
        scanf("%u%u",&n,&m);
        person osoby[n+1];
        for(unsigned int i=0;i<m;++i)
        {
            scanf("%u%u",&x,&y);
            osoby[x].out.push(y);
            ++osoby[y].in;
        }
        queue<unsigned int> kolejka;
        for(unsigned int i=1;i<=n;++i)
            if(osoby[i].in==0)
                kolejka.push(i);
        /*                      SORTOWANIE TOPOLOGICZNE             */
        unsigned int wynik[n];
        unsigned int *wsk=wynik;
        bool ok=true;
        while(!kolejka.empty())
        {
            *(wsk++)=kolejka.front();
            person &teraz=osoby[kolejka.front()];
            while(!teraz.out.empty())
            {
                --osoby[teraz.out.front()].in;
                if(osoby[teraz.out.front()].in==0)
                    kolejka.push(teraz.out.front());
                teraz.out.pop();
            }
            kolejka.pop();
        }
        for(unsigned int i=1;i<=n;++i)
            if(osoby[i].in)
                ok=false;
        if(ok)
        {
            puts("OK");
            for(unsigned int *tmp=wynik;tmp!=wsk;++tmp)
                printf("%u ",*tmp);
            putchar('\n');
        }
        else
            puts("CYKL");
        /*                      SORTOWANIE TOPOLOGICZNE             */
    }
    return 0;
}
