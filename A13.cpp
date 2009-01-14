#include <cstdio>
#include <stdint.h>

template<class T>
void swap (T&a,T&b)
{
	T t=a;
	a=b;
	b=t;
}

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

	void rebuild_tree()
	{
		size_t	n=1;
		size_t	i;
		//printf("Rebuild dla %u\n",n);
		while((n<<1)<=size)
		{
			//puts("A");
			i=n;
			if(tab[i]<tab[i<<1])
				i<<=1;
			if(((n<<1)|1)<=size && tab[i]<tab[(n<<1)|1])
				i=(n<<1)|1;
			if(tab[n]<tab[i])
			{
				//printf("Zamianiam komitet %u i %u\n",tab[n].i+1,tab[i].i+1);
				swap(tab[n],tab[i]);
				n=i;
			}
			else
				break;
		}
		//puts("E");
	}
	
	void rebuild_down(size_t n)
	{
		size_t i;
		//printf("Rebuild dla %u\n",n);
		while((n<<1)<=size)
		{
			//puts("A");
			i=n;
			if(tab[i]<tab[i<<1])
				i<<=1;
			if(((n<<1)|1)<=size && tab[i]<tab[(n<<1)|1])
				i=(n<<1)|1;
			if(tab[n]<tab[i])
			{
				//printf("Zamianiam komitet %u i %u\n",tab[n].i+1,tab[i].i+1);
				swap(tab[n],tab[i]);
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
	
	void dump_tab()
	{
		printf("Size: %u\n",size);
		for(size_t i=1;i<=size;++i)
		{
			printf("%lf ",static_cast<double>(tab[i].l)/tab[i].d);
		}
		putchar('\n');
	}
};

struct komitet
{
	uint64_t	l;	//g�osy
	size_t		d;	//dzielnik
	size_t		i;	//nr
	size_t		m;	//ilo�� mandat�w
	
	komitet(): d(1), m(0) {}
	
	bool operator<(const komitet &o) const
	{
		return l*o.d<o.l*d || (l*o.d==o.l*d && (l<o.l || (l==o.l && i>o.i)));
	}
};
	
int main()
{
	uint32_t z;
	scanf("%u",&z);
	while(z--)
	{
		uint32_t	n;
		uint32_t	m;
		uint32_t	i=0;
		size_t		*matryca;
		komitet		*tab;
		
		scanf("%u%u",&n,&m);
		tab=new komitet[n];
		
		for(komitet *wsk=tab,*end=tab+n;wsk!=end;++wsk,++i)
		{
			scanf("%llu",&(wsk->l));
			wsk->i=i;
		}
		
		heap<komitet> kopiec(tab,n);
		
		//kopiec.dump_tab();
		
		for(uint32_t i=0;i<m;++i)
		{
			++kopiec.max().m;
			++kopiec.max().d;
			//printf("Komitet %u ma teraz %u mandat�w\n",kopiec.max().i,kopiec.max().m);
			kopiec.rebuild_tree();
		}
		
		matryca=new size_t[n];
		
		for(size_t i=1;i<=n;++i)
			matryca[kopiec.tab[i].i]=kopiec.tab[i].m;
		
		for(size_t *i=matryca,*end=matryca+n;i!=end;++i)
			printf("%u\n",*i);
		
		delete [] matryca;
	}
	return 0;
}
