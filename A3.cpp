#include <cstdio>

inline unsigned int nwd(unsigned int a,unsigned int b)
{
    unsigned int c;
    while(b!=0)
    {
	c=a%b;
	a=b;
	b=c;
    }
    return a;
}

int main()
{
    unsigned int m,n,z;
    scanf("%u",&z);
    while(z--)
    {
	scanf("%u%u",&m,&n);
	printf("%u\n",nwd(m,n));
    }
    return 0;
}
