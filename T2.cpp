#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int* CP(int m,char *s)
{
    int     *PREF=new int[m+1];
    PREF[1] = -1;
    int     i = 2;
    int     t = 0;
    while (i <= m)
    {
        while (s[i + t] == s[1 + t])
            t++;
        PREF[i] = t;

        int k = 1;
        while (k < PREF[i] && PREF[1 + k] != PREF[i] - k)
        {
            PREF[i + k] = min(PREF[1 + k], PREF[i] - k);
            k++;
        }
        t -= k;
        t = max(0, t);
        i += k;
  }
  return PREF;
}

int main()
{
    int     z;
    scanf("%d\n",&z);
    while(z--)
    {
        int n;
        char *a;
        char *b;
        bool ok;
        scanf("%d\n",&n);
        a=new char[n+2];
        b=new char[n+2];
        scanf("%s\n%s\n",a,b);
        char *s=new char[n*3+2];
        memcpy(s,a,n);
        memcpy(s+n+1,b,n);
        memcpy(s+n+n+1,b,n);
        s[n]='#';
        s[3*n+1]='@';

        int *PREF1=CP(3*n+1,s-1);

        /*for(int i=0;i<=3*n+1;++i)
            printf("%d ",PREF1[i]);
        putchar('\n');*/
        
        for(int i=0;i<n;++i)
            s[n-i-1]=a[i];
        for(int i=0;i<n;++i)
            s[n+n-i]=s[3*n-i]=b[i];

        delete [] a;
        delete [] b;
        
        int *PREF2=CP(3*n+1,s-1);

        /*for(int i=0;i<=3*n+1;++i)
            printf("%d ",PREF2[i]);
        putchar('\n');*/

        for(int i=0;i<=n;++i)
            if((ok=(PREF1[n+2+i]+PREF2[2*n+2-i]==n-1)))
            {
                printf("TAK\n");
                //printf(" %d\n",i);
                break;
            }

        if(!ok)
            printf("NIE\n");

        delete [] PREF1;
        delete [] PREF2;
        delete [] s;
    }
    return 0;
}
