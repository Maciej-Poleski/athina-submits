#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

struct w
{
	int		v;
	int		p;
};

w			*tab;
int			n;

bool cmp(int a,int b)
{
	return tab[a].v<tab[b].v;
}

int main()
{
	int z;
	scanf("%d\n",&z);
	while(z--)
	{
		scanf("%d\n",&n);
		tab=new w[n+1];
		for(int i=1;i<=n;++i)
			scanf("%d ",&tab[i].v);
		vector<int>	wynik;
		wynik.push_back(1);
		tab[1].p=0;

		for(int i=2;i<=n;++i)
		{
			int p=lower_bound(wynik.begin(),wynik.end(),i,cmp)-wynik.begin();
			if(p==wynik.size())
			{
				wynik.push_back(i);
				tab[i].p=wynik[p-1];
				continue;
			}
			wynik[p]=i;
			tab[i].p=wynik[p-1];
		}

		int *ww=new int[n];
		int *p=ww;
		int i=wynik.back();
		while(i!=0)
		{
			*p++=i;
			i=tab[i].p;
		}

		delete [] tab;

		printf("%d\n",p-ww);
		while(p!=ww)
			printf("%d ",*--p);
		printf("\n");

		delete [] ww;
	}
	return 0;
}
