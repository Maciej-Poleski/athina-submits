#include <cstdio>
#include <stdint.h>
#include <cstdlib>
#include <ctime>

#ifdef stl_sort
#include <algorithm>
#endif

template<class T>
inline void swap(T &a,T &b)
{
	T tmp=a;
	a=b;
	b=tmp;
}

int32_t *A;

inline uint32_t quicksort_partition(uint32_t l,uint32_t r)
{
	swap(A[l],A[(rand()%(r-l))+l]);
	int32_t		v=A[l];
	uint32_t	i=l;
	uint32_t	j=r+1;
	do
	{
		do
		{
			++i;
		} while(i<=r && A[i]<v);
		
		do
		{
			--j;
		} while(j>=1 && A[j]>v);
		
		if(i<j)
			swap(A[i],A[j]);
	} while(i<j);
	
	A[l]=A[j];
	A[j]=v;
	return j;
}

inline void quicksort(uint32_t l,uint32_t r)
{
	if(l<r)
	{
		uint32_t q=quicksort_partition(l,r);
		quicksort(l,q-1);
		quicksort(q+1,r);
	}
}

int main()
{
	uint32_t z;
	srand(time(0));
	scanf("%u",&z);
	while(z--)
	{
		uint32_t n;
		scanf("%u",&n);
		A=new int32_t[n+1];
		for(int32_t *wsk=A+1,*end=A+n+1;wsk!=end;++wsk)
			scanf("%d",wsk);
		#ifndef stl_sort
		quicksort(1,n);
		#else
		std::sort(A+1,A+n+1);
		#endif
		for(int32_t *wsk=A+1,*end=A+n+1;wsk!=end;++wsk)
			printf("%d ",*wsk);
		putchar('\n');
		delete [] A;
	}
	return 0;
}
