#include <cstdio>
#include <algorithm>

#define MAX_LONG_LONG 1000000900

using std::min;

struct eer
{
    long long d,x,y;
    eer(int dd,int xx,int yy) : d(dd),x(xx),y(yy) {}
};

struct mlesr
{
    long long x0,c;
    mlesr() : x0(MAX_LONG_LONG),c(0) {}
};

eer ee(long long a,long long b)
{
    if(b==0)
	return eer(a,1,0);
    eer p=ee(b,a%b);
    return eer(p.d,p.y,p.x-(a/b)*p.y);
}

mlesr mles(long long a,long long b,long long n)
{
    eer p=ee(a,n);
    if(b%p.d)
	return mlesr();
    mlesr r;
    long long x0=p.x*(b/p.d)%n;
    for(int i=0;i<p.d;++i)
	++r.c,r.x0=min(r.x0,(x0+i*(n/p.d))%n);
    return r;
}

int main()
{
    /*while(2)
    {
	int a,b;
	scanf("%d%d",&a,&b);
	eer w=ee(a,b);
	printf("%d %d %d\n",w.d,w.x,w.y);
    }*/
    int z;
    scanf("%d",&z);
    while(z--)
    {
	int a,b,n;
	scanf("%d%d%d",&a,&b,&n);
	if(a<0)
	    a=-a,b=-b;
	mlesr w=mles(a,b,n);
	if(w.c)
	{
	    while(w.x0<0)
		w.x0+=n;
	    printf("%lld %lld\n",w.c,w.x0);
	}
	else
	    printf("0\n");
    }

    return 0;
}

