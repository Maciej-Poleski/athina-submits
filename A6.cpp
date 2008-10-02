#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

double x,y,c_;

inline double f(double w)
{
	return ((1.0/sqrt((y*y)-(w*w)))+(1.0/sqrt((x*x)-(w*w))))-1/c_;
}

inline double min(double l,double p)
{
	if(l<p)
		return l;
	else
		return p;
}

int main()
{
	ios_base::sync_with_stdio(0);
	unsigned int z;
	cin>>z;
	while(z--)
	{
	double a,b,c,d, pr=0.00001;
	cin>>x>>y>>c_;
	if(c_==0)
	{
		cout<<min(x,y)<<'\n';
		continue;
	}
	if(x==0 || y==0)
	{
		cout<<"0.000\n";
		continue;
	}
	a=x;b=y;
	c=min(a,b)/2;
	a-=0.00001;b-=0.00001;
	do
	{
		//cout<<"a = "<<a<<" b = "<<b<<" r��nica: "<<abs(b-a)<<" c = ";
		//cout<<c<<" f(a) = "<<f(a)<<" f(c) = "<<f(c)<<endl;
		if (f(a)*f(c)<0)
			b = c;
		else
			a = c;
		//cout<<"a = "<<a<<" b = "<<b<<endl;
		c = (a+b)/2;
	} while (abs(b-a) > pr);
	cout<<fixed<<setprecision(3)<<c<<'\n';
// 	while(true)
// 	{
// 		cin>>d;
// 		cout<<f(d)<<endl;
// 	}
	}
	return 0;
}
