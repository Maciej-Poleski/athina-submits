#include <cstdio>
#include <vector>

using namespace std;

const int   inf=1050000000;

inline int mpow2(int x)
{
    int wynik=1;
    while(wynik<x)
        wynik*=2;
    return wynik;
}

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
    vector<edge>    L;
};

vertex  *graf;
int     *drzewo;
int     size;
int     *wagi;
int		n;
int		m;

void rebuild(int x)
{
    x=(x+size-1)/2;
    while(x)
    {
        drzewo[x]=(wagi[drzewo[x<<1]]<wagi[drzewo[(x<<1)+1]]?drzewo[x<<1]:drzewo[(x<<1)+1]);
        //printf("Zaaktualizowano: %d=%d\n",drzewo[x],wagi[drzewo[x]]);
        x/=2;
    }
}

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

        wagi=new int[n+1];
        drzewo=new int[(size=mpow2(n))*2];

        for(int i=0;i<=n;++i)
            wagi[i]=inf;

        for(int i=1;i<size;++i)
            drzewo[i]=0;

        for(int i=0;i<n;++i)
            drzewo[i+size]=i+1;

        for(int i=n;i<size;++i)
            drzewo[i+size]=0;

        wagi[1]=0;
        
        //for(int i=size-1;i>0;--i)
            rebuild(1);
        
        while(wagi[drzewo[1]]!=inf)
        {
            int v=drzewo[1];
            int r=wagi[v];

            drzewo[v+size-1]=0;
            rebuild(v);

            /*printf("   ");
            for(int i=1;i<size*2;++i)
                printf("%d ",drzewo[i]);
            putchar('\n');*/

//          if(r==inf)                      // Najbliższy wierzchołek jest nieskończenie daleko - relaksacja jest niemożliwa
//              throw 2;                    // Nigdy nie powinno się wydarzyć

            for(vector<edge>::iterator i=graf[v].L.begin(),e=graf[v].L.end();i!=e;++i)
            {
                int x;
                
                if(i->T==0 || ((x=((r+i->T-i->a)%i->T))<i->l && r>=i->a))
                {
                    if(wagi[i->D]>r+i->w)
                    {
                        wagi[i->D]=r+i->w;
                        rebuild(i->D);
                        //printf("%d: ",i->D);
                        //for(int i=1;i<size*2;++i)
                            //printf("%d ",drzewo[i]);
                        //putchar('\n');
                    }
                }
                else if(r<i->a)
                {
                    if(wagi[i->D]>i->a)
                    {
                        wagi[i->D]=i->a;
                        rebuild(i->D);
                    }
                }
                else
                {
                    if(wagi[i->D]>r+i->w+i->T-x)
                    {
                        wagi[i->D]=r+i->w+i->T-x;
                        rebuild(i->D);
                        //printf("2: ");
                        //for(int i=1;i<size*2;++i)
                            //printf("%d ",drzewo[i]);
                        //putchar('\n');
                    }
                }
            }
        }
        
        if(wagi[n]==inf)
            puts("NIE");
        else
            printf("%d\n",wagi[n]);

        delete [] drzewo;
        delete [] wagi;
        delete [] graf;
    }
	return 0;
}
