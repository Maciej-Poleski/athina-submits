#include <cstdio>
#include <vector>

using namespace std;

struct node : public vector<int>
{
    //long long   v;
    int         p1;
    int         p2;
};

inline int mpow2(int n)
{
    int wynik=1;
    while(wynik<n)
        wynik<<=1;
    return wynik;
}

node            *G;
long long       *T;
int             size;
int             Tptr;

void dfs(int n,int p)
{
    //T[Tptr]=G[n].v;
    G[n].p1=Tptr++;
    for(vector<int>::iterator i=G[n].begin(),e=G[n].end();i!=e;++i)
        if(*i!=p)
            dfs(*i,n);
    //T[Tptr]=-G[n].v;
    G[n].p2=Tptr++;
}

int main()
{
    int         z;
    scanf("%d\n",&z);
    while(z--)
    {
        int     n;
        int     q;
        scanf("%d\n",&n);
        G=new node[n+1];
        T=new long long[(size=mpow2(n*2))*2];

        for(int i=1;i<n;++i)
        {
            int a;
            int b;
            scanf("%d %d\n",&a,&b);
            G[a].push_back(b);
            G[b].push_back(a);
        }

        Tptr=size;
        dfs(1,-1);

        for(int i=1;i<=n;++i)
        {
            scanf("%lld ",&T[G[i].p1]);
            T[G[i].p2]=-T[G[i].p1];
        }

        for(int i=size-1;i>0;--i)
            T[i]=T[i*2]+T[i*2+1];

        scanf("%d\n",&q);
        for(int i=0;i<q;++i)
        {
            char w;
            int t1;
            int t2;
            scanf("%c %d ",&w,&t1);

            switch(w)
            {
                case 'W':
                {
                    int a=size;
                    int b=G[t1].p1;
                    long long w=0;
                    while(a<=b)
                    {
                        int s=1;
                        int h=a;
                        for(;a+(s<<1)<=b;s<<=1,h>>=1);
                        w+=T[h];
                        a+=s;
                    }
                    printf("%lld\n",w);
                    break;
                }
                default:
                {
                    scanf("%d\n",&t2);
                    T[G[t1].p1]=t2;
                    for(int j=G[t1].p1>>1;j>0;j>>=1)
                        if(T[j]!=T[j<<1]+T[(j<<1)|1])
                            T[j]=T[j<<1]+T[(j<<1)|1];
                        else
                            break;
                    T[G[t1].p2]=-t2;
                    for(int j=G[t1].p2>>1;j>0;j>>=1)
                        if(T[j]!=T[j<<1]+T[(j<<1)|1])
                            T[j]=T[j<<1]+T[(j<<1)|1];
                        else
                            break;
                    break;
                }
            }
        }

        delete [] T;
        delete [] G;
    }
    return 0;
}
