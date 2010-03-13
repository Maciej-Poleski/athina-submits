#include <cstdio>
#include <algorithm>

using namespace std;

void man(const char * const T,const char * const W,int const N,int * const R)
{
    for(int j,k=0,i=0;k<=2*N;k+=j,i=max(i-j,-(k%2)))
    {
	while((k-i)/2>0 && (k+i)/2<N && (T[(k-i)/2-1]==W[(k+i)/2]) && (W[(k-i)/2-1]==T[(k+i)/2]))
	    i+=2;
	R[k]=i;
	for(j=1;j<i && j+R[k-j]<i;++j)
	    R[k+j]=R[k-j];
    }
}

int main()
{
    int z;
    scanf("%d",&z);
    while(z--)
    {
	int n;
	scanf("%d\n",&n);
	char T[n+5];
	scanf("%s\n",T);
	int R[2*n+5];
	char W[2*n+5];
	scanf("%s\n",W);
	man(T,W,n,R);
	int M=0;
	for(int i=0;i<2*n+1;++i)
	    M=max(M,R[i]);
	printf("%d\n",M);
    }
    return 0;
}

