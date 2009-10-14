#include <vector>
#include <algorithm>
#include <cstdio>
#include <climits>

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
		tab[0].v=INT_MIN;
		tab[0].p=0;

		for(int i=2;i<=n;++i)
		{
			vector<int>::iterator ttt=lower_bound(wynik.begin(),wynik.end(),i,cmp);
			int p=ttt-wynik.begin();
			if(ttt==wynik.end())
			{
				wynik.push_back(i);
				tab[i].p=wynik[p-1];
				continue;
			}
			wynik[p]=i;
			if(p!=0)
				tab[i].p=wynik[p-1];
			else
				tab[i].p=0;
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
