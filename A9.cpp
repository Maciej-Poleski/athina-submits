#include <cstdio>

template<class T>
unsigned int merge(T *tab,unsigned int l,unsigned int s,unsigned int p)
{
    unsigned int wynik=0,lt=l,st=s,pt=p;
    T *tmp=new T[p-l];
    T *end=tmp+(p-l);
    T *wsk=tmp;
    for(;wsk!=end;++wsk)
    {
		if(tab[st]>tab[lt])
		{
		    wynik+=s-lt;
		    *wsk=tab[st];
		    ++st;
		}
		else
		{
		    *wsk=tab[lt];
		    ++lt;
		}
		if(lt==s || st==p)
		{
			++wsk;
		    break;
		}
    }
    if(st==p)
    {
		while(lt!=s)
		{
			*(wsk++)=tab[lt++];
		}
    }
    else if(lt==s)
    {
		while(st!=p)
		{
		    *(wsk++)=tab[st++];
		}
    }
    
    for(unsigned int i=l;i<p;++i)
		tab[i]=tmp[i-l];
		
//	printf("\tWartości w tablicy tymczasowej dla |l: %u| |s: %u| |p: %u|  Wynik: %u\n\t",l,s,p,wynik); 
	
//	for(unsigned int i=0;i<p-l;++i)
//		printf("%d ",tmp[i]);
    
//    putchar('\n');
    
    delete [] tmp;
    
    return wynik;
}

template<class T>
unsigned int mergesort(T *tab,unsigned int l,unsigned int p)
{
    unsigned int s=(l+p)/2,wynik=0;
    if(p-l>1)
    {
		wynik+=mergesort(tab,l,s);
		wynik+=mergesort(tab,s,p);
    }
//    printf("Dla tablicy |l: %u| |s: %u| |p: %u|\n",l,s,p);
//    for(unsigned int i=l;i<p;++i)
//    	printf("%d ",tab[i]);
//    putchar('\n');
    return wynik+merge(tab,l,s,p);
}

int main()
{
    unsigned int z;
    scanf("%u",&z);
    while(z--)
    {
		unsigned int n;
		scanf("%u",&n);
		int *tab=new int[n];
		for(unsigned int i=0;i<n;++i)
	    	scanf("%d",tab+i);
		printf("%u\n",mergesort(tab,0,n));
//		for(unsigned int i=0;i<n;++i)
//		    printf("%d ",tab[i]);
//		putchar('\n');
		delete [] tab;
    }
    
    return 0;
}
