#include <cstdio>
#include <algorithm>
using namespace std;

unsigned int mpow2(unsigned int n)
{
    /*bool o=false;
    unsigned int size=0;
    while(n>1)
    {
        if(n&1)
            o=true;
        n>>=1;
        ++size;
    }
    if(o)
        return 1<<size+1;
    return 1<<size;*/
    unsigned int wynik=1;
    while(wynik<n)
        wynik<<=1;
    return wynik;
}

struct kartez
{
    int x,y;
    
    bool operator<(const kartez &o) const
    {
        if(x<o.x)
            return true;
        return false;
    }
    
    bool operator==(const kartez &o) const
    {
        if(x==o.x)
            return true;
        return false;
    }
};

struct sumTree
{
    unsigned int *tab;
    unsigned int size,tabSize;
    
    void add1(unsigned int n)
    {
        while(n)
        {
            ++tab[n];
            n=(n-1)>>1;
        }
        ++tab[0];
    }
    
    unsigned int add(unsigned int begin,unsigned int end)
    {
        unsigned int l=tab[begin],p=tab[end];
        while(begin+1!=end)
        {
            if(begin&1)
            {
                l+=tab[begin+1];
                begin>>=1;
            }
            else
            {
                begin=(begin-1)>>1;
            }
            if(end&1)
            {
                end>>=1;
            }
            else
            {
                p+=tab[end-1];
                end=(end-1)>>1;
            }
        }
        return l+p;
    }
    
    public:
    
    sumTree(unsigned int n) : size(mpow2(n)),tabSize(2*size-1)
    {
        tab=new unsigned int [tabSize];
        for(unsigned int *wsk=tab,*end=tab+tabSize;wsk!=end;++wsk)
            *wsk=0;
    }
    
    ~sumTree()
    {
        delete [] tab;
    }
    
    void inc(unsigned int n)
    {
        add1(size+n-1);
    }
    
    unsigned int suma(unsigned int begin,unsigned int end)
    {
        if(begin==end)
            return tab[size+begin-1];
        if(begin>end)
            return 0;
        return add(size+begin-1,size+end-1);
    }
};

struct obiekt
{
    kartez wsp;
    enum
    {
        stadionB=-1,
        drzewo,
        stadionE
    }typ;
    
    bool operator<(const obiekt &o) const
    {
        if(wsp<o.wsp or (wsp==o.wsp and typ<o.typ))
            return true;
        return false;
    }
};

struct stadiony
{
    int y1,y2;
    unsigned int suma;
};

sumTree *drzewo;
obiekt *stuff;
stadiony *stadion;
int *y;
unsigned int n,m,size,sizey;

int main()
{
    /*sumTree drzewo(8);
    drzewo.inc(0);
    drzewo.inc(4);
    for(unsigned int i=0;i<drzewo.tabSize;++i)
    {
        printf("%u ",drzewo.tab[i]);
    }
    putchar('\n');
    printf("%u\n",drzewo.suma(1,7));*/
    /*obiekt a,b;
    kartez x,y;
    x.x=x.y=1;
    y.x=y.y=2;
    a.wsp=x;
    b.wsp=y;
    a.typ=a.stadionE;
    b.typ=b.drzewo;
    printf("%u\n",a<b);*/
    unsigned int z;
    scanf("%u",&z);
    while(z--)
    {
        scanf("%u%u",&n,&m);
        size=n+m*2;
        stadion=new stadiony[m];
        {
            obiekt *wsk=stuff=new obiekt[size];
            unsigned int i=0;
            for(;i<n;++i,++wsk)
            {
                scanf("%d%d",&wsk->wsp.x,&wsk->wsp.y);
                wsk->typ=obiekt::drzewo;
            }
            i=0;
            stadiony *w3=stadion;
            for(obiekt *w2=wsk+1;i<m;++i,wsk+=2,w2+=2,++w3)
            {
                scanf("%d%d%d%d",&wsk->wsp.x,&w2->wsp.x,&w3->y1,&w3->y2);
                wsk->typ=obiekt::stadionB;
                w2->typ=obiekt::stadionE;
                wsk->wsp.y=w2->wsp.y=i;
            }
        }
        {
            int *wsk=y=new int[n];
            obiekt *end=stuff+n;
            for(obiekt *w2=stuff;w2!=end;++w2)
            {
                *(wsk++)=w2->wsp.y;
            }
            sort(y,wsk);
            sizey=unique(y,wsk)-y;
        }/*
        for(unsigned int i=0;i<sizey;++i)
        {
            printf("%d ",y[i]);
        }
        putchar('\n');*/
        sort(stuff,stuff+size);/*
        for(unsigned int i=0;i<size;++i)
        {
            if(stuff[i].typ==obiekt::drzewo)
            {
                printf("Drzewo: %d %d\n",stuff[i].wsp.x,stuff[i].wsp.y);
            }
            else if(stuff[i].typ==obiekt::stadionB)
            {
                printf("Początek stadionu %d: x: %d | y1: %d | y2: %d\n",stuff[i].wsp.y,stuff[i].wsp.x,stadion[stuff[i].wsp.y].y1,stadion[stuff[i].wsp.y].y2);
            }
            else
            {
                printf("Koniec stadionu %d: x: %d | y1: %d | y2: %d\n",stuff[i].wsp.y,stuff[i].wsp.x,stadion[stuff[i].wsp.y].y1,stadion[stuff[i].wsp.y].y2);
            }
        }*/
        //puts("a");
        drzewo=new sumTree(sizey);
        {
            stadiony *nr;
            int *w=y+sizey;
            for(obiekt *wsk=stuff,*end=stuff+size;wsk!=end;++wsk)
            {
                switch(wsk->typ)
                {
                    case obiekt::stadionB:
                        nr=stadion+wsk->wsp.y;
                        nr->suma=drzewo->suma(lower_bound(y,w,nr->y1)-y,upper_bound(y,w,nr->y2)-y-1);
                        //printf("Początek\n");
                        break;
                    case obiekt::stadionE:
                        nr=stadion+wsk->wsp.y;
                        nr->suma=drzewo->suma(lower_bound(y,w,nr->y1)-y,upper_bound(y,w,nr->y2)-y-1)-nr->suma;
                        //printf("Koniec\n");
                        break;
                    default:
                        drzewo->inc(lower_bound(y,w,wsk->wsp.y)-y);
                        break;
                }/*
                for(unsigned int i=0;i<drzewo->tabSize;++i)
                {
                    printf("%u ",drzewo->tab[i]);
                }
                putchar('\n');*/
            }
        }
        //puts("b");
        //puts("c");
        delete [] stuff;
        delete drzewo;
        delete [] y;
        for(stadiony *wsk=stadion,*end=stadion+m;wsk!=end;++wsk)
        {
            printf("%u\n",wsk->suma);
        }
        delete [] stadion;
    }/*
    int tab[]={-2,-1,0,2,5,6,9};
    const unsigned int size=sizeof(tab)/sizeof(int);
    printf("%u %u\n",lower_bound(tab,tab+size,3)-tab,upper_bound(tab,tab+size,99)-tab-1);*/
    return 0;
}
