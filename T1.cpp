#include <cstdio>
#include <cstring>

const int maxSize=2000000;

char W[maxSize];
char T[maxSize];
int n;
int PS[maxSize+1];
int R[maxSize+1];
int A[maxSize+1];
int B[maxSize+1];

void kmp(char* const W,const int N,int* const PS,char* const T,const int M,int* const R)
{
    int t=-1;
    for(int j=0;j<=M;++j)
    {
	while(t>=0 && T[j-1]!=W[t])
	    t=PS[t];
	R[j]=++t;
	if(t==N)
	    t=PS[t];
    }
}

int main()
{
    int z;
    scanf("%d\n",&z);
    while(z--)
    {
	scanf("%s\n",W);
	n=strlen(W);			// Długość W - n
	for(int i=n-1;i>=0;--i)		// T=W.reverse()
	    T[n-i-1]=W[i];
	T[n]=0;

	PS[0]=R[0]=-1;
	kmp(W,n,PS,W+1,n-1,PS+1);
	kmp(T,n,R,T+1,n-1,R+1);

	kmp(T,n,R,W,n,A);
	kmp(W,n,PS,T,n,B);

	if(A[n]>B[n])
	{
	    printf("%s",W);
	    for(int i=A[n];i<n;++i)
		putchar(T[i]);
	    printf("\n");
	}
	else
	{
	    printf("%s",T);
	    for(int i=B[n];i<n;++i)
		printf("%c",W[i]);
	    printf("\n");
	}
    }
    return 0;
}
