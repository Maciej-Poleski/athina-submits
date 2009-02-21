#include <cstdio>
#include <vector>

using namespace std;

struct  node
{
    int     v;
    int     p;
};

int         *K;
vector<int> *graf;
node        *queue;

int         *in;
int         *low;

int         n;
int         m;

int         t;
int         r;
bool        ok;

void dfs(int u,int p)
{
    //printf("DFS %d %d\n",u,p);
    K[u]=0;
    queue[t].v=u;
    queue[t].p=p;
    if(p==1)
        ++r;
    in[u]=t++;
    low[u]=in[u];
    for(vector<int>::iterator i=graf[u].begin(),e=graf[u].end();i!=e;++i)
    {
        int &w=*i;
        //printf("w: %d\n",w);
        if(w!=p)
        {
            if(K[w]==-1)
            {
                dfs(w,u);
                low[u]=min(low[u],low[w]);
                if(low[w]>=in[u] && u!=1)
                {
                    K[u]=4;
                    ok=false;
                }
            }
            else
                low[u]=min(low[u],in[w]);
        }
    }
}

inline int select(int a,int b)
{
    int i;
    bool t[4];
    for(i=1;i<=3;++i)
        t[i]=false;
    t[a]=true;
    t[b]=true;
    for(i=1;i<=3 && t[i];++i);
    return i;
}

int main()
{
    int     z;
    int     a;
    int     b;
    scanf("%d",&z);
    while(z--)
    {
        scanf("%d%d",&n,&m);
        
        K=new int[n+1];
        graf=new vector<int>[n+1];
        queue=new node[n+1];

        for(int i=1;i<=n;++i)
            K[i]=-1;
        
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            graf[a].push_back(b);
            graf[b].push_back(a);
        }

        in=new int[n+1];
        low=new int[n+1];

        ok=true;
        r=0;
        t=1;

        dfs(1,0);

        if(ok && r==1)
        {
            printf("TAK");
            printf(" %d",K[1]=1);
            for(int i=2;i<=n;++i)
            {
                K[queue[i].v]=select(K[queue[i].p],K[queue[low[queue[i].v]].v]);
            }
            for(int i=2;i<=n;++i)
            {
                printf(" %d",K[i]);
            }
            putchar('\n');
        }
        else
        {
            puts("NIE");
        }

        //printf("OK: %d, root: %d\n",ok,r);

        /*printf("queue: ");
        for(int i=1;i<=n;++i)
            printf("(%d %d) ",queue[i].v,queue[i].p);
        putchar('\n');
        printf("low:");
        for(int i=1;i<=n;++i)
            printf(" %d",low[i]);
        putchar('\n');*/

        delete [] graf;
        delete [] in;
        delete [] low;
        delete [] queue;
        delete [] K;
    }
    return 0;
}
