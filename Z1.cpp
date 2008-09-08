#include <stdio.h>

int n;

int main()
{
	scanf("%d",&n);
	int i=n;
	while(--i)
		n*=i;
	printf("%d\n",n);

	return 0;
}

