#include <cstdio>
#include <cmath>
using namespace std;

double x,y,c;

double f(double w)
{
	return 1/sqrt(x*x-w*w)+1/sqrt(y*y-w*w)-1/c;
}

double min(double l,double p)
{
	if(l<p)
		return l;
	return p;
}

int main()
{
	unsigned int z;
	scanf("%u",&z);
	while(z--)
	{
		scanf("%la%la%la",&x,&y,&c);
		double tmp=min(x,y)/2,st=tmp/2,pr=0.0000000001;
		while(f(tmp) && st)
		{
			if(f(tmp)<0)
				tmp+=st;
			else
				tmp-=st;
			st/=2;
		}
		printf("%.3f\n",tmp);
	}
	return 0;
}
