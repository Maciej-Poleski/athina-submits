#include <cstdio>
#include <stdint.h>

bool		P[200][200];
uint32_t	W[200][200];

uint32_t	n;
uint32_t	m;

int main()
{
	uint32_t	z;
	scanf("%u",&z);
	while(z--)
	{
		bool 		N=false;
		uint32_t	a;
		uint32_t	b;
		scanf("%u%u",&n,&m);
		
		for(uint32_t i=0;i<n;++i)
			for(uint32_t j=0;j<n;++j)
			{
				P[i][j]=false;
				W[i][j]=0;
			}
		
		for(uint32_t i=0;i<m;++i)
		{
			scanf("%u%u",&a,&b);
			P[a-1][b-1]=true;
		}
		
		for(uint32_t i=0;i<n;++i)
			P[i][i]=true;
		
		for(uint32_t i=0;i<n;++i)							//Domknięcie przechodnie
			for(uint32_t j=0;j<n;++j)
				for(uint32_t k=0;k<n;++k)
					if(P[j][k]==false && P[j][i]==true && P[i][k]==true)
						P[j][k]=true;
						
		/*for(uint32_t i=0;i<n;++i)
		{
			for(uint32_t j=0;j<n;++j)
				printf("%u ",P[i][j]);
			putchar('\n');
		}*/
		
		for(uint32_t i=0;i<n;++i)							//Zliczanie
			for(uint32_t j=0;j<n;++j)
				for(uint32_t k=0;k<n;++k)
					if(P[i][k] && P[j][k])
						++W[i][j];
		
		/*putchar('\n');
		for(uint32_t i=0;i<n;++i)
		{
			for(uint32_t j=0;j<n;++j)
				printf("%u ",W[i][j]);
			putchar('\n');
		}*/
		
		for(uint32_t i=0;i<n;++i)							//Stożki
			for(uint32_t j=0;j<n;++j)
				for(uint32_t k=0;k<n;++k)
					if(i!=j && j!=k && i!=k && P[i][j] && !P[i][k] && !P[k][j])
						if(W[i][k]!=W[i][j])
							N=true;
		
		if(N)
			puts("TAK");
		else
			puts("NIE");
	}
	return 0;
}
