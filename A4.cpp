#include <cstdio>

unsigned int n;

int main()
{
    unsigned int size;
    int *tab,wynik,tmp,scan;
    scanf("%u",&n);
    while(n--)
    {
	scanf("%u",&size);
	tab=new int[size];
	wynik=tmp=0;
	for(unsigned int i=0;i<size;++i)
	{
	    scanf("%u",&scan);
	    if(tmp>=0)
		tmp+=scan;
	    else
		tmp=scan;
	    if(tmp>wynik)
		wynik=tmp;
	}
	printf("%u\n",wynik);
	delete [] tab;
    }
    return 0;
}
