#include <cstdio>
#include <complex>
#include <utility>

#define REP(n,i) for(int i=0;i<n;++i)

using namespace std;

void kmp(pair<complex<long long>,complex<long long> >* const W,const int N,int* const PS,pair<complex<long long>,complex<long long> >* const T,const int M,int* const R)
{
    int t=-1;
    for(int j=0;j<=M;++j)
    {
	while(t>=0 && T[j-1].first*W[t].second!=T[j-1].second*W[t].first)
	    t=PS[t];
	R[j]=++t;
	if(t==N)
	    t=PS[t];
    }
}

int main()
{
    int z;
    scanf("%d",&z);
    while(z--)
    {
	int n;
	scanf("%d",&n);
	pair<int,int> *A=new pair<int,int>[n+2];		// Współrzędne
	REP(n,i) scanf("%d%d",&A[i].first,&A[i].second);
	pair<int,int> *B=new pair<int,int>[n+2];
	REP(n,i) scanf("%d%d",&B[i].first,&B[i].second);
	A[n]=A[0];
	B[n]=B[0];
	A[n+1]=A[1];
	B[n+1]=B[1];
	complex<long long> *T=new complex<long long>[n+1];	// Wektory
	complex<long long> *P=new complex<long long>[n+1];
	REP(n,i)
	{
	    complex<long long> a(A[i+1].first-A[i].first,A[i+1].second-A[i].second);
	    //complex<long long> b(A[i+2].first-A[i+1].first,A[i+2].second-A[i+1].second);
	    complex<long long> c(B[i+1].first-B[i].first,B[i+1].second-B[i].second);
	    //complex<long long> d(B[i+2].first-B[i+1].first,B[i+2].second-B[i+1].second);
	    T[i]=a;
	    P[i]=c;
	    //printf("a: %lld %lld | b: %lld %lld | c: %lld %lld | d: %lld %lld\n",a.real(),a.imag(),b.real(),b.imag(),c.real(),c.imag(),d.real(),d.imag());
	}
	T[n]=T[0];
	P[n]=P[0];
	//REP(n,i) T[n+i]=T[i];
	delete [] A;
	delete [] B;

	pair<complex<long long>,complex<long long> > TT[n*2];	// Tekst
	pair<complex<long long>,complex<long long> > PP[n];	// Wzorzec

	REP(n,i) TT[i]=make_pair(T[i],T[i+1]),PP[i]=make_pair(P[i],P[i+1]);
	REP(n,i) TT[n+1]=TT[i];

	delete [] T;
	delete [] P;

	int PS[n+5];
	int R[2*n+5];
	PS[0]=R[0]=-1;
	kmp(PP,n,PS,PP+1,n-1,PS+1);
	kmp(PP,n,PS,TT,n*2,R);

	int max=0;
	REP(n*2+1,i) max=max<R[i]?R[i]:max;
	printf("%s\n",max+1>=n?"TAK":"NIE");
    }
    return 0;
}
