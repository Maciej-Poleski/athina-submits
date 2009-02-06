#include <cstdio>
#include <vector>
#include <stdint.h>

using namespace std;

const int		inf=2000000000;

struct edge
{
	int			w;
	uint32_t	d;
	
	edge() {}
	edge(int ww,uint32_t dd) : w(ww),d(dd) {}
};
/*
template<class T>
T max(T a,T b)
{
	if(a<b)
		return b;
	return a;
}*/

vector<edge>	*graf;
int				*h;
int				*D;
uint32_t		a;
uint32_t		b;

uint32_t		n;

int main()
{
	uint32_t	z;
	scanf("%u",&z);
	while(z--)
	{
		uint32_t	d;
		uint32_t	m;
		int			w;
		scanf("%u%u%u",&n,&a,&b);
		
		graf=new vector<edge>[n+1];
		h=new int[n+1];
		
		for(uint32_t i=1;i<=n;++i)
		{
			scanf("%d%u",h+i,&m);
			
			graf[i].reserve(m);
			
			for(uint32_t j=0;j<m;++j)
			{
				scanf("%u%d",&d,&w);
				graf[i].push_back(edge(w,d));
			}
		}
		
		/*for(uint32_t i=1;i<=n;++i)
		{
			printf("wierzchołek: %u wysokość %d sąsiedzi: %u\n",i,h[i],graf[i].size());
			
			for(vector<edge>::iterator j=graf[i].begin(),e=graf[i].end();j!=e;++j)
			{
				printf("\tCel %u | odległość: %d\n",j->d,j->w);
			}
		}*/
		
		/******************** PREPROCESING *********************/
		
		for(uint32_t i=1;i<=n;++i)
		{
			for(vector<edge>::iterator j=graf[i].begin(),e=graf[i].end();j!=e;++j)
			{
				j->w+=(h[j->d]-h[i])/10;
			}
		}
		
		delete [] h;
		
		/*for(uint32_t i=1;i<=n;++i)
		{
			printf("wierzchołek: %u sąsiedzi: %u\n",i,graf[i].size());
			
			for(vector<edge>::iterator j=graf[i].begin(),e=graf[i].end();j!=e;++j)
			{
				printf("\tCel %u | odległość: %d\n",j->d,j->w);
			}
		}*/
		
		D=new int[n+1];
		
		for(int *i=D+1,*e=i+n;i!=e;++i)
			*i=inf;
			
		D[a]=0;
			
		for(uint32_t i=1;i<=n;++i)
		{
			bool relax=false;
			for(uint32_t j=1;j<=n;++j)
			{
				if(D[j]==inf)
					continue;
				for(vector<edge>::iterator k=graf[j].begin(),e=graf[j].end();k!=e;++k)
				{
					if(D[k->d]>D[j]+k->w)
					{
						D[k->d]=D[j]+k->w;
						relax=true;
					}
				}
			}
			if(!relax)
				break;
		}
		
		if(D[b]==inf)
			puts("BRAK");
		else
			printf("%d\n",max(0,D[b]));
			
		delete [] graf;
		delete [] D;
	}
	return 0;
}
