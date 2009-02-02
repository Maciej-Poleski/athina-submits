#include <cstdio>
#include <vector>
#include <stdint.h>

using namespace std;

struct edge
{
	uint32_t	d;
	uint32_t	v;
	
	edge(uint32_t dd,uint32_t vv) : d(dd),v(vv) {}
};

bool			*v2;
vector<edge>	*graf;
uint32_t		*wynik;
uint32_t		suma;
uint32_t		n;
uint32_t		m;

void buduj()
{
	for(uint32_t i=1;i<=n;++i)
	{
		if(graf[i].size()&1)
		{
			graf[0].push_back(edge(i,m+suma));
			graf[i].push_back(edge(0,m+suma));
			++suma;
		}
	}
}

void iteruj()
{
	wynik=new uint32_t[m+2];
	uint32_t				*w=wynik+1;
	uint32_t				n=0;
	vector<edge>::iterator	i,e;
	while(true)
	{
		for(i=graf[n].begin(),e=graf[n].end();i!=e && v2[i->v];++i);
	
		if(i==e)
		{
			/*printf("%u",w-wynik);
			for(uint32_t *wsk=wynik+1;wsk<w;++wsk)
				printf(" %u",*wsk);
			putchar('\n');
			w=wynik;
			puts("KONIEC");*/
			break;
		}
		if(i->d==0)
		{
			printf("%u",w-wynik-1);
			for(uint32_t *wsk=wynik+1;wsk<w;++wsk)
				printf(" %u",*wsk);
			putchar('\n');
			w=wynik;
		}
	
		*(w++)=i->d;
		v2[i->v]=true;
		n=i->d;
	}
	delete [] wynik;
}

void onlyOneEuler()
{
	wynik=new uint32_t[m+1];
	uint32_t				*w=wynik;
	uint32_t				n=1;
	vector<edge>::iterator	i,e;
	while(true)
	{
		for(i=graf[n].begin(),e=graf[n].end();i!=e && v2[i->v];++i);
	
		if(i==e)
		{
			printf("%u",w-wynik);
			for(uint32_t *wsk=wynik;wsk<w;++wsk)
				printf(" %u",*wsk);
			printf(" %u",*wynik);
			putchar('\n');
			w=wynik;
			break;
		}
		/*if(i->d==0)
		{
			printf("%u",w-wynik-1);
			for(uint32_t *wsk=wynik+1;wsk<w;++wsk)
				printf(" %u",*wsk);
			putchar('\n');
			w=wynik;
		}*/
	
		*(w++)=n;
		v2[i->v]=true;
		n=i->d;
	}
	delete [] wynik;
}

int main()
{
	uint32_t	z;
	uint32_t	a;
	uint32_t	b;
	scanf("%u",&z);
	while(z--)
	{
		scanf("%u%u",&n,&m);
		
		graf=new vector<edge>[n+1];
		
		for(uint32_t i=0;i<m;++i)
		{
			scanf("%u%u",&a,&b);
			graf[a].push_back(edge(b,i));
			graf[b].push_back(edge(a,i));
		}
		
		buduj();
		
		v2=new bool[m+suma];
		
		for(bool *i=v2,*e=i+m+suma;i!=e;++i)
			*i=false;
		
		if(suma!=0)
		{
			printf("%u\n",suma>>1);
			iteruj();
		}
		else
		{
			printf("1\n");
			onlyOneEuler();
		}
			
		delete [] graf;
		delete [] v2;
		
		/*printf("%u\n",suma);
		for(vector<edge>::iterator i=graf[0].begin(),e=graf[0].end();i!=e;++i)
			printf("%u ",i->d);
		putchar('\n');*/
		
		
		suma=0;
	}
	return 0;
}
