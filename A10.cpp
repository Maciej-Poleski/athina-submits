#include <cstdio>
#include <algorithm>

template <class T>
inline T min(T a,T b)
{
    if(a<b)
        return a;
    return b;
}

template <class T>
inline T max(T a,T b)
{
    if(a<b)
        return b;
    return a;
}

/*template <class T>
void swap(T &l,T &p)
{
    T tmp=l;
    l=p;
    p=tmp;
}*/

struct kartez
{
    int x,y;
    
    bool operator<(const kartez &o) const
    {
        if(x<o.x or (x==o.x and y<o.y))
            return true;
        return false;
    }
    
    bool operator==(const kartez &o) const
    {
        if(x==o.x and y==o.y)
            return true;
        return false;
    }
    
    long long operator-(const kartez &o) const
    {
        unsigned long long e1=(max(x,o.x)-min(x,o.x));
        unsigned long long e2=(max(y,o.y)-min(y,o.y));
        e1*=e1;
        e2*=e2;
        return e1+e2; 
    }
};

bool sorty(kartez a,kartez b)
{
    if(a.y<b.y or (a.y==b.y and a.x<b.x))
        return true;
    return false;
}

kartez *x;
unsigned int n;

long long find_minimum(unsigned int begin,unsigned int end)
{
    unsigned int size=end-begin;
    if(size>3)
    {
        unsigned int s=(end+begin)/2;
        //unsigned char nieparzysta=(end-begin)&1;
        long long a,b;
        kartez *yp,ys,*ypi;
        kartez *we=x+end;
        kartez *w1=x+begin;
        //yli=yl=new kartez [size/2];
        //ypi=yp=new kartez [size/2+nieparzysta];
        ys=x[s];
        /*for(unsigned int i=0;i<size;++i)
        {
            if(y[i]<ys)
            {
                *(yli++)=y[i];
            }
            else
            {
                *(ypi++)=y[i];
            }
        }*//*
        printf("Strona lewa p�aszczyzny:\n");
        for(unsigned int i=0;yl+i!=yli;++i)
        {
            printf("%d %d\n",yl[i].x,yl[i].y);
        }
        printf("Strona prawa p�aszczyzny:\n");
        for(unsigned int i=0;yp+i!=ypi;++i)
        {
            printf("%d %d\n",yp[i].x,yp[i].y);
        }
        printf("Koniec\n");*/
        
        a=find_minimum(begin,s);
        b=find_minimum(s,end);
        
        ypi=yp=new kartez [size];
        
        {
            kartez *w2=x+s;
            kartez *ws=x+s;
            
            while(w1!=ws and w2!=we)
            {
                if(sorty(*w1,*w2))
                {
                    *(ypi++)=*(w1++);
                }
                else
                {
                    *(ypi++)=*(w2++);
                }
            }
            
            while(w1!=ws)
            {
                *(ypi++)=*(w1++);
            }
            
            while(w2!=we)
            {
                *(ypi++)=*(w2++);
            }
            
            for(w1=x+begin,ypi=yp;w1!=we;)
            {
                *(w1++)=*(ypi++);
            }
        }
        delete [] yp;
        
        //printf("Lewo: %lld | Prawo: %lld\n",a,b);
        
        //delete [] yl;
        //delete [] yp;
        
        a>b?a=b:false;
        
        ypi=yp=new kartez [n];
        
        for(w1=x+begin;w1!=we;++w1)
        {
            if(static_cast<long long>(w1->x)>static_cast<long long>(ys.x)-a and static_cast<long long>(w1->x)<static_cast<long long>(ys.x)+a)
            {
                *(ypi++)=*w1;
            }
        }
        
        /*printf("D�ugo�� Yp: %u | Zawarto�� Yp:\n",ypi-yp);
        for(unsigned int i=0;yp+i<ypi;++i)
        {
            printf("%d %d\n",yp[i].x,yp[i].y);
        }
        printf("Koniec Yp\n");*/
        
        for(unsigned int i=0;yp+i<ypi;++i)
        {
            for(unsigned int j=1;j<8 and yp+i+j<ypi;++j)
            {
                if(yp[i]-yp[i+j]<a)
                    a=yp[i]-yp[i+j];
            }
        }
        delete [] yp;
        
        //printf("Znaleziona najmniejsza odleg�o��: %lld\n",a);
        
        return a;
    }
    else
    {
        if(size==3)
        {
            long long wynik=x[begin]-x[begin+1],tm;
            tm=x[begin+1]-x[begin+2];
            if(wynik>tm)
                wynik=tm;
            tm=x[begin+2]-x[begin];
            if(wynik>tm)
                wynik=tm;
            std::sort(x+begin,x+end,sorty);
            return wynik;
        }
        else
        {
            std::sort(x+begin,x+end,sorty);
            return x[begin]-x[begin+1];
        }
    }
}

int main()
{
    unsigned int z=1;
    scanf("%u",&z);
    while(z--)
    {
        scanf("%u",&n);
        x=new kartez[n];
        for(kartez *wsk=x,*end=x+n;wsk!=end;++wsk)
        {
            scanf("%d%d",&wsk->x,&wsk->y);
        }/*
        for(unsigned int i=0;i<n;++i)
        {
            printf("%d %d\n",x[i].x,x[i].y);
        }
        for(unsigned int i=0;i<n;++i)
        {
            printf("%d %d\n",y[i].x,y[i].y);
        }*/
        std::sort(x,x+n);
        //{       /*  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!   */
           /* bool ok=false;
            for(unsigned int i=1;i<n;++i)
            {
                if(x[i-1]==x[i])
                {
                    puts("0");
                    ok=true;
                    break;
                }
            }
            if(ok)
            {
                continue;
                delete [] x;
            }
        }*/       /*  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!   */
        /*
        for(unsigned int i=0;i<n;++i)
        {
            printf("%d %d\n",x[i].x,x[i].y);
        }
        for(unsigned int i=0;i<n;++i)
        {
            printf("%d %d\n",y[i].x,y[i].y);
        }*/
        printf("%lld\n",find_minimum(0,n));
        delete [] x;
    }
    return 0;
}
