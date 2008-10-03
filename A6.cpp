#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

long double x,y,c;

long double f(long double w)
{
	return 1/sqrt(x*x-w*w)+1/sqrt(y*y-w*w)-1/c;
}

long double min(long double l,long double p)
{
	if(l<p)
		return l;
	return p;
}

int main()
{
	ios_base::sync_with_stdio(0);
	unsigned int z;
	cin>>z;
	while(z--)
	{
		cin>>x>>y>>c;
		long double tmp=min(x,y)/2,st=tmp/2,pr=0.0000000001;
		while(abs(f(tmp))-pr>0)
		{
			if(f(tmp)<0)
				tmp+=st;
			else
				tmp-=st;
			st/=2;
		}
		cout<<fixed<<setprecision(3)<<tmp<<'\n';
	}
	return 0;
}