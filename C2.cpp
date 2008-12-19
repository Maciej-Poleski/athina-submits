#include <cstdio>
#include <algorithm>
using namespace std;

#define pion 1
#define poziomB 0
#define poziomE 2

inline unsigned int mpow2(unsigned int n)
{
	unsigned int wynik=1;
	while(wynik<n)
		wynik<<=1;
	return wynik;
}

struct kartez
{
	int x,y;
    
	bool operator<(const kartez &o) const
	{
		if(x<o.x)
			return true;
		return false;
	}
    
	bool operator==(const kartez &o) const
	{
		if(x==o.x)
			return true;
		return false;
	}
};

class sumTree
{
	unsigned int *tab;
	unsigned int size,tabSize;
    
	void add1(unsigned int n)
	{
		while(n)
		{
			++tab[n];
			n=(n-1)>>1;
		}
		++tab[0];
	}
	
	void sub1(unsigned int n)
	{
		while(n)
		{
			--tab[n];
			--n>>=1;
		}
		--tab[0];
	}
    
	unsigned int add(unsigned int begin,unsigned int end)
	{
		unsigned int l=tab[begin],p=tab[end];
		while(begin+1!=end)
		{
			if(begin&1)
			{
				l+=tab[begin+1];
				begin>>=1;
			}
			else
			{
				begin=(begin-1)>>1;
			}
			if(end&1)
			{
				end>>=1;
			}
			else
			{
				p+=tab[end-1];
				end=(end-1)>>1;
			}
		}
		return l+p;
	}
    
	public:
    
		sumTree(unsigned int n) : size(mpow2(n)),tabSize(2*size-1)
		{
			tab=new unsigned int [tabSize];
			for(unsigned int *wsk=tab,*end=tab+tabSize;wsk!=end;++wsk)
				*wsk=0;
		}
    
		~sumTree()
		{
			delete [] tab;
		}
    
		void inc(unsigned int n)
		{
			add1(size+n-1);
		}
		
		void dec(unsigned int n)
		{
			sub1(size+n-1);
		}
    
		unsigned int suma(int begin,int end)
		{
			if(begin==end)
				return tab[size+begin-1];
			if(begin>end)
				return 0;
			return add(size+begin-1,size+end-1);
		}
};

class segTree
{
    unsigned int *tab;
	unsigned int size,tabSize;
	
	void add(unsigned int a,unsigned int b)
	{
		while(a!=b)
		{
			//printf(" %u %u\n",a,b);
			unsigned int sub=b-a,n=a,i=1;
			for(;i<<1<=sub && n&1;i<<=1,--n>>=1);
			a+=i;
			++tab[n];
		}
	}
	
	unsigned int segSum(unsigned int n)
	{
		unsigned int wynik=0;
		while(n)
		{
			wynik+=tab[n];
			--n>>=1;
		}
		wynik+=tab[0];
		return wynik;
	}
	
	public:
	
	segTree(unsigned int n) : size(mpow2(n)),tabSize(2*size-1)
	{
		tab=new unsigned int [tabSize];
		for(unsigned int *wsk=tab,*end=tab+tabSize;wsk!=end;++wsk)
			*wsk=0;
	}
	
	~segTree()
	{
		delete [] tab;
	}
	
	void addSeg(int a,int b)
	{
		add(a+size-1,b+size);
	}
	
	unsigned int suma(int a)
	{
		return segSum(a+size-1);
	}
};

unsigned *wynik;
int *y;
int sizeY;

struct event
{
	int
					x,
					y,
					t;
	unsigned int
					n:30,
					o:2;
	
	bool operator<(const event &c) const
	{
		if(x<c.x or (x==c.x and o<c.o))
			return true;
		return false;
	}
};

int main()
{
	#ifdef segTree_test
	segTree drzewo(14);
	for(unsigned int i=0;i<drzewo.tabSize;++i)
		printf("%2u ",i);
	putchar('\n');
	for(unsigned int i=0;i<drzewo.tabSize;++i)
		printf("%2u ",drzewo.tab[i]);
	putchar('\n');
	drzewo.addSeg(0,2);
	for(unsigned int i=0;i<drzewo.tabSize;++i)
		printf("%2u ",i);
	putchar('\n');
	for(unsigned int i=0;i<drzewo.tabSize;++i)
		printf("%2u ",drzewo.tab[i]);
	putchar('\n');
	drzewo.addSeg(4,8);
	for(unsigned int i=0;i<drzewo.tabSize;++i)
		printf("%2u ",i);
	putchar('\n');
	for(unsigned int i=0;i<drzewo.tabSize;++i)
		printf("%2u ",drzewo.tab[i]);
	putchar('\n');
	drzewo.addSeg(7,10);
	for(unsigned int i=0;i<drzewo.tabSize;++i)
		printf("%2u ",i);
	putchar('\n');
	for(unsigned int i=0;i<drzewo.tabSize;++i)
		printf("%2u ",drzewo.tab[i]);
	putchar('\n');
	drzewo.addSeg(14,15);
	for(unsigned int i=0;i<drzewo.tabSize;++i)
		printf("%2u ",i);
	putchar('\n');
	for(unsigned int i=0;i<drzewo.tabSize;++i)
		printf("%2u ",drzewo.tab[i]);
	putchar('\n');
	drzewo.addSeg(0,15);
	for(unsigned int i=0;i<drzewo.tabSize;++i)
		printf("%2u ",i);
	putchar('\n');
	for(unsigned int i=0;i<drzewo.tabSize;++i)
		printf("%2u ",drzewo.tab[i]);
	putchar('\n');
	printf("%u %u %u %u %u\n",drzewo.suma(1),drzewo.suma(3),drzewo.suma(7),drzewo.suma(8),drzewo.suma(11));
	#endif
	unsigned int z;
	scanf("%u",&z);
	while(z--)
	{
		unsigned int n;
		scanf("%u",&n);
		event obiekty[2*n];
		event *begin=obiekty,*end=obiekty;
		wynik=new unsigned [n];
		y=new int[2*n];
		int *yE=y;
		for(unsigned i=0;i<n;++i,++end,++yE)
		{
			int x1,x2,y1,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			if(x2<x1)
				swap(x1,x2);
			if(y2<y1)
				swap(y1,y2);
			if(x1==x2)
			{
				end->x=x1;
				end->n=i;
				end->y=y1;
				end->t=y2;
				end->o=pion;
				*yE++=y1;
				*yE=y2;
			}
			else
			{
				end->n=i;
				end->x=x1;
				end->y=y1;
				end->t=y1;
				end->o=poziomB;
				*yE=y1;
				++end;
				end->n=i;
				end->x=x2;
				end->y=y2;
				end->t=y2;
				end->o=poziomE;
			}
		}
		sort(obiekty,end);
		#ifdef sort_debug
		for(event *begin=obiekty;begin!=end;++begin)
		{
			if(begin->t==begin->y)
			{
				printf("Znalazlem poziom x: %d, y: %d, nr: %u\n",begin->x,begin->y,begin->n);
			}
			else
			{
				printf("Znalazlem pion x: %d y1: %d y2: %d nr: %u\n",begin->x,begin->y,begin->t,begin->n);
			}
		}
		#endif
		
		#ifdef obsolete_unique_copy
		/******************** UNIQUE COPY **********************/
		{
			unsigned *wsk=y;
			for(event *beg=begin+1;beg!=end;++beg)
			{
				if(*wsk!=beg->y)
					*++wsk=beg->y;
			}
			sizeY=wsk+1-y;
		}
		/******************** UNIQUE COPY **********************/
		#else
		sort(y,yE);
		sizeY=unique(y,yE)-y;
		yE=y+sizeY;
		#endif
		#ifdef debugY
		printf("%u\n",sizeY);
		for(unsigned i=0;i<sizeY;++i)
			printf("%u\n",y[i]);
		#endif
		
		sumTree licznik(sizeY);
		segTree przedzial(sizeY);
		
		////////////////////////////////////////////////////////////////////////
		
		//printf("Rozmiar Y %u\n",yE-y);
		
		for(;begin!=end;++begin)
		{
			if(begin->o==poziomB)
			{
				//printf("Pozioma %u | x %u y %u początek poz %d suma %u\n",begin->n,begin->x,begin->y,lower_bound(y,yE,begin->y)-y,przedzial.suma(lower_bound(y,yE,begin->y)-y));
				wynik[begin->n]=przedzial.suma(lower_bound(y,yE,begin->y)-y);
				licznik.inc(lower_bound(y,yE,begin->y)-y);
			}
			else if(begin->o==poziomE)
			{
				//printf("Pozioma %u | x %u y %u koniec poz %d suma %u\n",begin->n,begin->x,begin->y,lower_bound(y,yE,begin->y)-y,przedzial.suma(lower_bound(y,yE,begin->y)-y));
				wynik[begin->n]=przedzial.suma(lower_bound(y,yE,begin->y)-y)-wynik[begin->n];
				licznik.dec(lower_bound(y,yE,begin->y)-y);
			}
			else
			{
				//printf("Pionowa %u | x %u y1 %u y2 %u poz1 %d poz2 %d suma %u\n",begin->n,begin->x,begin->y,begin->t,lower_bound(y,yE,begin->y)-y,lower_bound(y,yE,begin->t)-y,licznik.suma(lower_bound(y,yE,begin->y)-y,lower_bound(y,yE,begin->t)-y));
				wynik[begin->n]=licznik.suma(lower_bound(y,yE,begin->y)-y,lower_bound(y,yE,begin->t)-y);
				przedzial.addSeg(lower_bound(y,yE,begin->y)-y,lower_bound(y,yE,begin->t)-y);
			}
		}
		
		////////////////////////////////////////////////////////////////////////
		
		for(unsigned *wsk=wynik,*end=wynik+n;wsk!=end;++wsk)
			printf("%u\n",*wsk);
		
		delete [] y;
		delete [] wynik;
	}
	return 0;
}
