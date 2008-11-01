#include <cstdio>

unsigned int zero=0;

template<class T>
class matrix
{
    unsigned int height,width;
    T *obj;

    public:

    matrix() : obj(0) {}

    void set(unsigned int x,unsigned int y)
    {
        height=x;
        width=y;
        unsigned int size=x*y;
        if(obj)
        delete [] obj;
        obj=new T[size];
        //for(unsigned int i=0;i<size;++i)
          //  obj[i]=0xffffffff;
    }

    T & operator()(int x,int y)
    {
        if(x<0 || y<0 || x>=height || y>=width)
            return zero;
        return obj[x*width+y];
    }
};

template<class T>
class queue
{
    class key
    {
        public:
        T obj;
        key *next,*back;

        key() : next(0),back(0) {}
    };
    key *begin,*end;
    unsigned int size;

    public:

    queue() : begin(0),end(0),size(0) {}

    void push(T obj)
    {
        if(end)
        {
            key *wsk=new key;
            wsk->next=end;
            end->back=wsk;
            wsk->obj=obj;
            end=wsk;
        }
        else
        {
            begin=end=new key;
            end->obj=obj;
            end->next=end->back=0;

        }
        ++size;
    }

    void pop()
    {
        if(begin)
        {
            if(begin!=end)
            {
                begin=begin->back;
                delete begin->next;
            }
            else
            {
                delete begin;
                begin=end=0;
            }
            --size;
        }
        else
            printf("Usuwam nieistniej�cy obiekt!\n");
    }
    T &top()
    {
        return begin->obj;
    }

    bool empty()
    {
        if(begin)
        return false;
        return true;
    }
    unsigned int s()
    {
        return size;
    }
};

struct kartez
{
    unsigned int x,y;
    kartez(unsigned int q,unsigned int w) :x(q),y(w) {}
    kartez() {}
};

matrix<unsigned int> macierz;
queue<kartez> kolejka;

void bfs(unsigned int l=0)
{
    if(!kolejka.empty())
    {
        unsigned int size=kolejka.s();
        //printf("Rozmiar kolejki: %u\n",size);
        for(unsigned int i=0;i<size;++i)
        {
            unsigned int &x=kolejka.top().x;
            unsigned int &y=kolejka.top().y;

          //  printf("%u %u: ",x,y);

            if(macierz(x-1,y)>(l+1))
            {
                macierz(x-1,y)=l+1;
                kolejka.push(kartez(x-1,y));
            }
            if(macierz(x+1,y)>(l+1))
            {
                macierz(x+1,y)=l+1;
                kolejka.push(kartez(x+1,y));
            }
            if(macierz(x,y+1)>(l+1))
            {
                macierz(x,y+1)=l+1;
                kolejka.push(kartez(x,y+1));
            }
            if(macierz(x,y-1)>(l+1))
            {
                macierz(x,y-1)=l+1;
                kolejka.push(kartez(x,y-1));
            }

            //printf("%u\n",macierz(x,y));

            kolejka.pop();
        }
        bfs(++l);
    }
}


int main()
{
    unsigned int z;
    scanf("%u",&z);
    while(z--)
    {
    unsigned int n,m;
    scanf("%u%u",&n,&m);
    macierz.set(n,m);
    for(unsigned int i=0;i<n;++i)
    {
        getchar();
        for(unsigned int j=0;j<m;++j)
        {
            macierz(i,j)=getchar()-'1';
            if(macierz(i,j)==0)
                kolejka.push(kartez(i,j));
        }
    }
    //while(!kolejka.empty())
    //{
     //   printf("%u %u\n",kolejka.top().x,kolejka.top().y);
      //  kolejka.pop();
    //}
    bfs();

    for(unsigned int i=0;i<n;++i)
    {
        for(unsigned int j=0;j<m;++j)
        {
            printf("%u ",macierz(i,j));
        }
        putchar('\n');
    }
    }
    return 0;
}
