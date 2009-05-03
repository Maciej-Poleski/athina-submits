#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>

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

struct edge
{
    int     v;
    int     c;
    int     f;

    edge(int vv,int cc,int ff) : v(vv),c(cc),f(ff) {}
};

typedef queue<int>   qi;
typedef vector<edge> ve;

const int           inf=2000000000;
int                 f;
ve                  *G;
bool                *S;
bool                *v2;

void dfs(int n)
{
    if(!S[n])
    {
        S[n]=true;
        //printf("%d ",n);
        for(ve::iterator i=G[n].begin(),e=G[n].end();i!=e;++i)
            if((i->c)-(i->f)==1)
                dfs(i->v);
    }
};

void test(int n)
{
    if(!v2[n])
    {
        v2[n]=true;
        for(ve::iterator i=G[n].begin(),e=G[n].end();i!=e;++i)
        {
            if(i->c==0)
                continue;
            if(!S[i->v])
            {
                printf("%d %d\n",n,i->v);
                --f;
            }
            else
            {
                //printf("%d->%d\n",n,i->v);
                test(i->v);
            }
            if(f==0)
            {
                break;
            }
        }
    }
}

int main()
{
    int             z;
    scanf("%d",&z);
    while(z--)
    {
        int         n;
        int         m;
        int         s;
        int         t;
        int         u;
        int         v;
        bool        ok;
        scanf("%d%d%d%d",&n,&m,&s,&t);

        f=0;
        G=new ve[n+1];
        S=new bool[n+1];
        v2=new bool[n+1];
        
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            G[u].push_back(edge(v,1,0));
        }

        for(int i=0;i<=n;++i)
        {
            S[i]=v2[i]=false;
        }

        for(int i=1;i<=n;++i)
        {
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

        for(;;)
        {
            int     p[2][n+1];
            int     cfp[n+1];
            qi      q;

            for(int i=0;i<=n;++i)
                p[0][i]=0;

            p[s][0]=-1;
            cfp[s]=inf;
            q.push(s);
            ok=false;

            while(!q.empty())
            {
                int u=q.front();
                q.pop();

                for(int i=0,e=G[u].size();i<e;++i)
                {
                    int &v=G[u][i].v;
                    int tmp=G[u][i].c-G[u][i].f;

                    if(tmp && (p[0][v]==0))
                    {
                        p[0][v]=u;
                        p[1][v]=i;

                        cfp[v]=min(tmp,cfp[u]);

                        if(v==t)
                        {
                            f+=cfp[t];
                            int v=t;

                            while(v!=s)
                            {
                                int u=p[0][v];

                                G[u][p[1][v]].f+=cfp[t];

                                for(ve::iterator q=G[v].begin(),e=G[v].end();q!=e;++q)
                                    if(q->v==u)
                                    {
                                        q->f-=cfp[t];
                                        break;
                                    }

                                v=u;
                            }
                            ok=true;
                            break;
                        }
                        q.push(v);
                    }
                }
                if(ok)
                    break;
            }
            if(!ok)
                break;
        }

        printf("%d\n",f);

        dfs(s);
        //putchar('\n');
        test(s);

        delete [] G;
        delete [] S;
        delete [] v2;
    }
    return 0;
}
