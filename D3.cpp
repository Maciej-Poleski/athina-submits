#include <cstdio>

const int inf=2000002;				// Nieskończoność

int main()
{
	int z;
	scanf("%d\n",&z);
	while(z--)
	{
		/* n - ilość dostępnych nominałów
		 * m - suma do wydania
		 */
		
		int n,m;
		scanf("%d %d\n",&n,&m);

		int *N=new int[n];			// Dostępne nominały
		int *S=new int[m+1];		// Ilość sposobów wydania m znajduje się w S[m] po zakończeniu algorytmu

		// Czyszczenie S
		for(int i=1;i<=m;S[i++]=0);

		S[0]=1;						// Zero można wydać zawsze na jeden sposób

		for(int i=0;i<n;++i)		// Wczytuje dostępne nominały
			scanf("%d ",N+i);

		// Określam ilość rozwiązań O(n*m)
		for(int i=0;i<n;++i)
			for(int j=N[i];j<=m;++j)
				S[j]=(S[j]+S[j-N[i]])%1000000;

		printf("%d\n",S[m]);		// Wypisuje ilość rozwiązań

		if(S[m]==0)					// Jeżeli nie istnieje rozwiązanie
		{
			delete [] S;
			printf("ZONK\n");
			delete [] N;
			continue;
		}

		delete [] S;				// To jest już nie potrzebne

		int *C=new int[m+1];		// Ile minimum nominałów należy użyć, aby wydać m
		int *B=new int[m+1];		// Jaki nominał należy wydać podczas wydawania m

		//Czyszczenie
		for(int i=1;i<=m;C[i++]=inf);

		C[0]=0;						// Zero można wydać optymalnie kożystając z zera nominałów.
		B[0]=0;						// Gdy pozostało nam do wydania zero, kończymy wydawanie (strażnik)

		// Szukam optymalnego rozwiązania O(n*m)
		for(int i=0;i<n;++i)
			for(int j=N[i];j<=m;++j)
				if(C[j]>C[j-N[i]]+1)
				{
					C[j]=C[j-N[i]]+1;
					B[j]=N[i];
				}

		// Wypisuje optymalne rozwiązanie
		printf("%d",C[m]);
		delete [] C;				// To już jest niepotrzebne
		while(m)
		{
			printf(" %d",B[m]);
			m-=B[m];
		}
		printf("\n");

		// Czyszczenie
		delete [] N;
		delete [] B;
	}
	return 0;
}
