#include <cstdio>
#include <cmath>

int main()
{
    int z;
    scanf("%d",&z);
    while(z--)
    {
	long long n,w,t;
	scanf("%lld",&n);
	t=w=sqrt(n);
	for(long long i=1;i<=t;++i)
	    w+=2*((n-i*i)/i);
	printf("%lld\n",w);
    }
    return 0;
}
