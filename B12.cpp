#include <cstdio>
#include <utility>
#include <queue>
#include <vector>
#define MP(x,y) make_pair((x),(y))

using namespace std;
using namespace rel_ops;

typedef pair<int,int> PII;

const int   inf=1050000000;

struct edge
{
    int     D;
    int     w;
    int     T;
    int     a;
    int     l;
    
    edge(int DD,int ww,int TT,int aa,int ll) : D(DD),w(ww),T(TT),a(aa),l(ll) {}
};

struct vertex
{
    int             r;
    vector<edge>    L;

    vertex() : r(inf) {}
};

vertex  *graf;
int		n;
int		m;

int main()
{
	int		z;
    int     S,D,w,T,a,l;
	scanf("%d",&z);
	while(z--)
	{
        scanf("%d%d",&n,&m);
        graf=new vertex[n+1];

        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d%d%d%d",&S,&D,&w,&T,&a,&l);
            graf[S].L.push_back(edge(D,w,T,a,l));
        }

        priority_queue<PII> kolejka;        // Kolejka wierzchołków

        graf[1].r=0;
        kolejka.push(MP(0,1));

        while(!kolejka.empty())
        {
            PII top=kolejka.top();
            int &n=top.second;
            int &r=top.first;
            kolejka.pop();

            if(graf[n].r!=r)                // Informacja w kopcu jest nieauktualna
                continue;
//          if(r==inf)                      // Najbliższy wierzchołek jest nieskończenie daleko - relaksacja jest niemożliwa
//              throw 2;                    // Nigdy nie powinno się wydarzyć

            for(vector<edge>::iterator i=graf[n].L.begin(),e=graf[n].L.end();i!=e;++i)
            {
                int x;
                
                if(i->T==0 || ((x=((r+i->T-i->a)%i->T))<i->l /*&& r>=i->a*/))
                {
                    if(graf[i->D].r>r+i->w)
                    {
                        graf[i->D].r=r+i->w;
                        kolejka.push(MP(graf[i->D].r,i->D));
                    }
                }
                /*else if(r<i->a)
                {
                    if(graf[i->D].r>i->a)
                    {
                        graf[i->D].r=i->a;
                        kolejka.push(MP(i->a,i->D));
                    }
                }*/
                else
                {
                    if(graf[i->D].r>r+i->w+i->T-x)
                    {
                        graf[i->D].r=r+i->w+i->T-x;
                        kolejka.push(MP(graf[i->D].r,i->D));
                    }
                }
            }
        }

        if(graf[n].r==inf)
            puts("NIE");
        else
            printf("%d\n",graf[n].r);

        delete [] graf;
    }
	return 0;
}
