/* Wersja maksymalnie optymalizowana */

#include <cstdio>
#include <cstring>
#include <stdint.h>

/* Obsługiwana jest tylko architektura o kolejności bajtów Little-endian */
/* Wczesne wiązanie */
#define pow2(i)     ((1)<<(i))
#define get(x,i)    (((x)>>((i)-(1)))&(1))
#define set(x,i)    ((x)=((x)|(pow2((i)-(1)))))
#define clear(x,i)  ((x)=((x)&(~(pow2((i)-(1))))))

#ifdef ENABLE_OBSOLETE_CODE
int      n;
uint32_t T[20];                               // Wystarczy

uint64_t compute(uint8_t k)
{
    uint32_t backup;
    uint64_t wynik=static_cast<uint64_t>(0);
    if(k==n)
	return static_cast<uint64_t>(1);
    for(int i=0;i<n;++i)
	if(!get(T[i],k))
	{
	    backup=T[i];
	    T[i]=~(static_cast<uint32_t>(0));
	    wynik+=compute(k+1);
	    T[i]=backup;
	}
    return wynik;
}
#else
int        n;
uint64_t   T[1<<21];
bool       A[21][21];

int bitcount(uint32_t x)
{
    int w=0;
    for(int i=1;i<=20;++i)
	w+=get(x,i);
    return w;
}

#endif

int main()
{
    int z;
    scanf("%d\n",&z);
    while(z--)
    {
	scanf("%d\n",&n);
#ifdef USE_OBSOLETE_CODE
	memset(T,0,n*4);
	for(int i=0;i<n;++i)
	{
	    for(int j=0;j<n;++j)
	    {
		getchar()=='o'?set(T[i],j):false;
	    }
	    getchar();
	}
	printf("%llu\n",compute(static_cast<uint8_t>(0)));
#else
	for(int i=1;i<=n;++i)
	{
	    for(int j=1;j<=n;++j)
	    {
		A[i][j]=((getchar()=='.')?true:false);
	    }
	    getchar();
	}
	T[0]=1;
	for(uint32_t S=1;S<(1<<n);++S)
	{
	    T[S]=0;
	    for(int k=1;k<=20;++k)
	    {
		if(get(S,k))
		{
		    T[S]+=A[bitcount(S)][k]*T[S&(~(1<<(k-1)))];
		}
		if((S>>(k))==0)
			break;
	    }
	}
	printf("%llu\n",T[(1<<n)-1]);
#endif
    }
    return 0;
}
