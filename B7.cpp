#include <cstdio>
#include <stdint.h>
#include <vector>
#include <stack>
using namespace std;

struct edge
{
	uint32_t	d;
	bool		*v;
	
	edge(uint32_t dd,bool *vv) : d(dd),v(vv) {}
};

vector<edge>		*graf;
bool				*leak;
vector<uint32_t>	stos;
bool				*v;
bool				*v2;
uint32_t			n;
uint32_t			suma=0;

void dfs(uint32_t n=1)
{
	if(!v[n])
	{
		v[n]=true;
		if((graf[n].size())&1)
		{
			++suma;
			leak=new bool(false);
			graf[0].push_back(edge(n,leak));
			graf[n].push_back(edge(0,leak));
		}
		for(vector<edge>::iterator i=graf[n].begin(),e=graf[n].end();i!=e;++i)
		{
			dfs(i->d);
		}
	}
}

void dfs2(uint32_t n=0)
{
	for(vector<edge>::iterator i=graf[n].begin(),e=graf[n].end();i!=e;++i)
	{
		if(!(*(i->v)))
		{
			*(i->v)=true;
			stos.push_back(i->d);
			dfs2(i->d);
			break;
		}
	}
}

int main()
{
	uint32_t	z;
	scanf("%u",&z);
	while(z--)
	{
		uint32_t	m;
		uint32_t	t;
		uint32_t	x;
		uint32_t	y;
		
		scanf("%u%u",&n,&m);
		
		graf=new vector<edge>[n+1];
		v=new bool[n+1];
		v2=new bool[m+1];
		
		for(bool *i=v,*e=v+n+1;i!=e;++i)
			*i=false;
		t=m;
		while(m)
		{
			scanf("%u%u",&x,&y);
			graf[x].push_back(edge(y,v2+m));
			graf[y].push_back(edge(x,v2+m));
			v2[m]=false;
			--m;
		}
		
		dfs();
		delete [] v;
		
		//printf("%u\n",suma);
		stos.push_back(0);
		
		if(suma==0)
		{
			dfs2(1);
			delete [] v2;
			delete [] graf;
			printf("1\n%u",t+1);
			t=stos.back();
			while(stos.size()!=1)
			{
				printf(" %u",stos.back());
				stos.pop_back();
			}
			stos.pop_back();
			printf(" %u\n",t);
		}
		else
		{
			printf("%u\n",suma>>1);
			dfs2();
			delete [] v2;
			for(vector<edge>::iterator i=graf[0].begin(),e=graf[0].end();i!=e;++i)
				delete i->v;
			delete [] graf;
			
			uint32_t i=1;
			
			while(i<stos.size())
			{
				uint32_t j=i;
				for(;stos[j]!=0;++j);
				printf("%u",j-i);
				for(;i<j;++i)
					printf(" %u",stos[i]);
				putchar('\n');
				++i;
			}
			stos.clear();
		}
		
		/*for(vector<edge>::iterator i=graf[0].begin(),e=graf[0].end();i!=e;++i)
			printf("%u ",i->d);
		putchar('\n');
		
		while(!stos.empty())
		{
			printf("%u ",stos.top());
			stos.pop();
		}
		putchar('\n');*/
		
		//for(vector<edge>::iterator i=graf[0].begin(),e=graf[0].end();i!=e;++i)
		//	delete i->v;
		
		//for(vector<edge> *i=graf,*e=graf+n+1;i!=e;++i)
			//i->clear();
		
		suma=0;
	}
	return 0;
}
