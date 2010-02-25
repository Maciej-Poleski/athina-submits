#include <cstdio>
#include <algorithm>
#include <cstring>

const int n=1000000,m=1000000;
char W[n+5];
char T[m+5];
int PP[n+5];
int R[m+5];
char WR[n+5];
char TR[m+5];
int PPR[n+5];
int RR[m+5];
int rozw[m+5];

using namespace std;

inline void f(char *const W,int N,int *const PP,char *const T,int M,int *const R)
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
    int z;

    scanf("%d",&z);
    while(z--)
    {
	int n,m;
	scanf("%d %s\n%d %s",&n,W,&m,T);

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

	for(int i=0;i<=m-n;++i)
	    rozw[i]=0;

	if(R[0]==n)
	{
	    ++rozw[0];
	    --rozw[1];
	}
	for(int i=1;i<m;++i)
	{
	    if(RR[m-i]==n)
		--RR[m-i];
	    int am=R[i]+RR[m-i]-n;
	    //for(int j=0;j<=am;++j)
		//rozw[i-RR[m-i]+j]=true;
	    if(am<0)
		continue;
	    ++rozw[i-RR[m-i]];
	    --rozw[i-RR[m-i]+am+1];
	    //for(;R[i]+RR[m-i]>=n;--RR[m-i])
	    //{
		//rozw[i-RR[m-i]]=true;
		//i+=max(R[i]-1,0);
	    //}
	}

	int w=0,t=0;
	for(int i=0;i<=m-n;++i)
	{
	    t+=rozw[i];
	    if(t>0)
		++w;
	}
	printf("%d",w);
	for(int i=0,t=0;i<=m-n;++i)
	{
	    t+=rozw[i];
	    if(t>0)
		printf(" %d",i);
	}
	printf("\n");


    }
    return 0;
}
