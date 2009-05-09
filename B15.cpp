#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

struct edge
{
    int     v;
    int     c;
    int     f;

    edge(int vv,int cc,int ff) : v(vv),c(cc),f(ff) {}
};

typedef vector<edge> ve;
const int           inf=2000000000;

int                 f;
ve                  *G;
bool                *v1;
int                 n;
int                 m;

bool dfs(int u)
{
    if(u==2*n+1)
    {
        //printf("Mam cel\n");
        return true;
    }
    if(!v1[u] || u==0)
    {
        //printf("Wchodzę do %d\n",u);
        v1[u]=true;
        for(ve::iterator i=G[u].begin(),e=G[u].end();i!=e;++i)
        {
            if((i->c)-(i->f)>0)
            {
                int &v=i->v;
                //printf("Wybrałem krawędź %d->%d c: %d f: %d cf: %d\n",u,i->v,i->c,i->f,(i->c)-(i->f));
                if(dfs(v))
                {
                    ++(i->f);
                    for(ve::iterator j=G[v].begin(),ej=G[v].end();j!=ej;++j)
                    {
                        if(j->v==u)
                        {
                            --(j->f);
                            break;
                        }
                    }
                    return true;
                }
            }
            //else
                //printf("Pomijam %d->%d c: %d f: %d cf: %d\n",u,i->v,i->c,i->f,i->c-i->f);
        }
        return false;
    }
    return false;
}

int main()
{
    int         z;
    int         u;
    int         v;
    scanf("%d",&z);
    while(z--)
    {
        scanf("%d%d",&n,&m);
        G=new ve[2*n+2];
        v1=new bool[2*n+1];
        memset(v1,0,2*n+1);

        f=-1;

        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            if(!v1[u])
            {
                G[0].push_back(edge(u,1,0));
                v1[u]=true;
            }
            G[u].push_back(edge(n+v,1,0));
            if(!v1[n+v])
            {
                G[n+v].push_back(edge(2*n+1,1,0));
                v1[n+v]=true;
            }
        }

        for(int i=0;i<=2*n+1;++i)
        {
            bool ok;
            int     &u=i;
            for(ve::iterator j=G[u].begin(),e=G[u].end();j!=e;++j)
            {
                int &v=j->v;
                ok=false;
                for(ve::iterator k=G[v].begin(),ek=G[v].end();k!=ek;++k)
                {
                    if(ok=(k->v==u))
                        break;
                }
                if(!ok)
                {
                    G[v].push_back(edge(u,0,0));
                }
            }
        }

        do
        {
            memset(v1,0,2*n+1);
            ++f;
        } while(dfs(0));

        printf("%d\n",n-f);

        delete [] v1;
        delete [] G;
    }
    return 0;
}
