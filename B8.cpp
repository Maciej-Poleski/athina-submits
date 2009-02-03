#include <cstdio>
#include <string>
//#include <vector>
#include <algorithm>

using namespace std;

struct edge
{
	uint32_t	s;
	uint32_t	d;
	uint32_t	w;
	
	edge() {}
	
	edge(uint32_t ss,uint32_t dd,uint32_t vv) : s(ss),d(dd),w(vv) {}
	
	bool operator<(const edge &o) const
	{
		return w<o.w;
	}
};

struct node
{
	uint32_t	p;
	uint32_t	r;
	
	node() {}
	
	node(uint32_t pp,uint32_t rr) : p(pp),r(rr) {}
};

edge		*graf;
node		*las;
string		*osiedla;
uint32_t	n;
uint32_t	m;
uint64_t	wynik;
char		temp[16];
char		temp2[16];

uint32_t parent(uint32_t n)
{
	if(n==las[n].p)
		return n;
	
	return las[n].p=parent(las[n].p);
}

bool family(uint32_t a,uint32_t b)
{
	return parent(a)==parent(b);
}

void scal(uint32_t a,uint32_t b)
{
	a=parent(a);
	b=parent(b);
	if(las[a].r==las[b].r)
	{
		++las[b].r;
		las[a].p=b;
	}
	else if(las[a].r<las[b].r)
	{
		las[a].p=b;
	}
	else
	{
		las[b].p=a;
	}
}

int main()
{
	uint32_t	z;
	scanf("%u",&z);
	while(z--)
	{
		scanf("%u%u",&n,&m);
		getchar();
		
		graf=new edge[m];
		las=new node[n];
		osiedla=new string[n];
		
		for(string *i=osiedla,*e=osiedla+n;i!=e;++i)
		{
			gets(temp);
			i->assign(temp);
		}
		//getchar();
		
		/*sort(osiedla,osiedla+n);
		
		for(uint32_t i=0;i<n;++i)
			printf("%s\n",osiedla[i].c_str());
		*/
		
		for(edge *i=graf,*e=graf+m;i!=e;++i)
		{
			scanf("%s %s %u",temp,temp2,&(i->w));
			
			i->s=lower_bound(osiedla,osiedla+n,temp)-osiedla;
			i->d=lower_bound(osiedla,osiedla+n,temp2)-osiedla;
		}
		
		sort(graf,graf+m);
		
		for(node *i=las,*e=las+n;i!=e;++i)
		{
			i->p=i-las;
			i->r=0;
		}
		
		wynik=0;
		
		//for(uint32_t i=0;i<m;++i)
		//	printf("%u %u %u\n",graf[i].s,graf[i].d,graf[i].w);
		
		for(edge *i=graf,*e=graf+m;i!=e;++i)
		{
			if(family(i->s,i->d))
				continue;
			
			wynik+=i->w;
			
			scal(i->s,i->d);
		}
		
		printf("%llu\n",wynik);
		
		delete [] graf;
		delete [] las;
		delete [] osiedla;
	}
	return 0;
}
