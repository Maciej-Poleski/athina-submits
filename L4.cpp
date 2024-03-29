#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX_LONG_LONG 5000000900LL

using std::min;

//! Wynik zwracany przez funkcję realizującą rozszerzony algorytm euklidesa
struct eer
{
    long long d,x,y;
    eer(int dd,int xx,int yy) : d(dd),x(xx),y(yy) {}
};

//! Wynik zwracany przez funkcję rozwiązującą równanie modularne
struct mlesr
{
    long long x0,x1,c;
    mlesr() : x0(MAX_LONG_LONG),x1(MAX_LONG_LONG),c(0LL) {}
    mlesr(long long aa,long long bb,long long cc) : x0(aa),x1(bb),c(cc) {}

    //! Dodaje do zbioru rozwiązań wynik
    void add(long long what)
    {
	if(what<x0)
	{
	    x1=x0;
	    x0=what;
	}
	else if(what<x1)
	{
	    x1=what;
	}
    }
};

//! Rozszerzony algorytm euklidesa
inline eer ee(long long a,long long b)
{
    if(b==0)
	return eer(a,1,0);
    eer p=ee(b,a%b);
    return eer(p.d,p.y,p.x-(a/b)*p.y);
}

//! Oblicza ilość rozwiązań równania modularnego i jego najmniejsze rozwiązanie
/*! - a - całkowite
 *  - b - całkowite
 *  - n - dodatnie
 */
inline mlesr mles(long long a,long long b,long long n)
{
    if(b<0)
	b=-b,a=-a;
    b%=n;
    if(n==1)
	return mlesr(0,1,1);
    if(a==0 && b==0)
	return mlesr(0,1,n);
    if(a==0)
	return mlesr();
    if(a<0)
	a=-a,b=-b;
    eer p=ee(a,n);
    if(b%p.d)
	return mlesr();
    mlesr r;
    long long x0=p.x*(b/p.d);
    if(x0<0)
    {
	x0+=n*((-x0)/n);
    	if(x0<0)
	    x0+=n;
    }
    x0%=n;
    for(int i=0;i<p.d;++i)
	++r.c,r.add((x0+i*(n/p.d))%n);
    return r;
}

int main()
{
    int z;
    scanf("%d",&z);
    while(z--)
    {
	int m;
	int bad=0;
	scanf("%d",&m);
	long long a[m];
	long long b[m];
	long long n[m];
	bool e[m];
	bool ok=true;
	memset(e,0,m);
	for(int i=0;i<m;++i)
	    scanf("%lld%lld%lld",a+i,b+i,n+i);
	for(int i=0;i<m;++i)
	    a[i]%=n[i],b[i]%=n[i];
	for(int i=0;i<m;++i)
	{
	    if(a[i]==0)
	    {
		if(b[i]==0)
		    ++bad,e[i]=true;
		else
		{
		    printf("NIE\n");
		    ok=false;
		    break;
		}
	    }
	}
	if(!ok)
	    continue;
	for(int i=0;i<m;++i)
	{
	    if(e[i])
		continue;
	    if(b[i]%ee(a[i]<0?-a[i]:a[i],n[i]).d)
	    {
		printf("NIE\n");
		ok=false;
		break;
	    }
	}
	if(!ok)
	    continue;
	if(m-bad==1)
	{
	    int i=0;
	    while(e[i])
		++i;
	    mlesr w=mles(a[i],b[i],n[i]);
	    if(w.c==0)
	    {
		printf("NIE\n");
		continue;
	    }
	    else if(w.c==1)
	    {
		if(w.x0==0)
		    w.x0=n[i];
		printf("%lld %lld\n",w.x0,w.x0+n[i]);
		continue;
	    }
	    else
	    {
		if(w.x0==0)
		{
		    w.x0=w.x1;
		    w.x1+=n[i];
		}
		printf("%lld %lld\n",w.x0,w.x1);
		continue;
	    }
	}
	else if(m-bad==0)
	{
	    printf("1 2\n");
	    continue;
	}
	/*
	long long A=1;
	for(int i=0;i<m;++i)
	    A*=e[i]?1:a[i];
	//long long B=1;
	//for(int i=0;i<m;++i)
	//    B*=b[i];
	long long M=1;
	for(int i=0;i<m;++i)
	    M*=e[i]?1:n[i];
	long long x=0;
	for(int i=0;i<m;++i)
	{
	    if(e[i])
		continue;
	    //printf("%d: %lld %lld\n",i+1,ee(n[i],M/n[i]).x,ee(n[i],M/n[i]).y);
	    //printf("%lld*%lld*%lld*%lld\n",ee(n[i],M/n[i]).y,(M/n[i]),(long long)b[i],(A/a[i]));
	    x+=(ee(n[i],M/n[i]).y*(M/n[i]))*(((b[i]*(A/a[i])))%n[i]);
	}
	//printf("%lld %lld\n",x/n[0],x/n[1]);
	A%=M;
	while(x<0)
	    x+=M;
	while(x%A)
	    x+=M;
	x/=A;
	if(x>M || x<0)
	{
	    //x-=(x/M)*M;
	    x%=M;
	}
	if(x<0)
	    x+=M;
	printf("%lld %lld\n",x,x+M);*/
	ok=true;
	for(int i=0;i<m;++i)
	{
	    if(e[i])
		continue;
	    if(a[i]<0)
		a[i]=-a[i],b[i]=-b[i];
	    eer dd=ee(a[i],n[i]);
	    a[i]/=dd.d;
	    //if(b[i]%dd.d)
		//throw 2;
	    b[i]/=dd.d;
	    n[i]/=dd.d;
	    mlesr t=mles(a[i],1,n[i]);
	    if(t.c==0)
	    {
		printf("NIE\n");
		//fprintf(stderr,"__203__\n");
		ok=false;
		break;			// CHOKE ME
	    }
	    a[i]*=t.x0;
	    a[i]%=n[i];
	    //if(a[i]!=1)
	    //	fprintf(stderr,"a[%d]: %d\n",i,a[i]);
	    b[i]*=t.x0;
	    b[i]%=n[i];
	    //fprintf(stderr,"b[%d]: %d\n",i,b[i]);
	}
	if(!ok)
	    continue;
	//long long A=1;
	//for(int i=0;i<m;++i)
	//    A*=e[i]?1:a[i];
	//long long B=1;
	//for(int i=0;i<m;++i)
	//    B*=b[i];
	long long M=1;
	for(int i=0;i<m;++i)
	    M*=e[i]?1:n[i];
	long long x=0;
	for(int i=0;i<m;++i)
	{
	    if(e[i])
		continue;
	    //printf("%d: %lld %lld\n",i+1,ee(n[i],M/n[i]).x,ee(n[i],M/n[i]).y);
	    //printf("%lld*%lld*%lld*%lld\n",ee(n[i],M/n[i]).y,(M/n[i]),(long long)b[i],(A/a[i]));
	    x+=(ee(n[i],M/n[i]).y*(M/n[i]))*b[i];
	}
	x%=M;
	while(x<0)
	    x+=M;
	if(x==0)
	    x=M;
	printf("%lld %lld\n",x,x+M);
    }
    return 0;
}

