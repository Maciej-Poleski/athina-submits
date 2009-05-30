#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

struct info
{
    int         v;
    int         h;

    info(int vv,int hh) : v(vv),h(hh) {}
    info() {}

    bool operator<(const info &o) const
    {
        return h<o.h;
    }
};

struct node
{
    vector<int> d;
    int         h;

    node() : h(-1) {}
};

node            *G;
int             h;
int             I;
info            *t;
int             *p;
int             tt;

void dfs(int n)
{
    t[I++]=info(n,h++);
    if(G[n].h==-1)
        G[n].h=I-1;
    
    for(vector<int>::iterator i=G[n].d.begin(),e=G[n].d.end();i!=e;++i)
    {
        dfs(*i);
        t[I++]=info(n,h-1);
    }
    --h;
    return;
}

int main()
{
    int         z;
    scanf("%d",&z);
    while(z--)
    {
        int     n;
        int     m;
        int     x;
        scanf("%d",&n);

        const int tt=static_cast<int>(ceil(log10(2*n-1)/log10(2)));

        G=new node[n];

        for(int i=1;i<n;++i)
        {
            scanf("%d",&x);
            G[x].d.push_back(i);
        }

        t=new info[n<<1];

        h=0;
        I=0;
        dfs(0);

        info    d[tt][2*n-1];

        for(int i=0;i<n*2-1;++i)
            d[0][i]=t[i];

        /*for(int i=0;i<n*2-1;++i)
            printf("%d %d\n",d[0][i].v,d[0][i].h);*/

        delete [] t;
        
        p=new int[tt+1];

        p[0]=1;
        for(int i=1;i<=tt;++i)
            p[i]=p[i-1]<<1;

        for(int i=1;i<tt;++i)
        {
            for(int j=0;(j+p[i-1]<n*2-1);++j)
                d[i][j]=min(d[i-1][j],d[i-1][j+p[i-1]]);
        }

        /*for(int i=0;i<tt;++i)
        {
            for(int j=0;j<2*n && d[i][j].v>=0;++j)
                printf("%d %d | ",d[i][j].v,d[i][j].h);
            putchar('\n');
        }*/

        int     a;
        int     b;
        int     k;
        int     L;

        scanf("%d",&m);
        while(m--)
        {
            scanf("%d%d",&a,&b);
            a=G[a].h;
            b=G[b].h;
            if(b<a)
                swap(a,b);
            k=floor(log10(b-a+1)/log10(2));
            L=p[k];
            printf("%d\n",d[k][a]<d[k][b-L+1]?d[k][a].v:d[k][b-L+1].v);
        }
        delete [] p;
        delete [] G;
    }
    return 0;
}
