#include <cstdio>

class bigBinInteger
{
    char *wsk,*obj;     /*  wsk to cała dostępna przestrzeń, obj to początek liczby w przestrzeni wsk.
                            Wykorzystuje to swobodnego przesuwania bitowego. */
    int size;           //  Długość liczby w zapisie binarnym

    /*  Najbardziej znaczący bit znajduje się w *obj,
        najmniej znaczący w obj[size-1] */

    public:

    bigBinInteger() : size(0)
    {
        wsk=new char[8002];
        obj=wsk+sizeof(char)*4000;
    }

    bigBinInteger(const bigBinInteger & co)
    {
        wsk=new char[8002];
        obj=wsk+sizeof(char)*4000;
        for(unsigned int i=0;i<co.size;++i)
        {
            obj[i]=co.obj[i];
        }
        size=co.size;
    }

    bigBinInteger & operator=(const bigBinInteger & co)
    {
        obj=wsk+sizeof(char)*4000;
        for(unsigned int i=0;i<co.size;++i)
        {
            obj[i]=co.obj[i];
        }
        size=co.size;

        return *this;
    }

    bigBinInteger & operator>>(const unsigned int & ile)
    {
        size-=ile;  //  Czyli obcinam końcówke (najmniej znaczące bity)
        if(size<0)
        size=0;
    }

    bigBinInteger & operator<<(unsigned int ile)
    {
        for(unsigned int i=0;i<ile;++i)
        obj[size+i]=0;  //  Zeruje przestrzeń, którą zajmą najmniej zanczące bity
        size+=ile;
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

void operator-=(const bigBinInteger & co)
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
    }

    bigBinInteger operator-(const bigBinInteger & co)
    {
        bigBinInteger temp;
        temp=*this;
        temp-=co;

        return temp;
    }

    bool isEmpty()
    {
        if(size)
        return false;
        return true;
    }

    void getInteger()   //  Pobieram liczbę w zapisie binarnym
    {
        obj=wsk+sizeof(char)*4000;  //  Powracam do początkowego ustawienia wskaźnika w przestrzeni
        char *target=obj;           //  Wskaźnik pomocniczy
        size=0;                     //  Zeruje długość liczby
        for(char tmp=getchar();tmp=='1' || tmp=='0';tmp=getchar())
        {
            *(target++)=tmp-'0';
            ++size;
        }

        deleteZeros();
    }

    void putInteger()   //  Wyświetlam liczbę w zapisie binarnym
    {
        char *from=obj;
        unsigned int i=size;
        while(i--)
        {
            putchar((*(from++))+'0');
        }
    }

    void deleteZeros()  //  Obcinam zera wiodące
    {
        while(*obj==0 && size)
        {
            --size;
            ++obj;
        }
    }

    void atomSubstraction(char* od_czego,char co)   //  Odejmuję od liczby potęgę dwójki (pojedyńczy bit)
    {
        if(co==1)
        {
            if(*od_czego==1)
            *od_czego=0;
            else
            {
                *od_czego=1;
                atomSubstraction(od_czego-1,co);    //  Rekurencyjnie w stronę bardziej znaczących bitów
            }
        }
    }

    bool isPair()   //  Czy liczba jest parzysta
    {
        return obj[size-1]-1;   //  Jeżeli tak, to 0-1=-1 || 0-1=0xffffffff w zależności czy char jest signed czy nie...
    }
};

bigBinInteger a,b,tmp;
unsigned int r;

int main()
{
    unsigned int z; //  Zestawy danych
    scanf("%u",&z);
    getchar();      //  bigBinInteger::getInteger() jest bardzo wrażliwa
    while(z--)
    {
        a.getInteger();
        b.getInteger();

        if(a.isEmpty())
        {
            b.putInteger();
	    putchar('\n');
            continue;
        }
        if(b.isEmpty())
        {
            a.putInteger();
	    putchar('\n');
	    continue;
        }

        for(r=0;a.isPair() && b.isPair();++r)
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
                tmp=b;
                tmp-=a;
                tmp>>1;
                b=a;
                a=tmp;
            }
            else
            {
                a-=b;
                a>>1;
            }
        } while(!b.isEmpty());

        if(r) a<<r;

        a.putInteger();
        putchar('\n');
    }

    return 0;
}
