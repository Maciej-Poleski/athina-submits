#include <cstdio>
#include <vector>
#include <stdint.h>

using namespace std;

inline unsigned int mpow2(unsigned int n)
{
	unsigned int wynik=1;
	while(wynik<n)
		wynik<<=1;
	return wynik;
}

const int	inf=2000000000;

struct edge
{
	uint32_t	d;
	int			w;
	int			t;
	int			a;
	int			l;
	
	edge(uint32_t dd,int ww,int tt,int aa,int ll) : d(dd),w(ww),t(tt),a(aa),l(ll) {}
};

/*struct vertex
{
	uint32_t	i;
	int			t;
	
	vertex() : t(inf) {}
	
	bool operator<(const vertex &o) const
	{
		return t<o.t;
	}
};*/

vector<edge>	*graf;
uint32_t		n;
uint32_t		m;

namespace PQ
{
	int			*mat;
	uint32_t	*tree;
	uint32_t	treeS;
	
}

using namespace PQ;

void print_t()
{
        printf("<table border=2 cellspacing=0 width=100%>\n<tr>\n");
        for(size_t i=1;i<treeS*2;++i)
        {
                size_t cols=(i==mpow2(i)?treeS*2/i:treeS*2/(mpow2(i)/2));
                printf("<td colspan=%u>\n",cols);

                printf("<center>%d<br />%d<br />%u</center>\n",tree[i],mat[tree[i]],i);

                printf("</td>\n");

                if(i==mpow2(i)-1 || i==1)
                        printf("</tr>\n<tr>\n");
        }
        printf("</table>");
}

void rebuild(uint32_t n)
{
    uint32_t    t;
    while(n)
    {
        t=(mat[tree[n<<1]]<mat[tree[(n<<1)+1]]?(n<<1):((n<<1)+1));
        
        tree[n]=tree[t];
        
        n>>=1;
    }
}

int main()
{
	uint32_t	z;
	scanf("%u",&z);
	while(z--)
	{
		uint32_t	u;
		uint32_t	v;
		int			w;
		int			t;
		int			a;
		int			l;
		
		scanf("%u%u",&n,&m);
		
		graf=new vector<edge>[n+1];
		
		for(uint32_t i=1;i<=m;++i)
		{
			scanf("%u%u%d%d%d%d",&u,&v,&w,&t,&a,&l);
			graf[u].push_back(edge(v,w,t,a,l));
		}
		
		PQ::mat=new int[n+1];
		
		for(uint32_t i=1;i<=n;++i)
			mat[i]=inf;
		
		PQ::tree=new uint32_t[(PQ::treeS=mpow2(n+1))*2-1];
		--PQ::tree;
		
		//for(uint32_t i=1;i<PQ::treeS*2;++i)
		//	printf("%u ",PQ::tree[i]);
		//putchar('\n');
		
		for(uint32_t i=1;i<PQ::treeS*2;++i)
			PQ::tree[i]=n;
		
		for(uint32_t i=PQ::treeS,e=i+n;i<e;++i)
			PQ::tree[i]=i-PQ::treeS;
		for(uint32_t i=PQ::treeS+n,e=PQ::treeS*2;i<e;++i)
			PQ::tree[i]=n;
		
		mat[tree[treeS]]=0;
		
		for(uint32_t i=treeS>>1;i>0;--i)
		{
			//printf("%u %u\n",tree[i<<1],tree[(i<<1)+1]);
			tree[i]=(mat[tree[i<<1]]<mat[tree[(i<<1)+1]]?tree[i<<1]:tree[(i<<1)+1]);
		}
			
		//print_t();
		
		for(uint32_t i=1;i<n;++i)
		{
			uint32_t	V=tree[1];
            if(V==n)
                break;
			tree[V+treeS]=n;
			
			rebuild((V+treeS)>>1);
			
			//print_t();
			//fflush(stdout);
			for(vector<edge>::iterator i=graf[V+1].begin(),e=graf[V+1].end();i!=e;++i)
			{
				//printf("relax z %d waga %d",V+1,mat[V]);
				if(i->t==0 || (mat[V]+i->t-i->a)%i->t<i->l)
				{
					//printf(" A ");
					mat[i->d-1]=(mat[i->d-1]<mat[V]+i->w?mat[i->d-1]:mat[V]+i->w);
				}
				else
				{
					//printf(" B %d | ",(i->t-((mat[V]+i->t-i->a)%i->t)+i->w));
					mat[i->d-1]=(mat[i->d-1]<mat[V]+(i->t-((mat[V]+i->t-i->a)%i->t)+i->w)?mat[i->d-1]:mat[V]+(i->t-((mat[V]+i->t-i->a)%i->t)+i->w));
				}
				//printf("%d\n",mat[i->d-1]);
				//printf("W %u dla V=%u w=%u\n",V+1,i->d,mat[i->d-1]);
				
				rebuild((treeS+i->d-1)>>1);
				
				//print_t();
			}
		}
		
		/*for(uint32_t i=0;i<=n;++i)
			printf("%d ",mat[i]);
		putchar('\n');*/
		
		if(tree[1]==n)
			puts("NIE");
		else
			printf("%d\n",mat[tree[1]]);
		
		delete [] graf;
		delete [] ++tree;
		delete [] mat;
	}
	return 0;
}
