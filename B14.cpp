#include <cstdio>
#include <list>
#include <algorithm>

using namespace std;

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

const int   MAXINT = 2147483647;
bool        S[501];
int         n,fmax;
int         C[501][501], F[501][501];
int         p[501], cfp[501];
queue<int>   q;

inline void dfs1(int nn)
{
    if(!S[nn])
    {
        S[nn]=true;
        for(int k=1;k<=n;++k)
        {
            if((C[nn][k]==1 && F[nn][k]==0) || (C[k][nn]==1 && F[k][nn]==1))
            {
                //printf("%d->%d\n",nn,k);
                dfs1(k);
            }
        }
    }
}

inline void test()
{
    for(int ii=1;ii<=n;++ii)
    {
        if(S[ii])
        {
            for(int jj=1;jj<=n;++jj)
            {
                if(C[ii][jj]==1 && S[jj]==false)
                {
                    printf("%d %d\n",ii,jj);
                    if((--fmax)==0)
                        return;
                }
            }
        }
    }
}

int main()
{
    int z;
    scanf("%d",&z);
    while(z--)
    {
        int m,s,t,cp,x,y,esc,i,j;
        scanf("%d%d%d%d",&n,&m,&s,&t);

        for(i=0;i<=n;++i)
            S[i]=false;

  for(i = 1; i <= n; i++)
    for(j = 1; j <= n; j++) F[i][j] = C[i][j] = 0;

  for(i = 1; i <= m; i++)
  {
    scanf("%d%d",&x,&y);
    C[x][y] = 1;
  }

  for(int i=1;i<=n;++i)
      C[i][i]=0;

  fmax = 0;

  do
  {

    for(i = 1; i <= n; i++) p[i] = 0;
    p[s] = -1;
    cfp[s] = MAXINT;
    q.clear(); q.push(s);
    esc = 0;
    while(!q.empty())
    {
      x = q.front(); q.pop();
      for(y = 1; y <= n; y++)
      {
        cp = C[x][y] - F[x][y];
        if(cp && !p[y])
        {
          p[y] = x;
          cfp[y] = cfp[x] > cp ? cp : cfp[x];
          if(y == t)
          {
             fmax += cfp[t];
             while(y != s)
             {
               x = p[y];
               F[x][y] += cfp[t];
               F[y][x] -= cfp[t];
               y = x;
             }
             esc = 1; break;

          }
          q.push(y);

        }

      }
      if(esc) break;

    }
    if(!esc) break;

  } while(true);

  /*for(x = 1; x <= n; x++)
    for(y = 1; y <= n; y++)
      if(C[x][y])
          printf("%d -> %d %d/%d\n",x,y,F[x][y],C[x][y]);*/

  printf("%d\n",fmax);
      dfs1(s);

      /*for(int i=1;i<=n;++i)
          if(S[i])
              printf("%d ",i);
          putchar('\n');*/

    S[s]=true;
    test();
    }

    return 0;
}
// I Liceum Ogólnokształcące
// im. K. Brodzińskiego
// w Tarnowie
//--------------------------
// Koło informatyczne 2006/7
//--------------------------
// P029 Maksymalny przepływ
// Wersja z macierzami sąsiedztwa
