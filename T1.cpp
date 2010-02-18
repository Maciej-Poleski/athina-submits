#include <cstdio>
#include <cstring>

const int maxSize=2000005;

int n;

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
    char *W=new char[maxSize];
    char *T=new char[maxSize];
    int *PS=new int[maxSize+1];
    int *R=new int[maxSize+1];
    int *A=new int[maxSize+1];
    int *B=new int[maxSize+1];

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

    delete [] W;
    delete [] T;
    delete [] PS;
    delete [] R;
    delete [] A;
    delete [] B;

    return 0;
}
