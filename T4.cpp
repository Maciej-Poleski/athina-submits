#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

void f(char *const W,int N,int *const PP,char *const T,int M,int *const R)
{
    for(int j,i=0,k=0;k<M;k+=j,i=max(0,i-j))
    {
	while(i<N && k+i<M && W[i]==T[k+i])
	    ++i;
	R[k]=i;
	for(j=1;j<i && j+PP[j]<i;++j)
	    R[j+k]=PP[j];
    }
}

int main()
{
    char *T=0;
    char *TR=0;
    char *W=0;
    char *WR=0;
    int *PP=0;
    int *PPR=0;
    int *R=0;
    int *RR=0;
    int z;
    const int n=1000000,m=1000000;
    W=new char[n+5];
    T=new char[m+5];
    PP=new int[n+5];
    R=new int[m+5];
    WR=new char[n+5];
    TR=new char[m+5];
    PPR=new int[n+5];
    RR=new int[m+5];
    bool rozw[m+5];
    scanf("%d\n",&z);
    while(z--)
    {
	int n,m;
	scanf("%d ",&n);

	scanf("%s\n",W);
	scanf("%d ",&m);

	scanf("%s\n",T);

	for(int i=n-1;i>=0;--i)
	    WR[n-i-1]=W[i];
	for(int i=m-1;i>=0;--i)
	    TR[m-i-1]=T[i];
	WR[n]=0;
	TR[m]=0;
	f(W,n,PP,W+1,n-1,PP+1);
	f(WR,n,PPR,WR+1,n-1,PPR+1);
	f(W,n,PP,T,m,R);
	f(WR,n,PPR,TR,m,RR);

	/*printf("%d %d\n%s\n%s\n%s\n%s\n",n,m,W,WR,T,TR);

	for(int i=0;i<n;++i)
	    printf("%d ",PP[i]);
	printf("\n");
	for(int i=0;i<n;++i)
	    printf("%d ",PPR[i]);
	printf("\n");
	for(int i=0;i<m;++i)
	    printf("%d ",R[i]);
	printf("\n");
	for(int i=m-1;i>=0;--i)
	    printf("%d ",RR[i]);
	printf("\n");
	for(int i=0;i<=m;++i)
	    printf("%d ",RR[i]);
	printf("\n");*/



	int w=0;


	memset(rozw,0,m+1);

	if(R[0]==n)
	{
	    ++w;
	    rozw[0]=true;
	}
	for(int i=1;i<m;++i)
	{
	    if(RR[m-i]==n)
		--RR[m-i];
	    for(;R[i]+RR[m-i]>=n;++w,--RR[m-i])
	    {
		if(rozw[i-RR[m-i]])
		{
		    --w;
		    continue;
		}
		rozw[i-RR[m-i]]=true;
		//i+=max(R[i]-1,0);
	    }
	}

	printf("%d",w);
	for(int i=0;i<=m;++i)
	    if(rozw[i])
		printf(" %d",i);
	printf("\n");


    }
    delete [] T;
    delete [] TR;
    delete [] W;
    delete [] WR;
    delete [] PP;
    delete [] PPR;
    delete [] R;
    delete [] RR;
    return 0;
}
