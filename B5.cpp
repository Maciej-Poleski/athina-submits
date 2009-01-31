#include <cstdio>
#include <stdint.h>
#include <list>
#include <vector>
using namespace std;

const uint64_t	inf=0xffffffffffffffffll-1000005ll;
uint32_t		k;					//k

struct vertex;

template<class T>
struct heap
{
	T		*tab;
	size_t	size;

	public:

	heap(T *w,size_t s): tab(w),size(s)
	{
		--tab;
		for(size_t i=s>>1;i>0;--i)
			rebuild_down(i);
	}

	~heap()
	{
		delete [] ++tab;
	}

	void rebuild_tree()								//Ta funkcja nie jest generyczna!!!
	{
		size_t	n=1;
		size_t	i;
		//printf("Rebuild dla %u\n",n);
		while((n<<1)<=size)
		{
			//puts("A");
			i=n;
			if(tab[i<<1]<tab[i])
				i<<=1;
			if(((n<<1)|1)<=size && tab[(n<<1)|1]<tab[i])
				i=(n<<1)|1;
			if(tab[i]<tab[n])
			{
				//printf("Zamianiam komitet %u i %u\n",tab[n].i+1,tab[i].i+1);
				swap(tab[n],tab[i]);
				tab[i].wsk->i[tab[i].r]=i;
				tab[n].wsk->i[tab[i].r]=n;
				n=i;
			}
			else
				break;
		}
		//puts("E");
	}
	
	void rebuild_down(size_t n)						//Ta funkcja nie jest generyczna!!!
	{
		size_t i;
		//printf("Rebuild dla %u\n",n);
		while((n<<1)<=size)
		{
			//puts("A");
			i=n;
			if(tab[i<<1]<tab[i])
				i<<=1;
			if(((n<<1)|1)<=size && tab[(n<<1)|1]<tab[i])
				i=(n<<1)|1;
			if(tab[i]<tab[n])
			{
				//printf("Zamianiam komitet %u i %u\n",tab[n].i+1,tab[i].i+1);
				swap(tab[n],tab[i]);
				tab[i].wsk->i[tab[i].r]=i;
				tab[n].wsk->i[tab[i].r]=n;
				n=i;
			}
			else
			{
				break;
			}
		}
		//puts("E");
	}
	
	T & max()
	{
		return tab[1];
	}
	
	void dump_tab(vertex *w)
	{
		printf("Size: %u\n",size);
		for(size_t i=1;i<=size;++i)
		{
			printf("v: %d | waga: %llu\n",tab[i].wsk-w,tab[i].min);
		}
		putchar('\n');
	}
	
	//	v2:
	
	size_t rebuild_up(size_t n)					//Ta funkcja nie jest generyczna!!!
	{
		size_t i=n;
		T tmp=tab[n];
		while((i>>1) && tmp<tab[i>>1])
		{
			tab[i]=tab[i>>1];
			tab[i].wsk->i[tab[i].r]=i;
			//printf("Kopiec: %u zastępuje %u\n",i>>1,i);
			i>>=1;
		}
		tab[i]=tmp;
		tab[i].wsk->i[tab[i].r]=i;
		//printf("Kopiec: %u zastępuje %u\n",i>>1,i);
		return i;
	}
	
	T& min()
	{
		return tab[1];
	}
	
	T extract_min()
	{
		T tmp=tab[1];
		tab[1]=tab[size--];
		rebuild_tree();
		return tmp;
	}
	
	size_t insert(T tmp)
	{
		tab[++size]=tmp;
		return rebuild_up(size);
	}
};

struct edge
{
	uint32_t	w;	//Waga
	uint32_t	d;	//Cel
	
	edge() {}
	
	edge(uint32_t ww,uint32_t dd) : w(ww), d(dd) {}
};

struct vertex
{
	uint64_t			min;	//Najlżejsza droga po wszystkich modułach z k z this
	size_t				*i;		//Indeks label w kopcu
	uint64_t			*k;		//Najlżejsze moduły do this wierzchołka
	vector<edge>		edges;	//Krawędzie
	bool				*heap;	//Jest w kopcu
	
	vertex()
	{
		k=new uint64_t[::k];
		heap=new bool[::k];
		i=new size_t[::k];
		min=inf;
		for(uint64_t *wsk=k,*end=k+::k;wsk!=end;++wsk)
			*wsk=inf;
		for(bool *wsk=heap,*end=heap+::k;wsk!=end;++wsk)
			*wsk=false;
	}
	
	~vertex()
	{
		delete [] k;
		delete [] heap;
		delete [] i;
	}
};

struct label
{
	uint64_t	min;		//Najlżejsza droga po wszystkich modułach z k z wsk 
	vertex*		wsk;		//Wskaźnik do wierzchołka
	uint32_t	r;
	
	label() {}
	
	label(uint64_t m,vertex* w,uint32_t rr) : min(m),wsk(w),r(rr) {}
	
	bool operator<(const label &o) const
	{
		return min<o.min;
	}
};

int main()
{
	#ifdef heap_test
	size_t i=10;
	int tab[]={7,32,87,4,6,2,8,456,2,65};
	heap<int> h(tab,i);
	h.dump_tab();
	printf("%d %d %d %d %d %d %d\n",h.extract_min(),h.extract_min(),h.extract_min(),h.extract_min(),h.extract_min(),h.extract_min(),h.extract_min());
	h.insert(5);
	h.insert(20);
	h.dump_tab();
	printf("%d %d %d %d %d\n",h.extract_min(),h.extract_min(),h.extract_min(),h.extract_min(),h.extract_min());
	#else
	
	uint32_t z;
	scanf("%u",&z);
	
	while(z--)
	{
		uint32_t	n;	//Wierzchołki
		uint32_t	m;	//Ścieżki
		uint32_t	a;	//a
		uint32_t	b;	//b
		uint32_t	d;	//waga
		uint32_t	q;	//rundy
		char		c[8];	//To by się zamknął
		
		scanf("%u%u%u",&n,&m,&k);
		
		vertex *node=new vertex[n];
		--node;
		
		for(uint32_t i=0;i<m;++i)
		{
			scanf("%u%u%u",&a,&b,&d);
			node[a].edges.push_back(edge(d,b));
			node[b].edges.push_back(edge(d,a));
		}
		
		node[n].min=0;
		node[n].k[0]=0;
		node[n].i[0]=1;
		node[n].heap[0]=true;
		
		label * tab=new label[n*k];
		*tab=label(0,node+n,0);
		
		heap<label> kopiec(tab,1);
		
		/**********************	DIJKSTRA ********************/
		
		while(kopiec.size)
		{
			vertex *wsk;
			uint64_t m;
			uint32_t rr;
			{
				label tmp=kopiec.extract_min();
				wsk=tmp.wsk;					//This
				m=tmp.min;						//Droga do this wierzchołka
				rr=tmp.r;
				//printf("%llu ",m);
			}
			
			//printf("Dijkstra v: %u | d: %llu | r: %llu\n",wsk-node,m,m%k);
				
			wsk->heap[rr]=false;
			//bool push=false;
			for(vector<edge>::iterator i=wsk->edges.begin(),e=wsk->edges.end();i!=e;++i)
			{
				uint64_t r=(m+i->w)%k;				//Reszta do celu włącznie
				if(node[i->d].k[r]>m+i->w)
				{
					node[i->d].k[r]=m+(i->w);
					//printf("Poprawka v: %u | d: %llu ",i->d,node[i->d].k[r]);
					if(node[i->d].heap[r])
					{
						//printf("modyfikacja %u\n",node[i->d].i[r]);
						kopiec.tab[node[i->d].i[r]].min=m+i->w;
						kopiec.rebuild_up(node[i->d].i[r]);
					}
					else
					{
						//printf("wrzut\n");
						node[i->d].heap[r]=true;
						kopiec.insert(label(m+i->w,&node[i->d],r));
					}
					//kopiec.dump_tab(node);
					//printf("Poprawka v: %u | d: %llu\n",kopiec.tab[node[i->d].i[r]].wsk-node,kopiec.tab[node[i->d].i[r]].min);
				}
			}
		}
		//uint32_t aa=1;
		/*
		putchar('\n');
		for(int i=1;i<=n;++i)
		{
			printf("%u|",i);
			for(int j=0;j<k;++j)
			{
				if(node[i].k[j]!=inf)
					printf("\t%llu",node[i].k[j]);
				else
					printf("\tinf");
			}
			putchar('\n');
		}*/
		
		scanf("%u",&q);
		while(q--)
		{
			scanf("%u%u%s",&a,&b,c);
			if(node[a].k[0]==node[b].k[0])
			{
				if(node[a].k[0]==inf)
				{
					//printf("%u %u %s\n",a,b,c);
					printf("NIKT\n");
				}
				else if(*c=='J')
				{
					//printf("%u %u %s\n",a,b,c);
					printf("Jacek %llu\n",node[a].k[0]/(::k));
				}
				else
				{
					//printf("%u %u %s\n",a,b,c);
					printf("Placek %llu\n",node[a].k[0]/(::k));
				}
			}
			else
			{
				if(node[a].k[0]<node[b].k[0])
				{
					//printf("%u %u %s\n",a,b,c);
					printf("Jacek %llu\n",node[a].k[0]/(::k));
				}
				else
				{
					//printf("%u %u %s\n",a,b,c);
					printf("Placek %llu\n",node[b].k[0]/(::k));
				}
			}
		}
		
		delete [] ++node;
	}
	
	#endif
	
	return 0;
}
