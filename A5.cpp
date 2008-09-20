#include <cstdio>

int *tab,tmp;
unsigned int z,n,q;

unsigned int findF(unsigned int l,unsigned int p,int x)
{
    unsigned int s;
    while(l<p)
    {
	s=(l+p)/2;
	if(tab[s]<x)
	    l=s+1;
	else
	    p=s;
    }
    return l;
}

unsigned int findL(unsigned int l,unsigned int p,int x)
{
    unsigned int s;
    while(l<p)
    {
	s=(l+p)/2;
	#ifdef debug
	printf("l: %u s: %u p: %u\n",l,s,p);
	#endif
	if(tab[s]<=x)
	    l=s+1;
	else
	    p=s;
    }
    return l;
}

int main()
{
    scanf("%u",&z);
    while(z--)
    {
	scanf("%u",&n);
	tab=new int[n];
	for(unsigned int i=0;i<n;++i)
	    scanf("%d",tab+i);
	scanf("%u",&q);
	while(q--)
	{
	    scanf("%d",&tmp);
	    printf("%u\n",findL(0,n,tmp)-findF(0,n-1,tmp));
	}
	delete [] tab;
    }
    return 0;
}
