#include <stdio.h>

unsigned int n;

int main()
{
	scanf("%d",&n);
	if(n==0)
	{
		puts("0");
		return 0;
	}
	unsigned int i=n;
	while(--i)
		n*=i;
	printf("%d\n",n);

	return 0;
}

