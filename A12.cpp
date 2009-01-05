#include <cstdio>
#include <stdint.h>

template<class T>
void swap(T &a,T &b)
{
	T tmp=a;
	a=b;
	b=tmp;
}

struct tablica
{
	uint8_t v[7];
	
	void operator=(const tablica &o)
	{
		v[0]=o.v[0];
		v[1]=o.v[1];
		v[2]=o.v[2];
		v[3]=o.v[3];
		v[4]=o.v[4];
		v[5]=o.v[5];
		v[6]=o.v[6];
	}
	
	#ifdef use_obsolete_storage
	uint8_t get(size_t o)
	{
		return (v/(pow(10,7-o)))%10;
	}
	
	void operator=(const tablica &o)
	{
		c[0]=o.c[0];
		c[1]=o.c[1];
		v=o.v;
	}
	#endif
};

bool cmp(uint8_t *ptrS,uint8_t *ptrD,size_t s)
{
	if(s>=4)
	{
		uint32_t *cS_ptr=reinterpret_cast<uint32_t*>(ptrS);
		uint32_t *cD_ptr=reinterpret_cast<uint32_t*>(ptrD);
		s-=4;
		ptrS+=4;
		ptrD+=4;
		if(*cS_ptr!=*cD_ptr)
			return false;
	}
	if(s>=2)
	{
		uint16_t *cS_ptr=reinterpret_cast<uint16_t*>(ptrS);
		uint16_t *cD_ptr=reinterpret_cast<uint16_t*>(ptrD);
		s-=2;
		ptrS+=2;
		ptrD+=2;
		if(*cS_ptr!=*cD_ptr)
			return false;
	}
	if(s==1)
	{
		uint8_t *cS_ptr=reinterpret_cast<uint8_t*>(ptrS);
		uint8_t *cD_ptr=reinterpret_cast<uint8_t*>(ptrD);
		if(*cS_ptr!=*cD_ptr)
			return false;
	}
	return true;
}

uint32_t	n;
uint32_t	tmp[26];
tablica		*dane1;
tablica		*dane2;
tablica		*beg1;
tablica		*beg2;
tablica		*end1;
tablica		*end2;


int main()
{
	uint32_t z;
	scanf("%u",&z);
	while(z--)
	{
		scanf("%u",&n);
		dane1=new tablica[n];
		dane2=new tablica[n];
		
		for(beg1=dane1,end1=dane1+n;beg1!=end1;++beg1)
		{
			scanf(" %c%c",beg1->v,&beg1->v[1]);
			beg1->v[2]=getchar()-'0';
			beg1->v[3]=getchar()-'0';
			beg1->v[4]=getchar()-'0';
			beg1->v[5]=getchar()-'0';
			beg1->v[6]=getchar()-'0';
		}
		
		for(size_t i=6;i>=2;--i)
		{
			for(uint32_t *wsk=tmp,*end=tmp+10;wsk!=end;++wsk)
				*wsk=0;
			
			for(beg1=dane1;beg1!=end1;++beg1)
				++tmp[beg1->v[i]];
			
			for(uint32_t *wsk=tmp+1,*end=tmp+10;wsk!=end;++wsk)
			{
				*wsk+=*(wsk-1);
			}
			
			for(beg1=dane1-1,end1=dane1+n-1;beg1!=end1;--end1)
			{
				dane2[tmp[end1->v[i]]-1]=*end1;
				--tmp[end1->v[i]];
			}
			
			swap(dane1,dane2);
			beg1=dane1;
			end1=dane1+n;
			beg2=dane2;
			end2=dane2+n;

			tablica	*w=beg1;
			tablica	*t1=beg1+1;
			size_t	max=1;
			size_t	t2=1;

			for(;t1!=end1;++t1)
			{
				if(cmp(t1->v+i,(t1-1)->v+i,7-i))
				{
					++t2;
					if(t2>max)
					{
						max=t2;
						w=t1;
					}
				}
				else
					t2=1;
			}

			for(size_t j=i;j<7;++j)
				printf("%u",w->v[j]);
			putchar(' ');
		}
		for(int i=1;i>=0;--i)
		{
			for(uint32_t *wsk=tmp,*end=tmp+26;wsk!=end;++wsk)
				*wsk=0;
			
			for(beg1=dane1;beg1!=end1;++beg1)
				++tmp[beg1->v[i]-65];
			
			for(uint32_t *wsk=tmp+1,*end=tmp+26;wsk!=end;++wsk)
				*wsk+=*(wsk-1);
			
			for(beg1=dane1-1,end1=dane1+n-1;beg1!=end1;--end1)
			{
				dane2[tmp[end1->v[i]-65]-1]=*end1;
				--tmp[end1->v[i]-65];
			}
			
			swap(dane1,dane2);
			beg1=dane1;
			end1=dane1+n;
			beg2=dane2;
			end2=dane2+n;

			tablica	*w=beg1;
			tablica	*t1=beg1+1;
			size_t	max=1;
			size_t	t2=1;

			for(;t1!=end1;++t1)
			{
				if(cmp(t1->v+i,(t1-1)->v+i,7-i))
				{
					++t2;
					if(t2>max)
					{
						max=t2;
						w=t1;
					}
				}
				else
					t2=1;
			}

			for(size_t j=i;j<2;++j)
				printf("%c",w->v[j]);
			for(size_t j=2;j<7;++j)
				printf("%u",w->v[j]);
			putchar(' ');
		}
		putchar('\n');

		for(int i=0;i<n;++i)
			printf("%c%c%u%u%u%u%u\n",dane1[i].v[0],dane1[i].v[1],dane1[i].v[2],dane1[i].v[3],dane1[i].v[4],dane1[i].v[5],dane1[i].v[6]);
		
		delete [] dane1;
		delete [] dane2;
	}
	return 0;
}

