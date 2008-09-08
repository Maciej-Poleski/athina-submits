#include <cstdio>

char *tab,z;
unsigned int n;

int main()
{
	scanf("%d",&n);
	getchar();
	tab=new char[1000];
	while(n--)
	{
		unsigned int i=0;
		while((z=getchar())!='\n')
			tab[i++]=z;
		while(i)
			putchar(tab[--i]);
		puts("");
	}

	return 0;
}


