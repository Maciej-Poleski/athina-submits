#include <cstdio>

int main()
{
    int z;
    scanf("%d\n",&z);
    while(z--)
    {
        int n;
        scanf("%d\n",&n);
        char text[n];
        scanf("%s\n",text);

        int KMPNext[n+1],b=-1,w=0;
        KMPNext[0]=b;

        /*for(int i=1;i<=n;++i)
        {
            while((b>-1) && text[i-1]!=text[b])
                b=KMPNext[b];
            ++b;
            if(text[i]!=text[b] || b==n)
            {
                KMPNext[i]=b;
                ++w;
            }
            else
                KMPNext[i]=KMPNext[b];
        }*/

        for(int i=0;i<n;++i)
        {
            while((b>-1) && text[i]!=text[b])
                b=KMPNext[b];
            KMPNext[i+1]=++b;
        }

        for(int i=1;i<=n;++i)
            if(i/(i-KMPNext[i])>1)
                ++w;

        printf("%d\n",w);

        for(int i=1;i<=n;++i)
            if(i/(i-KMPNext[i])>1)
                printf("%d %d\n",i,i/(i-KMPNext[i]));
    }
    return 0;
}