#include <cstdio>
#include <climits>
#include <vector>
using namespace std;

#ifdef USE_OBSOLETE_FUNCTIONS
#ifdef FULL_DEBUG
#define TOPSORT_DEBUG
#endif
#endif

struct edge
{
	int				v;
	int				d;

	edge(int vv,int dd) : v(vv),d(dd) {}
};

struct node
{
	int				minN;
	int				max0;
	int				count0;
	int				countN;
	int				selectedX;
	int				selectedN;
	vector<edge>	next;
	vector<edge>	back;

	node(): minN(INT_MAX), max0(INT_MIN), count0(0), countN(0) {}
};

node				*G;
int					*b;
int					cb;
int					n;
int					m;
int					q;

#ifdef USE_OBSOLETE_FUNCTIONS
void topSort(int n)
{
	for(vector<int>::iterator i=G[n].next.begin(),e=G[n].next.end();i!=e;++i)
	{
		if(G[i->d].count==1)
			(G[i->d].count=0,topSort(i->d));
	}
	*(--topPtr)=n;
}

#endif

int main()
{
	int z;
	scanf("%d\n",&z);
	while(z--)
	{
		scanf("%d %d",&n,&m);
		G=new node[n+1];
		for(int i=0;i<m;++i)
		{
			int a,b,r;
			scanf("%d %d %d\n",&a,&b,&r);
			G[a].next.push_back(edge(r,b));
			G[b].back.push_back(edge(r,a));
		}

		#ifdef USE_OBSOLETE_FUNCTIONS

		topSort(1);

		#ifdef TOPSORT_DEBUG
		for(int i=0;i<n;++i)
			printf("%d\n",top[i]);
		#endif
		#endif

		G[1].max0=G[n].minN=0;
		G[1].count0=G[n].countN=1;

		for(int v=1;v<=n;++v)
		{
			for(vector<edge>::iterator j=G[v].next.begin(),e=G[v].next.end();j!=e;++j)
			{
				G[j->d].count0+=G[v].count0;
				if(G[j->d].max0<G[v].max0+j->v)
				{
					G[j->d].max0=G[v].max0+j->v;
					G[j->d].selectedX=v;
				}
			}
		}

		for(int v=n;v>0;--v)
		{
			for(vector<edge>::iterator j=G[v].back.begin(),e=G[v].back.end();j!=e;++j)
			{
				G[j->d].countN+=G[v].countN;
				if(G[j->d].minN>G[v].minN+j->v)
				{
					G[j->d].minN=G[v].minN+j->v;
					G[j->d].selectedN=v;
				}
			}
		}

		scanf("%d\n",&q);
		while(q--)
		{
			b=new int[n];
			cb=0;
			int x;
			scanf("%d ",&x);
			printf("%d\n",G[x].count0*G[x].countN);
			int v=x;
			while(v!=1)
			{
				b[cb++]=v;
				v=G[v].selectedX;
			}
			b[cb++]=1;
			int p=cb-1;
			v=x;
			while(v!=n)
			{
				v=G[v].selectedN;
				b[cb++]=v;
			}
			printf("%d",cb);
			for(int i=p;i>=0;--i)
				printf(" %d",b[i]);
			for(int i=p+1;i<cb;++i)
				printf(" %d",b[i]);
			delete [] b;
			printf("\n");
		}
		delete [] G;
	}
}
