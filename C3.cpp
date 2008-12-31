#include <cstdio>
#include <stdint.h>
#include <algorithm>
using namespace std;

inline unsigned int mpow2(unsigned int n)
{
	unsigned int wynik=1;
	while(wynik<n)
		wynik<<=1;
	return wynik;
}

class intTree
{
	struct node
	{
		size_t	pokrycie;
		size_t	v;
		int		vl;
		int		vr;
	};
	int*	eY;
	size_t	seY;
	int*	eeY;
	node*	tab;
	size_t	stab;
	size_t	size;
	
	void rebuild_add(size_t n,size_t v)
	{
		tab[n].pokrycie+=v;
		n>>=1;
		while(n && !tab[n].v)
		{
			tab[n].pokrycie+=v;
			n>>=1;
		}
	}
	
	void rebuild_sub(size_t n)
	{
		if(tab[n].v)
			return;
		
		size_t v;
		
		if(((n<<1)|1)<stab)
			v=tab[n].pokrycie-(tab[n<<1].pokrycie+tab[(n<<1)|1].pokrycie);
		else
			v=tab[n].pokrycie;
		
		while(n && !tab[n].v)
		{
			tab[n].pokrycie-=v;
			n>>=1;
		}
	}
	
	void add(size_t l,size_t r)
	{
		size_t sub=r-l;
		while(sub)
		{
			size_t	i=1;
			size_t	n=l;
			for(;!(n&1) && i<<1<=sub;i<<=1,n>>=1)
				;
			l+=i;
			sub-=i;
			++tab[n].v;
			rebuild_add(n,(tab[n].vr-tab[n].vl)-tab[n].pokrycie);
		}
	}
	
	void sub(size_t l,size_t r)
	{
		size_t sub=r-l;
		//printf("%u %u   %u<br />\n",l,r,sub);
		while(sub)
		{
			size_t	i=1;
			size_t	n=l;
			for(;!(n&1) && i<<1<=sub;i<<=1,n>>=1);
			l+=i;
			sub-=i;
			--tab[n].v;
			rebuild_sub(n);
		}
	}
	
	public:
		
		intTree(int* eYP,size_t seYP) : eY(eYP), seY(seYP),size(mpow2(seYP-1)),eeY(eYP+seYP)
		{
			size_t i=0;
			int* wtmp=eY;
			tab=new node[stab=(size<<1)-1];
			--tab;
			for(node *wsk=tab+size,*end=wsk+size;wsk!=end;++wsk)
			{
				wsk->pokrycie=wsk->v=0;
				if(++i<seY)
				{
					wsk->vl=*wtmp++;
					wsk->vr=*wtmp;
				}
			}
			for(size_t i=size-1;i;--i)
			{
				node*	wsk=tab+i;
				size_t	child=i<<1;
				wsk->pokrycie=wsk->v=0;
				wsk->vl=tab[child].vl;
				wsk->vr=tab[++child].vr;
			}
		}
		
		~intTree()
		{
			//delete [] eY;
			delete [] ++tab;
		}
		
		void addInterval(int l,int r)
		{
			add(lower_bound(eY,eeY,l)-eY+size,lower_bound(eY,eeY,r)-eY+size);
		}
		
		void subInterval(int l,int r)
		{
			sub(lower_bound(eY,eeY,l)-eY+size,lower_bound(eY,eeY,r)-eY+size);
		}
		
		size_t get_overlay() const
		{
			return (tab+1)->pokrycie;
		}
};

struct event
{
	int x,y1,y2;
	
	bool operator<(const event& o) const
	{
		return x<o.x || (x==o.x && y2<y1 && o.y1<o.y2);
	}
	
	bool is_begin() const
	{
		return y1<y2;
	}
};
#ifdef intTree_test
void print_t(intTree &drzewo)
{
	printf("<table border=2 cellspacing=0 width=100%>\n<tr>\n");
	for(size_t i=1;i<=drzewo.stab;++i)
	{
		size_t cols=(i==mpow2(i)?drzewo.size/i:drzewo.size/(mpow2(i)/2));
		printf("<td colspan=%u>\n",cols);
		
		printf("<center><table  border=0>\n<tr>\n<td colspan=2 align=center>%u</td>\n</tr><tr>\n<td colspan=2 align=center>%u</td>\n</tr>\n<tr>\n<td align=center>%d</td><td align=center>%d</td>\n</tr>\n</table></center>\n",drzewo.tab[i].v,drzewo.tab[i].pokrycie,drzewo.tab[i].vl,drzewo.tab[i].vr);
		
		printf("</td>\n");
		
		if(i==mpow2(i)-1 || i==1)
			printf("</tr>\n<tr>\n");
	}
	printf("</table>");
}
#endif

int main()
{
	#ifdef intTree_test
	int *tab=new int[9];
	tab[0]=-2;
	tab[1]=0;
	tab[2]=3;
	tab[4]=6;
	tab[5]=8;
	tab[6]=9;
	tab[7]=13;
	tab[8]=14;
	size_t tabs=9;
	intTree drzewo(tab,tabs);
	
	print_t(drzewo);
	
	drzewo.addInterval(3,13);
	print_t(drzewo);
	drzewo.addInterval(0,6);
	print_t(drzewo);
	drzewo.addInterval(-2,9);
	print_t(drzewo);
	drzewo.addInterval(0,14);
	print_t(drzewo);
	drzewo.addInterval(6,8);
	print_t(drzewo);
	drzewo.subInterval(0,14);
	print_t(drzewo);
	drzewo.subInterval(-2,9);
	print_t(drzewo);
	#else
	
	size_t z;
	
	scanf("%u",&z);
	while(z--)
	{
		size_t		m;
		scanf("%u",&m);
		
		int			y[m*2];
		int			x;
		uint64_t	wynik=0;
		event		space2D[m*2];
		
		int*		yB=y;
		int*		yE=y;
		event*		space2DB=space2D;
		event*		space2DE=space2D;
		
		for(size_t i=0;i<m;++i)
		{
			int		x1;
			int		x2;
			int		y1;
			int		y2;
			
			scanf("%d%d%d%d",&x1,&x2,&y1,&y2);
			
			if(x1==x2 || y1==y2)
				continue;
			
			*yE++			=	y1;
			*yE++			=	y2;
			
			space2DE->x		=	x1;
			space2DE->y1	=	y1;
			space2DE->y2	=	y2;
			
			++space2DE;
			
			space2DE->x		=	x2;
			space2DE->y1	=	y2;
			space2DE->y2	=	y1;
			
			++space2DE;
		}
		
		if(space2DB==space2DE)
		{
			puts("0");
			continue;
		}
		
		sort(yB,yE);
		
		yE=unique(yB,yE);
		
		intTree		space1D(yB,yE-yB);
		
		sort(space2DB,space2DE);
		
		#ifdef dump_y
		for(size_t i=0;y+i<yE;++i)
		{
			printf("%d ",y[i]);
		}
		puts("\nKoniec dump_y");
		#endif
		
		#ifdef dump_space2D
		for(size_t i=0;space2D+i<space2DE;++i)
		{
			printf("%u ",i);
			if(space2D[i].y1<space2D[i].y2)
			{
				printf("Początek: x %d\t| y1 %d\t| y2 %d\n",space2D[i].x,space2D[i].y1,space2D[i].y2);
			}
			else
			{
				printf("Koniec:   x %d\t| y1 %d\t| y2 %d\n",space2D[i].x,space2D[i].y2,space2D[i].y1);
			}
		}
		puts("Koniec dump_space2D");
		#endif
		
		x=space2DB->x;
		
		for(size_t i=0;space2DB!=space2DE;++space2DB,++i)
		{
			fflush(stdout);
			if(space2DB->x!=x)
			{
				wynik+=space1D.get_overlay()*(space2DB->x-x);
				x=space2DB->x;
			}
			
			if(space2DB->is_begin())
				space1D.addInterval(space2DB->y1,space2DB->y2);
			else
			{
				space1D.subInterval(space2DB->y2,space2DB->y1);
			}
		}
		
		printf("%llu\n",wynik);
	}
	
	#endif
	
	return 0;
}
