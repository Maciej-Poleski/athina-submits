#include <cstdio>

template <class T>
inline T max(T a,T b)
{
    return a>b?a:b;
}

inline int mpow2(int n)
{
    int wynik=1;
    while(wynik<n)
        wynik<<=1;
    return wynik;
}

inline void ign()
{
    while(getchar()!='\n');
}

struct node
{
    long long   s;
    long long   v;
    long long   mp;
    long long   ms;

    node() : s(0),v(0),mp(0),ms(0) {}

    void app(long long a)
    {
        s=a;
        mp=ms=v=max(s,0ll);
    }
}*tree;

int         n;
long long   s;

inline void comp_tree(int q)
{
    tree[q].s=tree[q<<1].s+tree[(q<<1)|1].s;
    tree[q].mp=max(tree[q<<1].mp,tree[q<<1].s+tree[(q<<1)|1].mp);
    tree[q].ms=max(tree[(q<<1)|1].ms,tree[(q<<1)|1].s+tree[q<<1].ms);
    tree[q].v=max(tree[q<<1].v,tree[(q<<1)|1].v);
    tree[q].v=max(tree[q].v,tree[q<<1].ms+tree[(q<<1)|1].mp);
}

#ifdef dump_tree
inline void dump_node(int q)
{
    printf("<center><table border=1 cellspacing=0><tr><td>%d</td><td>%d</td></tr><tr><td>%d</td><td>%d</td></tr></table></center>",tree[q].s,tree[q].v,tree[q].mp,tree[q].ms);
}

inline void dump_tree()
{
    int i=1;
    printf("<table border=0>\n");
    for(int j=1;j<=s;j*=2)
    {
        printf("<tr>\n");
        for(int k=1;k<=j;++k)
        {
            printf("<td colspan=%d>",s/j);
            dump_node(i++);
            printf("</td>\n");
        }
        printf("</tr>\n");
    }
    printf("</table>\n");
}
#else
#define dump_node()
#define dump_tree()
#endif

inline node comp(node &a,node &b)
{
    node w;
    w.s=a.s+b.s;
    w.mp=max(a.mp,a.s+b.mp);
    w.ms=max(b.ms,b.s+a.ms);
    w.v=max(max(a.v,b.v),a.ms+b.mp);
    return w;
}

int main()
{
    int z;
    scanf("%d\n",&z);
    while(z--)
    {
        int     m;
        long long   t;
        long long   w;
        char    c;
        scanf("%d %d\n",&n,&m);
        s=mpow2(n);
        tree=new node[s<<1];
        
        for(int i=s;i<s+n;++i)
        {
            scanf("%lld ",&t);
            tree[i].app(t);
        }

        dump_tree();

        for(int i=s-1;i>0;--i)
            comp_tree(i);

        dump_tree();
        
        while(m--)
        {
            c=getchar();
            ign();

            switch(c)
            {
                case 'U':
                    scanf("%lld %lld\n",&t,&w);
                    t+=s-1;
                    tree[t].app(w);
                    t>>=1;
                    while(t!=0)
                    {
                        comp_tree(t);
                        t>>=1;
                    }
                    dump_tree();
                    break;
                default:
                    scanf("%lld %lld\n",&t,&w);
                    node e;
                    long long r=w-t;
                    --t;
                    --w;
                    t+=s;
                    w+=s;
                    ++r;

                    //printf("%d %d %d:",r,t,w);
                    while(r)
                    {
                        long long   i=1;
                        for(;(t&1)==0 && r-(i<<1)>=0;t>>=1,i<<=1);
                        //printf(" %d",t);
                        e=comp(e,tree[t]);
                        r-=i;
                        t=w-r+1;
                    }
                    //putchar('\n');
                    printf("%lld\n",e.v);
                    break;
            }
        }

        delete [] tree;
    }
}
