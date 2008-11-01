#include <cstdio>
#include <queue>
using namespace std;

unsigned int zero=0;

/*template<class T>
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
*/
/*template<class T>
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
    unsigned int s;

    public:

    queue() : begin(0),end(0),s(0) {}

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
        ++s;
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
            --s;
        }
        else
            printf("Usuwam nieistniej�cy obiekt!\n");
    }
    T &front()
    {
        return begin->obj;
    }

    bool empty()
    {
        if(begin)
        return false;
        return true;
    }
    unsigned int size()
    {
        return s;
    }
};*/

struct kartez
{
    unsigned int x,y;
    kartez(unsigned int q,unsigned int w) :x(q),y(w) {}
    kartez() {}
};

unsigned int macierz[2000][2000];
queue<kartez> kolejka;
unsigned int n,m;

void bfs(unsigned int l=0)
{
    while(!kolejka.empty())
    {
        unsigned int size=kolejka.size();
        //printf("Rozmiar kolejki: %u\n",size);
        for(unsigned int i=0;i<size;++i)
        {
            unsigned int &x=kolejka.front().x;
            unsigned int &y=kolejka.front().y;

            if(x>0)
            if(macierz[x-1][y]>(l+1))
            {
                macierz[x-1][y]=l+1;
                kolejka.push(kartez(x-1,y));
            }
            if(x<n-1)
            if(macierz[x+1][y]>(l+1))
            {
                macierz[x+1][y]=l+1;
                kolejka.push(kartez(x+1,y));
            }
            if(y<m-1)
            if(macierz[x][y+1]>(l+1))
            {
                macierz[x][y+1]=l+1;
                kolejka.push(kartez(x,y+1));
            }
            if(y>0)
            if(macierz[x][y-1]>(l+1))
            {
                macierz[x][y-1]=l+1;
                kolejka.push(kartez(x,y-1));
            }

            //printf("%u\n",macierz(x,y));

            kolejka.pop();
        }
        ++l;
    }
}


int main()
{
    unsigned int z;
    scanf("%u",&z);
    while(z--)
    {
    scanf("%u%u",&n,&m);
    for(unsigned int i=0;i<n;++i)
    {
        getchar();
        for(unsigned int j=0;j<m;++j)
        {
            macierz[i][j]=getchar()-'1';
            if(macierz[i][j]==0)
                kolejka.push(kartez(i,j));
        }
    }
    bfs();

    for(unsigned int i=0;i<n;++i)
    {
        for(unsigned int j=0;j<m;++j)
        {
            printf("%u ",macierz[i][j]);
        }
        putchar('\n');
    }
    }
    return 0;
}
