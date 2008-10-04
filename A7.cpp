#include <cstdio>
#include <cstdlib>

class bigBinInteger
{
    char *wsk,*obj;
    static char tmp;
    int size;

    public:

    bigBinInteger() : size(0)
    {
        wsk=new char[8002];
        obj=wsk+sizeof(char)*4000;
    }

    ~bigBinInteger()
    {
        delete [] wsk;
        wsk=obj=0;
    }

    bigBinInteger & operator>>(const unsigned int & ile)
    {
        size-=ile;
        if(size<0)
        size=0;
    }

    bool isEmpty()
    {
        if(size)
        return false;
        return true;
    }

    void getInteger()
    {
        obj=wsk+sizeof(char)*4000;
        char *target=obj;
        size=0;
        for(char tmp=getchar();tmp=='1' || tmp=='0';tmp=getchar())
        {
            *(target++)=tmp-'0';
            ++size;
        }

        deleteZeros();
    }

    void putInteger()
    {
        char *from=obj;
        unsigned int i=size;
        while(i--)
        {
            putchar((*(from++))+'0');
        }
    }

    void deleteZeros()
    {
        while(*obj==0 && size)
        {
            --size;
            ++obj;
        }
    }

    void atomSubstraction(char* od_czego,char co)
    {
        if(co==1)
        {
            if(*od_czego==1)
            *od_czego=0;
            else
            {
                *od_czego=1;
                atomSubstraction(od_czego-1,co);
            }
        }
    }

    bigBinInteger & operator-=(const bigBinInteger & co)
    {
        char *wsk1,*wsk2;
        wsk1=obj+size-1;
        wsk2=co.obj+co.size-1;
        for(unsigned int i=size;i>0;--i)
        {
            atomSubstraction(wsk1,*wsk2);
            --wsk1;--wsk2;
        }
        deleteZeros();
        return *this;
    }

    bigBinInteger(const bigBinInteger & co)
    {
        if(wsk)
        delete [] wsk;
        wsk=new char[8002];
        obj=wsk+sizeof(char)*4000;
        for(unsigned int i=0;i<size;++i)
        {
            obj[i]=co.obj[i];
        }
        size=co.size;
    }

    bigBinInteger & operator-(const bigBinInteger & co)
    {
        bigBinInteger *temp=new bigBinInteger();
        *temp=*this;
        *temp-=co;

        return *temp;
    }

    bool isPair()
    {
        return obj[size-1]-1;
    }

    bool operator<(const bigBinInteger & co)
    {
        if(size<co.size) return true;
        if(size>co.size) return false;

        for(unsigned int i=0;i<size;++i)
        {
            if(obj[i]>co.obj[i]) return false;
            if(obj[i]<co.obj[i]) return true;
        }
        return false;
    }

    bigBinInteger & operator<<(unsigned int ile)
    {
        for(unsigned int i=0;i<ile;++i)
        obj[size+i]=0;
        size+=ile;
    }
};


int main()
{
    unsigned int z;
    scanf("%u",&z);
    getchar();
    while(z--)
    {{
        bigBinInteger a,b;
        unsigned int k;
        a.getInteger();
        b.getInteger();

        if(a.isEmpty())
        {
            b.putInteger();
            return 0;
        }
        if(b.isEmpty())
        {
            a.putInteger();
            return 0;
        }

        for(k=0;a.isPair() && b.isPair();++k)
        {
            a>>1;
            b>>1;
        }

        do
        {
            if(a.isEmpty())
            {
                a=b;
                break;
            }

            while(a.isPair()) a>>1;
            while(b.isPair()) b>>1;
            if(a<b)
            {
                bigBinInteger r;
                r=(b-a)>>1;
                b=a;
                a=r;
            }
            else
            {
                a-=b;
                a>>1;
            }
        } while(!b.isEmpty());

        if(k) a<<k;

        a.putInteger();
        putchar('\n');
    }}

    return 0;
}
