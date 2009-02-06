#include <cstdio>
#include <algorithm>

using namespace std;

uint32_t		n;
uint32_t		wynik=0;
pair<int,int>	*vertex;
int				*D;

const int		inf=2000000000;

int main()
{
	uint32_t	z;
	scanf("%u",&z);
	while(z--)
	{
		uint32_t	n;
		int			x;
		int			y;
		
		scanf("%u",&n);
		
		vertex=new pair<int,int>[n];
		
		for(uint32_t i=0;i<n;++i)
		{
			scanf("%d%d",&x,&y);
			vertex[i].first=x+y;
			vertex[i].second=y-x;
		}
		
		sort(vertex,vertex+n);
		
		D=new int[n];
		
		for(uint32_t i=0;i<n;++i)
		{
			D[i]=inf;
		}
		
		for(int i=n-1;i>=0;--i)
		{
			uint32_t	p=lower_bound(D,D+wynik,vertex[i].second)-D;
			D[p]=vertex[i].second;
			
			if(p==wynik)
				++wynik;
		}
		
		/*for(uint32_t i=0;i<n;++i)
			printf("%d ",D[i]);
		putchar('\n');*/
		
		printf("%u\n",wynik);
		
		delete [] D;
		delete [] vertex;
		
		wynik=0;
	}
	return 0;
}
