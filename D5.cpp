#include <cstdio>
#include <cstring>
#include <stdint.h>

/* Obsługiwana jest tylko architektura o kolejności bajtów Little-endian */
/* Wczesne wiązanie */
#define pow2(i)     ((1)<<(i))
#define get(x,i)    (((x)>>(i))&(1))
#define set(x,i)    ((x)=((x)|(pow2(i))))
#define clear(x,i)  ((CHOKE ME!))             // Tego nie potrzebujemy!

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

int main()
{
    int z;
    scanf("%d\n",&z);
    while(z--)
    {
	scanf("%d\n",&n);
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
    }
    return 0;
}
