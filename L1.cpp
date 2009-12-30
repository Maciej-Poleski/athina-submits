#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

const int MAX_SIZE=100000001;

bool *sito;
int  *prime;
int pc=0;

long long pow(long long n,int k)
{
    long long w=1;
    for(int i=0;i<k;++i)
	w*=n;
    return w;
}

int main()
{
    /* generuje sito */
    sito=new bool[MAX_SIZE+5];
    memset(sito,0,MAX_SIZE+5);
    for(int i=3;i<=MAX_SIZE;i+=2)
    {
	if(sito[i])
	{
	    continue;
	}
	++pc;
	if(static_cast<long long>(i)*i>MAX_SIZE)
	    continue;
	for(int j=i*i;j<=MAX_SIZE;j+=i)
	{
	    sito[j]=true;
	}
    }
    prime=new int[pc+2];
    {
	int *ptr=prime;
	*ptr++=2;
	for(int i=3;i<=MAX_SIZE;i+=2)
	    if(!sito[i])
		*ptr++=i;
	*ptr++=100000007;
    }
    delete [] sito;
    int z;
    scanf("%d",&z);

    while(z--)
    {
	long long x,xx;
	long long w=1;
	int k=0;
	scanf("%lld",&x);

	xx=x;

	if(x==1)
	{
	    printf("1 0\n");
	    continue;
	}

	/* Faktoryzuje i obliczam e(x) */

	while((x&1)==0)		// 2 jest wyjątkowe
	    ++k,x>>=1;

	if(k>0)
	{
		w=(1L<<k)-(1L<<(k-1));
	}

	// Faktoryzacja właściwa

	for(int i=1;x>1 && i<=pc;++i)
	{
	    k=0;
	    int p=prime[i];
	    while(x%p==0)
		++k,x/=p;
	    if(k==0)
		continue;
	    w*=pow(p,k-1)*(p-1);
	}
	if(x>1)
	{
	    w*=x-1;
	}

	int l;
	printf("%lld %d\n",w,((l=std::lower_bound(prime,prime+pc+1,(k=(int)sqrt(xx)))-prime),prime[l]==k?l+1:l));
    }
    delete [] prime;
    return 0;
}
