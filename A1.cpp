#include <cstdio>
#include <algorithm>

using namespace std;

int n,i,*tab;

int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d",&i);
		tab=new int[i];
		for(int j=0;j<i;++j)
		{
			scanf("%d",tab+j);
		}
		sort(tab,tab+i);
		for(int j=0;j<i;++j)
			printf("%d ",tab[j]);
		puts("");
		delete [] tab;
	}

	return 0;
}

