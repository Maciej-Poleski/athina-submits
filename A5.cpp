#include <cstdio>

//#define debug

int *tab,tmp;
unsigned int z,n,q;

unsigned int findF(unsigned int l,unsigned int p,int x)
{
    #ifdef debug
    puts("findF");
    #endif
    unsigned int s;
    while(l<p)
    {
	s=(l+p)/2;
	#ifdef debug
	printf("l: %u s: %u p: %u\n",l,s,p);
	#endif
	if(tab[s]<x)
	    l=s+1;
	else
	    p=s;
    }
    #ifdef debug
    printf("l: %u s: %u p: %u\n",l,s,p);
    if(tab[z-1]<x)
    #else
    if(tab[n-1]<x)
    #endif
	++l;
    return l;
}

unsigned int findL(unsigned int l,unsigned int p,int x)
{
    #ifdef debug
    puts("findL");
    #endif
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
    #ifdef debug
    printf("l: %u s: %u p: %u\n",l,s,p);
    #endif
    return l;
}

int main()
{
    scanf("%u",&z);
    #ifndef debug
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
    #else
    tab=new int[z];
    for(unsigned int i=0;i<z;++i)
	scanf("%d",tab+i);
    while(true)
    {
	scanf("%d",&tmp);
	n=findF(0,z-1,tmp);
	q=findL(0,z,tmp);
	printf("Początek: %u Koniec: %u Ilość: %u\n",n,q,q-n);
    }
    #endif
    return 0;
}
