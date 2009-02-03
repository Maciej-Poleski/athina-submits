#include <cstdio>
#include <string>
#include <map>

using namespace std;

int32_t		D[200][200];
string		*N;
char		temp[11];
char		temp2[11];
uint32_t	n;

const int32_t inf=100000005;

int main()
{
	uint32_t	z;
	scanf("%u",&z);
	while(z--)
	{
		map<string,uint32_t>	M;
		uint32_t				m;
		scanf("%u\n",&n);
		
		N=new string[n];
		
		for(uint32_t i=0;i<n;++i)
			for(uint32_t j=0;j<n;++j)
				D[i][j]=inf;
			
		for(uint32_t i=0;i<n;++i)
			D[i][i]=0;
		
		for(uint32_t i=0;i<n;++i)
		{
			gets(temp);
			N[i]=temp;
			M.insert(pair<string,uint32_t>(temp,i));
		};
		
		/*for(map<string,uint32_t>::iterator i=M.begin(),e=M.end();i!=e;++i)
		{
			printf("%s %u\n",i->first.c_str(),i->second);
		}
		
		for(uint32_t i=0;i<n;++i)
			printf("%s\n",N[i].c_str());*/
			
		scanf("%u\n",&m);
		while(m--)
		{
			scanf("%s %s",temp,temp2);
			//printf("_%s_%s_\n",temp,temp2);
			scanf("%d\n",&D[M[temp]][M[temp2]]);
			D[M[temp2]][M[temp]]=D[M[temp]][M[temp2]];
		}
		
		/*for(uint32_t i=0;i<n;++i)
		{
			for(uint32_t j=0;j<n;++j)
				printf("%u\t\t",D[i][j]);
			putchar('\n');
		}*/
		
		for(uint32_t i=0;i<n;++i)
			for(uint32_t j=0;j<n;++j)
				for(uint32_t k=0;k<n;++k)
					if(D[j][k]>D[j][i]+D[i][k])
						D[j][k]=D[j][i]+D[i][k];
		
		/*for(uint32_t i=0;i<n;++i)
		{
			for(uint32_t j=0;j<n;++j)
				printf("%u\t\t",D[i][j]);
			putchar('\n');
		}*/
		
		printf("%12s","");
		for(uint32_t i=0;i<n;++i)
			printf("%12s",N[i].c_str());
		putchar('\n');
		
		for(uint32_t i=0;i<n;++i)
		{
			printf("%12s",N[i].c_str());
			for(uint32_t j=0;j<n;++j)
				printf("%12d",D[i][j]);
			putchar('\n');
		}
		
		delete [] N;
	}
	return 0;
}
