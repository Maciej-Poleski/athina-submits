#include <cstdio>
#include <cstdlib>
#include <ctime>

template<class T>
class list
{
    public:
        struct key
        {
            T obj;
            key *next;
        
            key() : next(0), obj() {}
            key(T &t) : next(0), obj(t) {}
            
        };
        class iterator
        {
            key *wsk;
            
            public:
            
            iterator() : wsk(0) {}
            iterator(key *w) : wsk(w) {}
            
            operator bool()
            {
                return wsk;
            }
            
            iterator &operator++()
            {
                wsk=wsk->next;
                return *this;
            }
            
            T& operator*()
            {
                return wsk->obj;
            }
        };
        
    private:
        
        key *beg;
        key *e;
        
    public:
        
        list() : beg(0), e(0) {}
        ~list()
        {
            while(!empty())
            {
                key *tmp=beg;
                beg=beg->next;
                delete tmp;
            }
            beg=e=0;
            
        }
        
        void push(T obj)
        {
            if(e)
            {
                key *tmp=new key(obj);
                e->next=tmp;
                e=tmp;
            }
            else
            {
                beg=e=new key(obj);
            }
        }
        
        bool empty()
        {
            return beg==0;
        }
        
        iterator begin()
        {
            return iterator(beg);
        }
        
        iterator end()
        {
            return iterator(e);
        }
};

template <class T>
struct node
{
    T obj;
    unsigned int parent;
    list<unsigned int> child;
    
    node() : parent(0),child() {}
};

struct pair
{
    unsigned int wej,wyj;
    
    pair() : wej(0), wyj(0) {}
};

list<unsigned int> *graf;
node<pair> *drzewo;
bool *odwiedzone;
unsigned int x,y;
unsigned int poziom;

void build_tree(unsigned int miasto)
{
    fflush(stdout);
    odwiedzone[miasto]=true;
    drzewo[miasto].obj.wej=poziom++;
    for(list<unsigned int>::iterator it=graf[miasto].begin();it;++it)
    {
        if(!odwiedzone[*it])
        {
            drzewo[*it].parent=miasto;
            drzewo[miasto].child.push(*it);
            build_tree(*it);
        }
    }
    drzewo[miasto].obj.wyj=poziom++;
    //putchar('\r');
    return;
}

bool in(pair w1,pair w2)    // Czy w1 zawiera się w w2
{
    if(w1.wej<w2.wej || w1.wyj>w2.wyj)
        return false;
    return true;
}

node<pair> * find_gparent(node<pair> *w1,node<pair> *w2)    // Znajdź przodka w1 i w2
{
    node<pair> *wynik=w1;
    
    while(!in(w2->obj,wynik->obj))
        wynik=drzewo+wynik->parent;
    
    return wynik;
}

void print(unsigned int poz)
{
    if(poz!=x)
        print(drzewo[poz].parent);
    printf("%u ",poz);
    return;
}

int main()
{
    srand(time(0));
    unsigned int z;
    scanf("%u",&z);
    while(z--)
    {
        unsigned int n,q;
        scanf("%u",&n);
        graf=new list<unsigned int> [n+1];
        drzewo=new node<pair> [n+1];
        odwiedzone=new bool[n+1];
        for(unsigned int i=0;i<=n;++i)
            odwiedzone[i]=false;
        for(unsigned int i=1;i<n;++i)
        {
            scanf("%u%u",&x,&y);
            graf[x].push(y);
            graf[y].push(x);
        }
        
        /*for(unsigned int i=1;i<=n;++i)
        {
            printf("Wierzchołek: %u |",i);
            for(list<unsigned int>::iterator it=graf[i].begin();it;++it)
                printf(" %u",*it);
            putchar('\n');
        }*/
        
        poziom=0;
        build_tree(rand()%n+1);
        
        delete [] graf;
        
        /*for(unsigned int i=1;i<=n;++i)
        {
            printf("Obieg %u | Zawartość: %u %u | Rodzic: %u | Dzieci: ",i,drzewo[i].obj.wej,drzewo[i].obj.wyj,drzewo[i].parent);
            for(list<unsigned int>::iterator it=drzewo[i].child.begin();it;++it)
            {
                printf(" %u",*it);
            }
            putchar('\n');
            fflush(stdout);
        }*/
        
        scanf("%u",&q);
        
        while(q--)
        {
            scanf("%u%u",&x,&y);
            node<pair> *gparent=find_gparent(drzewo+x,drzewo+y);
            //printf("Znaleziony ojciec to %u\n",gparent-drzewo);
            while(drzewo+x!=gparent)
            {
                printf("%u ",x);
                x=drzewo[x].parent;
            }
            
            x=gparent-drzewo;
            
            print(y);
            
            putchar('\n');
        }
        
        delete [] drzewo;
        delete [] odwiedzone;
    }
    return 0;
}
