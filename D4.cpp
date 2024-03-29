#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char a[30005];
char b[30005];

int *LCSP;
int *LCSS;

int n;
int m;

int LCS(const int PA,const int KA,const int PB,const int KB)
{
    //printf("\t%d %d %d %d:\n",PA,KA,PB,KB);
    if(KB-PB==1)
    {
	for(int i=PA;i<KA;++i)
	    if(a[i]==b[PB])
	    {
		printf("%c",b[PB]);
		return 1;
	    }
	return 0;
    }
    int l=KA-PA;		// Długość części prefixu słowa a
    
    if(l==0)			// Nie zajmuje się słowem którego nie ma.
	return 0;
    
    LCSP=new int[l];		// Tablica O(n) dla prefixów
    LCSS=new int[l];		// Dla sufiksów
    int x,q;			// Dodatkowy element
    
    /* PREFIXY */
    LCSP[0]=(a[PA]==b[PB])?1:0;
    for(int i=1;i<l;++i)		// Wypełniam LCS prefixów pierwszy rząd
	LCSP[i]=max(LCSP[i-1],(a[PA+i]==b[PB])?1:0);
    
    /*printf("int:");
    for(int i=0;i<l;++i)
	printf(" %d",LCSP[i]);
    puts("");*/
    
    for(int i=PB+1;i<(PB+KB)/2;++i)		// Wyznaczam LCS prefixów (rozwiązanie w LCSP[l-1])
    {
	x=LCSP[0];
	LCSP[0]=max(LCSP[0],(b[i]==a[PA])?1:0);
	for(int j=1;j<l;++j)
	{
	    q=LCSP[j];
	    LCSP[j]=(b[i]==a[j+PA])?1+x:max(LCSP[j],LCSP[j-1]);
	    x=q;
	}
    }
    
    /* SUFIXY */
    LCSS[l-1]=(a[KA-1]==b[KB-1])?1:0;
    for(int i=l-2;i>=0;--i)		// Wypełniam LCS sufiksów pierwszy rząd
	LCSS[i]=max(LCSS[i+1],a[PA+i]==b[KB-1]?1:0);
    
    for(int i=KB-2;i>=(PB+KB)/2;--i)		// Wyznaczam LCS sufixów (rozwiązanie w LCSS[l-1])
    {
	x=LCSS[l-1];
	LCSS[l-1]=max(LCSS[l-1],(b[i]==a[KA-1])?1:0);
	for(int j=l-2;j>=0;--j)
	{
	    q=LCSS[j];
	    LCSS[j]=(b[i]==a[PA+j])?1+x:max(LCSS[j],LCSS[j+1]);
	    x=q;
	}
    }
    
    /*for(int i=0;i<l;++i)
	printf("%d ",LCSP[i]);
    puts("");
    
    for(int i=0;i<l;++i)
	printf("%d ",LCSS[i]);
    puts("");*/
    
    x=-1;
    q=LCSS[0];
    
    for(int i=0;i<l-1;++i)
    {
	if(LCSP[i]+LCSS[i+1]>q)
	{
	    x=i;
	    q=LCSP[i]+LCSS[i+1];
	}
    }
    
    if(LCSP[l-1]>q)
    {
	q=LCSP[l-1];
	x=l-1;
    }
    
    int t1=(x>=0)?LCSP[x]:0;
    int t2=(x+1<l)?LCSS[x+1]:0;
    
    delete [] LCSP;
    delete [] LCSS;
    
    if(int e=LCS(PA,PA+x+1,PB,(PB+KB)/2)!=t1)
	printf("|To rozwiązanie jest błędne!, oczekiwano %d a otrzymano %d|",t1,e);
    if(int e=LCS(PA+x+1,KA,(PB+KB)/2,KB)!=t2)
	printf("|To rozwiązanie jest błędne!, oczekiwano %d a otrzymano %d|",t2,e);
    
    return q;
}

int main()
{
  int z;
  scanf("%d\n",&z);
  while(z--)
  {
      scanf("%s %s\n",a,b);		// Słowa a i b
      
      n=strlen(a);			// Długości
      m=strlen(b);
      
      if(LCS(0,n,0,m)==0)
	  printf("-");
      printf("\n");
  }
  return 0;
}
